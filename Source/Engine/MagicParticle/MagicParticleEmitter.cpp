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

#include "Precompiled.h"
#include "Camera.h"
#include "Context.h"
#include "Drawable2D.h"
#include "Geometry.h"
#include "GraphicsEvents.h"
#include "IndexBuffer.h"
#include "Log.h"
#include "MagicParticleEffect.h"
#include "MagicParticleEmitter.h"
#include "Material.h"
#include "Node.h"
#include "Profiler.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "SceneEvents.h"
#include "Sort.h"
#include "VertexBuffer.h"
#include "WorkQueue.h"

#include "DebugNew.h"


extern T_Magic_CreateFirstRenderedParticlesList Magic_CreateFirstRenderedParticlesList;
extern T_Magic_CreateNextRenderedParticlesList Magic_CreateNextRenderedParticlesList;
extern T_Magic_DuplicateEmitter Magic_DuplicateEmitter;
extern T_Magic_GetBBox Magic_GetBBox;
extern T_Magic_GetNextParticleVertexes Magic_GetNextParticleVertexes;
extern T_Magic_InInterval Magic_InInterval;
extern T_Magic_IsInterrupt Magic_IsInterrupt;
extern T_Magic_Restart Magic_Restart;
extern T_Magic_SetBBoxPeriod Magic_SetBBoxPeriod;
extern T_Magic_SetCamera Magic_SetCamera;
extern T_Magic_SetEmitterDirection Magic_SetEmitterDirection;
extern T_Magic_SetEmitterPosition Magic_SetEmitterPosition;
extern T_Magic_SetInterrupt Magic_SetInterrupt;
extern T_Magic_SetScale Magic_SetScale;
extern T_Magic_Stop Magic_Stop;
extern T_Magic_UnloadEmitter Magic_UnloadEmitter;
extern T_Magic_Update Magic_Update;

namespace Urho3D
{

extern const char* GEOMETRY_CATEGORY;

// Magic particle vertex.
struct MParticleVertex
{
    // Position.
    Vector3 position_;
    // Color.
    unsigned color_;
    // Texcoord.
    Vector2 uv_;
};

// Magic particle vertex mask.
static const unsigned MASK_MPARTICLE_VERTEX = MASK_POSITION | MASK_COLOR | MASK_TEXCOORD1;

static inline Vector3 MagicToVector3(const MAGIC_POSITION& pos)
{
    return Vector3(pos.x, pos.y, pos.z);
}

static inline MAGIC_POSITION Vector3ToMagic(const Vector3& position)
{
    MAGIC_POSITION magicPosition = { position.x_, position.y_, position.z_ };
    return magicPosition;
}

static inline MAGIC_DIRECTION QuaternionToMagic(const Quaternion& rotation)
{
    MAGIC_DIRECTION magicDirection = { rotation.x_, rotation.y_, rotation.z_, rotation.w_ };
    return magicDirection;
}

MagicParticleEmitter::MagicParticleEmitter(Context* context) :
    Drawable(context, DRAWABLE_PROXYGEOMETRY),
    index_(-1),
    magicEmitter_(0),
    indexBuffer_(new IndexBuffer(context_)),
    vertexBuffer_(new VertexBuffer(context_))
{
}

MagicParticleEmitter::~MagicParticleEmitter()
{
    if(magicEmitter_ > 0)
        Magic_UnloadEmitter(magicEmitter_);
}

void MagicParticleEmitter::RegisterObject(Context* context)
{
    context->RegisterFactory<MagicParticleEmitter>(GEOMETRY_CATEGORY);

    ACCESSOR_ATTRIBUTE(MagicParticleEmitter, VAR_RESOURCEREF, "Magic Particle Effect", GetEffectAttr, SetEffectAttr, ResourceRef, ResourceRef(MagicParticleEffect::GetTypeStatic()), AM_DEFAULT);
    ACCESSOR_ATTRIBUTE(MagicParticleEmitter, VAR_INT, "Emitter Index", GetIndex, SetIndex, int, -1, AM_DEFAULT);
    COPY_BASE_ATTRIBUTES(MagicParticleEmitter, Drawable);
}

void MagicParticleEmitter::OnSetEnabled()
{
    Drawable::OnSetEnabled();

    Scene* scene = GetScene();
    if (scene)
    {
        if (IsEnabledEffective())
        {
            Restart();
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(MagicParticleEmitter, HandleScenePostUpdate));
        }
        else
        {
            Stop();
            UnsubscribeFromEvent(scene, E_SCENEPOSTUPDATE);
        }
    }
}

