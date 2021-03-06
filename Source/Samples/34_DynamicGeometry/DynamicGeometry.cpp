//
// Copyright (c) 2008-2014 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Camera.h"
#include "CoreEvents.h"
#include "Engine.h"
#include "Font.h"
#include "Geometry.h"
#include "Graphics.h"
#include "Input.h"
#include "Light.h"
#include "Log.h"
#include "Model.h"
#include "Octree.h"
#include "Profiler.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StaticModel.h"
#include "Text.h"
#include "VertexBuffer.h"
#include "UI.h"
#include "Zone.h"

#include "DynamicGeometry.h"

#include "DebugNew.h"

DEFINE_APPLICATION_MAIN(DynamicGeometry)

DynamicGeometry::DynamicGeometry(Context* context) :
    Sample(context),
    animate_(true),
    time_(0.0f)
{
}

void DynamicGeometry::Start()
{
    // Execute base class startup
    Sample::Start();

    // Create the scene content
    CreateScene();
    
    // Create the UI content
    CreateInstructions();
    
    // Setup the viewport for displaying the scene
    SetupViewport();
    
    // Hook up to the frame update events
    SubscribeToEvents();
}

void DynamicGeometry::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    
    scene_ = new Scene(context_);
    
    // Create the Octree component to the scene so that drawable objects can be rendered. Use default volume
    // (-1000, -1000, -1000) to (1000, 1000, 1000)
    scene_->CreateComponent<Octree>();

    // Create a Zone for ambient light & fog control
    Node* zoneNode = scene_->CreateChild("Zone");
    Zone* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetFogColor(Color(0.2f, 0.2f, 0.2f));
    zone->SetFogStart(200.0f);
    zone->SetFogEnd(300.0f);
    
    // Create a directional light
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(-0.6f, -1.0f, -0.8f)); // The direction vector does not need to be normalized
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetColor(Color(0.4f, 1.0f, 0.4f));
    light->SetSpecularIntensity(1.5f);
    
    // Get the original model and its unmodified vertices, which are used as source data for the animation
    Model* originalModel = cache->GetResource<Model>("Models/Box.mdl");
    if (!originalModel)
    {
        LOGERROR("Model not found, cannot initialize example scene");
        return;
    }
    // Get the vertex buffer from the first geometry's first LOD level
    VertexBuffer* buffer = originalModel->GetGeometry(0, 0)->GetVertexBuffer(0);
    const unsigned char* vertexData = (const unsigned char*)buffer->Lock(0, buffer->GetVertexCount());
    if (vertexData)
    {
        unsigned numVertices = buffer->GetVertexCount();
        unsigned vertexSize = buffer->GetVertexSize();
        // Copy the original vertex positions
        for (unsigned i = 0; i < numVertices; ++i)
        {
            const Vector3& src = *reinterpret_cast<const Vector3*>(vertexData + i * vertexSize);
            originalVertices_.Push(src);
        }
        buffer->Unlock();
        
        // Detect duplicate vertices to allow seamless animation
        vertexDuplicates_.Resize(originalVertices_.Size());
        for (unsigned i = 0; i < originalVertices_.Size(); ++i)
        {
            vertexDuplicates_[i] = i; // Assume not a duplicate
            for (unsigned j = 0; j < i; ++j)
            {
                if (originalVertices_[i].Equals(originalVertices_[j]))
                {
                    vertexDuplicates_[i] = j;
                    break;
                }
            }
        }
    }
    else
    {
        LOGERROR("Failed to lock the model vertex buffer to get original vertices");
        return;
    }
    
    // Create StaticModels in the scene. Clone the model for each so that we can modify the vertex data individually
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            Node* node = scene_->CreateChild("Object");
            node->SetPosition(Vector3(x * 2.0f, 0.0f, y * 2.0f));
            StaticModel* object = node->CreateComponent<StaticModel>();
            SharedPtr<Model> cloneModel = originalModel->Clone();
            object->SetModel(cloneModel);
            // Store the cloned vertex buffer that we will modify when animating
            animatingBuffers_.Push(SharedPtr<VertexBuffer>(cloneModel->GetGeometry(0, 0)->GetVertexBuffer(0)));
        }
    }

    // Create the camera
    cameraNode_ = new Node(context_);
    cameraNode_->SetPosition(Vector3(0.0f, 2.0f, -20.0f));
    Camera* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(300.0f);
}

void DynamicGeometry::CreateInstructions()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    UI* ui = GetSubsystem<UI>();
    
    // Construct new Text object, set string to display and font to use
    Text* instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetText(
        "Use WASD keys and mouse/touch to move\n"
        "Space to toggle animation"
    );
    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_CENTER);
    instructionText->SetVerticalAlignment(VA_CENTER);
    instructionText->SetPosition(0, ui->GetRoot()->GetHeight() / 4);
}

void DynamicGeometry::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();
    
    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}

void DynamicGeometry::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, HANDLER(DynamicGeometry, HandleUpdate));
}

void DynamicGeometry::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;
    
    Input* input = GetSubsystem<Input>();
    
    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.1f;
    
    // Use this frame's mouse motion to adjust camera node yaw and pitch. Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    
    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    if (input->GetKeyDown('W'))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('S'))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('A'))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown('D'))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void DynamicGeometry::AnimateObjects(float timeStep)
{
    PROFILE(AnimateObjects);
    
    time_ += timeStep * 100.0f;
    
    // Repeat for each of the cloned vertex buffers
    for (unsigned i = 0; i < animatingBuffers_.Size(); ++i)
    {
        float startPhase = time_ + i * 30.0f;
        VertexBuffer* buffer = animatingBuffers_[i];
        
        // Lock the vertex buffer for update and rewrite positions with sine wave modulated ones
        // Cannot use discard lock as there is other data (normals, UVs) that we are not overwriting
        unsigned char* vertexData = (unsigned char*)buffer->Lock(0, buffer->GetVertexCount());
        if (vertexData)
        {
            unsigned vertexSize = buffer->GetVertexSize();
            unsigned numVertices = buffer->GetVertexCount();
            for (unsigned j = 0; j < numVertices; ++j)
            {
                // If there are duplicate vertices, animate them in phase of the original
                float phase = startPhase + vertexDuplicates_[j] * 10.0f;
                Vector3& src = originalVertices_[j];
                Vector3& dest = *reinterpret_cast<Vector3*>(vertexData + j * vertexSize);
                dest.x_ = src.x_ * (1.0f + 0.1f * Sin(phase));
                dest.y_ = src.y_ * (1.0f + 0.1f * Sin(phase + 60.0f));
                dest.z_ = src.z_ * (1.0f + 0.1f * Sin(phase + 120.0f));
            }
            
            buffer->Unlock();
        }
    }
}

void DynamicGeometry::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();
    
    // Toggle animation with space
    Input* input = GetSubsystem<Input>();
    if (input->GetKeyPress(KEY_SPACE))
        animate_ = !animate_;

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);
    
    // Animate objects' vertex data if enabled
    if (animate_)
        AnimateObjects(timeStep);
}
