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

#pragma once

#include "Drawable.h"
#include "Magic.h"

namespace Urho3D
{

class IndexBuffer;
class MagicParticleEffect;
class VertexBuffer;

/// Magic particle emitter.
class URHO3D_API MagicParticleEmitter : public Drawable
{
    OBJECT(MagicParticleEmitter);

public:
    /// Construct.
    MagicParticleEmitter(Context* context);
    /// Destruct.
    virtual ~MagicParticleEmitter();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Handle enabled/disabled state change.
    virtual void OnSetEnabled();
    /// Update before octree reinsertion. is called from a worker thread.
    virtual void Update(const FrameInfo& frame);
    /// Calculate distance and prepare batches for rendering. May be called from worker thread(s), possibly re-entrantly.
    virtual void UpdateBatches(const FrameInfo& frame);
    /// Prepare geometry for rendering. Called from a worker thread if possible (no GPU update.)
    virtual void UpdateGeometry(const FrameInfo& frame);
    /// Return whether a geometry update is necessary, and if it can happen in a worker thread.
    virtual UpdateGeometryType GetUpdateGeometryType();

    /// Set effect and emitter index.
    void SetEffect(MagicParticleEffect* effect, int index);
    /// Set effect.
    void SetEffect(MagicParticleEffect* effect);
    /// Set emitter index.
    void SetIndex(int index);
    /// Restart.
    void Restart();
    /// Stop.
    void Stop();
    /// Pause.
    void Pause();
    /// Resume.
    void Resume();

    /// Return effect.
    MagicParticleEffect* GetEffect() const;
    /// Return emitter index.
    int GetIndex() const { return index_; }

    /// Set effect attribute.
    void SetEffectAttr(ResourceRef value);
    /// Return effect attribute.
    ResourceRef GetEffectAttr() const;

private:
    /// Handle node being assigned.
    virtual void OnNodeSet(Node* node);
    /// Recalculate the world-space bounding box.
    virtual void OnWorldBoundingBoxUpdate();
    /// Handle scene post update.
    void HandleScenePostUpdate(StringHash eventType, VariantMap& eventData);

    /// Magic particle effect.
    SharedPtr<MagicParticleEffect> effect_;
    /// Emitter index.
    int index_;
    /// Emitter instance.
    HM_EMITTER magicEmitter_;
    /// Index buffer.
    SharedPtr<IndexBuffer> indexBuffer_;
    /// Vertex buffer.
    SharedPtr<VertexBuffer> vertexBuffer_;
    /// Geometries.
    Vector<SharedPtr<Geometry> > geometries_;
    /// Number of particles for each geometries.
    PODVector<unsigned> numParticles_;
    /// Particles.
    PODVector<MAGIC_PARTICLE_VERTEXES> particles_;
};

}