void MagicParticleEmitter::Update(const FrameInfo& frame)
{
    if (magicEmitter_ == 0)
        return;

    if (Magic_IsInterrupt(magicEmitter_))
        return;

    // Set current camera
    Camera* camera = frame.camera_;
    Vector3 cameraPos = camera->GetNode()->GetWorldPosition();
    Vector3 cameraDir = camera->GetNode()->GetWorldDirection();
    
    static MAGIC_CAMERA magicCamera;
    magicCamera.pos = Vector3ToMagic(cameraPos);
    magicCamera.dir = Vector3ToMagic(cameraDir);
    Magic_SetCamera(&magicCamera);

    // Set world position
    MAGIC_POSITION emitterPosition = Vector3ToMagic(node_->GetWorldPosition());
    Magic_SetEmitterPosition(magicEmitter_, &emitterPosition);
    Magic_SetScale(magicEmitter_, 0.01f);

    // Set world rotation
    MAGIC_DIRECTION emitterDirection = QuaternionToMagic(node_->GetWorldRotation());
    Magic_SetEmitterDirection(magicEmitter_, &emitterDirection);

    // Update emitter
    Magic_Update(magicEmitter_, 1000.0 * frame.timeStep_);

    OnMarkedDirty(node_);
}

void MagicParticleEmitter::UpdateBatches(const FrameInfo& frame)
{
    numParticles_.Clear();
    particles_.Clear();

    Vector<SharedPtr<Material> > materials;

    if (magicEmitter_ >0 && Magic_InInterval(magicEmitter_))
    {
        MAGIC_RENDERING rendering;
        Magic_CreateFirstRenderedParticlesList(magicEmitter_, &rendering);
        while (rendering.count)
        {
            unsigned base = particles_.Size();
            particles_.Resize(base + rendering.count);

            for (int i = 0; i < rendering.count; ++i)
                Magic_GetNextParticleVertexes(&particles_[base + i]);

            numParticles_.Push(rendering.count);
            SharedPtr<Material> material(effect_->GetMaterial(rendering.texture_id, rendering.intense));
            materials.Push(material);

            Magic_CreateNextRenderedParticlesList(&rendering);
        }
    }

    batches_.Resize(materials.Size());
    geometries_.Resize(materials.Size());

    for (unsigned i = 0; i < materials.Size(); ++i)
    {
        batches_[i].material_ = materials[i];
        batches_[i].distance_ = 0.0f;
        batches_[i].worldTransform_ = &Matrix3x4::IDENTITY;
    }
}

void MagicParticleEmitter::UpdateGeometry(const FrameInfo& frame)
{
    unsigned totalParticles = 0;
    for (unsigned i = 0; i < numParticles_.Size(); ++i)
        totalParticles += numParticles_[i];

    unsigned totalIndexCount = totalParticles * 6;
    unsigned totalVertexCount = totalParticles * 4;

    if (indexBuffer_->GetIndexCount() < totalIndexCount)
    {
        bool largeIndices = totalVertexCount > 0xffff;
        indexBuffer_->SetSize(totalIndexCount, largeIndices);
        void* buffer = indexBuffer_->Lock(0, totalIndexCount, true);
        if (buffer)
        {
            if (largeIndices)
            {
                unsigned* dest = reinterpret_cast<unsigned*>(buffer);
                for (unsigned i = 0; i < particles_.Size(); ++i)
                {
                    unsigned base = i * 4;
                    dest[0] = base;
                    dest[1] = base + 1;
                    dest[2] = base + 2;
                    dest[3] = base;
                    dest[4] = base + 2;
                    dest[5] = base + 3;
                    dest += 6;
                }
            }
            else
            {
                unsigned short* dest = reinterpret_cast<unsigned short*>(buffer);
                for (unsigned i = 0; i < particles_.Size(); ++i)
                {
                    unsigned base = i * 4;
                    dest[0] = (unsigned short)(base);
                    dest[1] = (unsigned short)(base + 1);
                    dest[2] = (unsigned short)(base + 2);
                    dest[3] = (unsigned short)(base);
                    dest[4] = (unsigned short)(base + 2);
                    dest[5] = (unsigned short)(base + 3);
                    dest += 6;
                }
            }

            indexBuffer_->Unlock();
        }
        else
        {
            LOGERROR("Failed to lock index buffer");
            return;
        }
    }

    if (vertexBuffer_->GetVertexCount() < totalVertexCount)
        vertexBuffer_->SetSize(totalVertexCount, MASK_MPARTICLE_VERTEX);

    if (totalVertexCount)
    {
        MParticleVertex* dest = reinterpret_cast<MParticleVertex*>(vertexBuffer_->Lock(0, totalVertexCount, true));
        if (dest)
        {
            for (unsigned d = 0; d < particles_.Size(); ++d)
            {
                const MAGIC_PARTICLE_VERTEXES& vertices = particles_[d];
                unsigned color = vertices.color;
                
                // ARGB -> ABGR
                unsigned r = (color >> 16) & 0xff;
                unsigned b = (color      ) & 0xff;
                color &= 0xff00ff00;
                color |= (b << 16) + r;

                dest->position_ = MagicToVector3(vertices.vertex1);
                dest->color_ = color;
                dest->uv_ = Vector2(vertices.u1, vertices.v1);
                ++dest;

                dest->position_ = MagicToVector3(vertices.vertex2);
                dest->color_ = color;
                dest->uv_ = Vector2(vertices.u2, vertices.v2);
                ++dest;

                dest->position_ = MagicToVector3(vertices.vertex3);
                dest->color_ = color;
                dest->uv_ = Vector2(vertices.u3, vertices.v3);
                ++dest;

                dest->position_ = MagicToVector3(vertices.vertex4);
                dest->color_ = color;
                dest->uv_ = Vector2(vertices.u4, vertices.v4);
                ++dest;
            }

            vertexBuffer_->Unlock();
        }
        else
            LOGERROR("Failed to lock vertex buffer");
    }

    unsigned indexStart = 0;
    unsigned vertexStart = 0;
    for (unsigned i = 0; i < batches_.Size(); ++i)
    {
        if (!geometries_[i])
        {
            geometries_[i] = new Geometry(context_);
            geometries_[i]->SetIndexBuffer(indexBuffer_);
            geometries_[i]->SetVertexBuffer(0, vertexBuffer_, MASK_MPARTICLE_VERTEX);
        }

        unsigned indexCount = numParticles_[i] * 6;
        unsigned vertexCount = numParticles_[i] * 4;
        geometries_[i]->SetDrawRange(TRIANGLE_LIST, indexStart, indexCount, vertexStart, vertexCount, false);
        indexStart += indexCount;
        vertexStart += vertexCount;

        batches_[i].geometry_ = geometries_[i];
    }
}

