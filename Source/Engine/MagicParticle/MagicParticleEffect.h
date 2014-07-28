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

#include "ArrayPtr.h"
#include "Magic.h"
#include "Resource.h"

namespace Urho3D
{

class Material;
class Texture2D;

/// Magic Particle effect (ptc file).
class URHO3D_API MagicParticleEffect : public Resource
{
    OBJECT(MagicParticleEffect);

public:
    /// Construct.
    MagicParticleEffect(Context* context);
    /// Destruct.
    virtual ~MagicParticleEffect();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Load resource from stream. May be called from a worker thread. Return true if successful.
    virtual bool BeginLoad(Deserializer& source);
    /// Finish resource loading. Always called from the main thread. Return true if successful.
    virtual bool EndLoad();

    /// Return number of emitters.
    unsigned GetNumEmitters() const;
    /// Return emitter at index.
    HM_EMITTER GetEmitter(unsigned index) const;
    /// Return material by texture index and add mode.
    Material* GetMaterial(unsigned index, bool addMode);

private:
    /// Load folder.
    void LoadFolder(HM_FILE file, const char* path);
    /// Load emitter.
    void LoadEmitter(HM_FILE file, const char* path);
    /// Load atlas.
    bool CreateAtlases(HM_FILE file);
    /// Create texture.
    bool CreateTexture(const MAGIC_CHANGE_ATLAS& atlas);
    /// Load atlas.
    bool LoadAtlas(const MAGIC_CHANGE_ATLAS& atlas);
    /// Load static atlas.
    bool LoadStaticAtlas(HM_FILE file);

    /// File data size.
    unsigned dataSize_;
    /// File data.
    SharedArrayPtr<char> data_;
    /// Emitters.
    PODVector<HM_EMITTER> emitters_;
    /// Textures.
    Vector<SharedPtr<Texture2D> > textures_;
    /// Materials.
    Vector<SharedPtr<Material> > materials_;
};

}