UpdateGeometryType MagicParticleEmitter::GetUpdateGeometryType()
{
    return UPDATE_MAIN_THREAD;
}

void MagicParticleEmitter::SetEffect(MagicParticleEffect* effect, int index)
{
    if (effect == effect_ && index == index_)
        return;

    if (magicEmitter_ > 0)
    {
        Stop();

        Magic_UnloadEmitter(magicEmitter_);
        magicEmitter_ = 0;
    }

    effect_ = effect;
    index_ = index;

    if (effect_ && index_ >= 0)
    {
        HM_EMITTER emitter = effect_->GetEmitter(index_);
        if (emitter > 0)
        {
            // Create new emitter
            magicEmitter_ = Magic_DuplicateEmitter(emitter);
            // Calculating bounding box every frame
            Magic_SetBBoxPeriod(magicEmitter_, 1);

            Restart();
        }
    }
}

void MagicParticleEmitter::SetEffect(MagicParticleEffect* effect)
{
    SetEffect(effect, index_);
}

void MagicParticleEmitter::SetIndex(int index)
{
    SetEffect(effect_, index);
}

void MagicParticleEmitter::Restart()
{
    if (magicEmitter_ > 0)
        Magic_Restart(magicEmitter_);
}

void MagicParticleEmitter::Stop()
{
    if (magicEmitter_ > 0)
        Magic_Stop(magicEmitter_);
}

void MagicParticleEmitter::Pause()
{
    if (magicEmitter_ > 0)
        Magic_SetInterrupt(magicEmitter_, true);
}

void MagicParticleEmitter::Resume()
{
    if (magicEmitter_ > 0)
        Magic_SetInterrupt(magicEmitter_, false);
}

MagicParticleEffect* MagicParticleEmitter::GetEffect() const
{
    return effect_;
}

void MagicParticleEmitter::SetEffectAttr(ResourceRef value)
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    SetEffect(cache->GetResource<MagicParticleEffect>(value.name_));
}

ResourceRef MagicParticleEmitter::GetEffectAttr() const
{
    return GetResourceRef(effect_, MagicParticleEffect::GetTypeStatic());
}

void MagicParticleEmitter::OnNodeSet(Node* node)
{
    Drawable::OnNodeSet(node);

    if (node)
    {
        Scene* scene = GetScene();
        if (scene && IsEnabledEffective())
            SubscribeToEvent(scene, E_SCENEPOSTUPDATE, HANDLER(MagicParticleEmitter, HandleScenePostUpdate));
    }
}

void MagicParticleEmitter::OnWorldBoundingBoxUpdate()
{
    if (magicEmitter_ > 0)
    {
        MAGIC_BBOX bbox;
        Magic_GetBBox(magicEmitter_, &bbox);

        worldBoundingBox_.Define(
            Vector3(bbox.corner1.x, bbox.corner1.y, bbox.corner1.z),
            Vector3(bbox.corner2.x, bbox.corner2.y, bbox.corner2.z));

        boundingBox_ = worldBoundingBox_.Transformed(node_->GetWorldTransform().Inverse());
    }
    else
    {
        boundingBox_.Clear();
        worldBoundingBox_ = boundingBox_;
    }
}

void MagicParticleEmitter::HandleScenePostUpdate(StringHash eventType, VariantMap& eventData)
{
    MarkForUpdate();
}

}
