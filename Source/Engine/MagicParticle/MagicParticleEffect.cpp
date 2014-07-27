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
#include "Context.h"
#include "Deserializer.h"
#include "File.h"
#include "FileSystem.h"
#include "Graphics.h"
#include "Image.h"
#include "Log.h"
#include "MagicParticleEffect.h"
#include "Material.h"
#include "MemoryBuffer.h"
#include "ResourceCache.h"
#include "Technique.h"
#include "Texture2D.h"

#include "DebugNew.h"

extern T_Magic_CloseFile Magic_CloseFile;
extern T_Magic_CreateAtlasesForEmitters Magic_CreateAtlasesForEmitters;
extern T_Magic_FindFirst Magic_FindFirst;
extern T_Magic_FindNext Magic_FindNext;
extern T_Magic_GetNextAtlasChange Magic_GetNextAtlasChange;
extern T_Magic_GetStaticAtlas Magic_GetStaticAtlas;
extern T_Magic_GetStaticAtlasCount Magic_GetStaticAtlasCount;
extern T_Magic_HasTextures Magic_HasTextures;
extern T_Magic_LoadEmitter Magic_LoadEmitter;
extern T_Magic_OpenFileInMemory Magic_OpenFileInMemory;
extern T_Magic_SetCleverModeForAtlas Magic_SetCleverModeForAtlas;
extern T_Magic_SetCurrentFolder Magic_SetCurrentFolder;
extern T_Magic_SetInterpolationMode Magic_SetInterpolationMode;
extern T_Magic_SetStartingScaleForAtlas Magic_SetStartingScaleForAtlas;
extern T_Magic_Stop Magic_Stop;
extern T_Magic_UnloadEmitter Magic_UnloadEmitter;

namespace Urho3D
{

MagicParticleEffect::MagicParticleEffect(Context* context) :
    Resource(context)
{
}

MagicParticleEffect::~MagicParticleEffect()
{
    for (unsigned i = 0; i < emitters_.Size(); ++i)
        Magic_UnloadEmitter(emitters_[i]);
}

void MagicParticleEffect::RegisterObject(Context* context)
{
    context->RegisterFactory<MagicParticleEffect>();

    Magic_SetCleverModeForAtlas(true);
    Magic_SetStartingScaleForAtlas(1.0f);
}

bool MagicParticleEffect::Load(Deserializer& source)
{
    for (unsigned i = 0; i < emitters_.Size(); ++i)
        Magic_UnloadEmitter(emitters_[i]);

    emitters_.Clear();

    textures_.Clear();
    materials_.Clear();

    unsigned size = source.GetSize();
    SharedArrayPtr<char> data(new char[size]);
    if (source.Read(data, size) != size)
    {
        LOGERROR("Could not load data");
        return false;
    }

    HM_FILE file = Magic_OpenFileInMemory(data);
    if (file <= 0)
    {
        LOGERROR("Could not open file");
        return false;
    }

    LoadFolder(file, "");

    bool success = true;
    if (Magic_HasTextures(file))
        success = CreateAtlases(file);
    else
        success =LoadStaticAtlas(file);

    Magic_CloseFile(file);

    materials_.Resize(textures_.Size() * 2);
    SetMemoryUse(GetMemoryUse() + size);

    return success;
}   

unsigned MagicParticleEffect::GetNumEmitters() const
{
    return emitters_.Size();
}

HM_EMITTER MagicParticleEffect::GetEmitter(unsigned index) const
{
    if (index >= emitters_.Size())
        return 0;

    return emitters_[index];
}

Material* MagicParticleEffect::GetMaterial(unsigned index, bool addMode)
{
    if (index >= textures_.Size())
        return 0;

    SharedPtr<Texture2D> texture = textures_[index];
    if (!texture)
    {
        LOGERROR("Invalid texture index");
        return 0;
    }

    unsigned matIndex = index * 2 + (addMode ? 1 : 0);
    if (materials_[matIndex])
        return materials_[matIndex];

    SharedPtr<Material> material(new Material(context_));

    Technique* technique = new Technique(context_);
    Pass* pass = technique->CreatePass(PASS_ALPHA);
    pass->SetBlendMode(addMode ? BLEND_ADDALPHA : BLEND_ALPHA);
    pass->SetDepthWrite(false);

    pass->SetVertexShader("Unlit");
    pass->SetVertexShaderDefines("VERTEXCOLOR");
    pass->SetPixelShader("Unlit");
    pass->SetPixelShaderDefines("DIFFMAP VERTEXCOLOR");

    material->SetTechnique(0, technique);
    material->SetCullMode(CULL_CCW);
    material->SetTexture(TU_DIFFUSE, texture);

    materials_[matIndex] = material;

    return material;
}

void MagicParticleEffect::LoadFolder(HM_FILE file, const char* path)
{
    Magic_SetCurrentFolder(file, path);

    MAGIC_FIND_DATA find;
    const char* name = Magic_FindFirst(file, &find, MAGIC_FOLDER | MAGIC_EMITTER);
    while (name)
    {
        if (find.animate)
            LoadEmitter(file, name);
        else
            LoadFolder(file, name);

        name = Magic_FindNext(file, &find);
    }

    Magic_SetCurrentFolder(file, "..");
}

void MagicParticleEffect::LoadEmitter(HM_FILE file, const char* path)
{
    HM_EMITTER emitter = Magic_LoadEmitter(file, path);
    if (emitter)
    {
        Magic_SetInterpolationMode(emitter, true);
        Magic_Stop(emitter);
        emitters_.Push(emitter);
    }
}

bool MagicParticleEffect::CreateAtlases(HM_FILE file)
{
    Magic_CreateAtlasesForEmitters(1024, 1024, emitters_.Size(), &emitters_[0], 1, 0.1f);

    MAGIC_CHANGE_ATLAS atlas;
    while (Magic_GetNextAtlasChange(&atlas) ==  MAGIC_SUCCESS)
    {
        switch (atlas.type)
        {
        case MAGIC_CHANGE_ATLAS_CREATE:
            if (!CreateTexture(atlas))
                return false;
            break;

        case MAGIC_CHANGE_ATLAS_DELETE:
            assert("Not implement now!");
            break;

        case MAGIC_CHANGE_ATLAS_LOAD:
            if (!LoadAtlas(atlas))
                return false;
            break;

        case MAGIC_CHANGE_ATLAS_CLEAN:
            assert("Not implement now!");
            break;

        default:
            break;
        }
    }

    return true;
}

bool MagicParticleEffect::CreateTexture(const MAGIC_CHANGE_ATLAS& atlas)
{
    SharedPtr<Texture2D> texture(new Texture2D(context_));
    texture->SetNumLevels(1);

    texture->SetSize(atlas.width, atlas.height, Graphics::GetRGBAFormat());
    
    SharedArrayPtr<unsigned char> data(new unsigned char[atlas.width * atlas.height * 4]);
    memset(&data[0], 0, atlas.width * atlas.height * 4);
    texture->SetData(0, 0, 0, atlas.width, atlas.height, data);

    if (textures_.Size() < (unsigned)atlas.index + 1)
        textures_.Resize(atlas.index + 1);

    textures_[atlas.index] = texture;

    return true;
}

bool MagicParticleEffect::LoadAtlas(const MAGIC_CHANGE_ATLAS& atlas)
{
    SharedPtr<Texture2D> texture = textures_[atlas.index];
    if (!texture)
        return false;

    Image image(context_);
    if (atlas.data)
    {
        // Load image from memory
        MemoryBuffer buffer(atlas.data, atlas.length);
        if (!image.Load(buffer))
        {
            LOGERROR("Could not load image from memory");
            return false;
        }
    }
    else
    {
        // Load image from file
        String imageFilePath;
        String parentPath = GetParentPath(GetName());
        if (parentPath.Empty())
            imageFilePath = atlas.file;
        else
            imageFilePath = parentPath + "/" + atlas.file;

        File file(context_);
        if (!file.Open(imageFilePath))
        {
            LOGERROR("Could not open file " + imageFilePath);
            return false;
        }

        if (!image.Load(file))
        {
            LOGERROR("Could not load image " + imageFilePath);
            return false;
        }
    }

    if (atlas.width != image.GetWidth() || atlas.height != image.GetHeight())
    {
        LOGERROR("Atlas scale not support now");
        return false;
    }

    return texture->SetData(0, atlas.x, atlas.y, atlas.width, atlas.height, image.GetData());
}

bool MagicParticleEffect::LoadStaticAtlas(HM_FILE file)
{
    int atlasCount = Magic_GetStaticAtlasCount(file);
    if (atlasCount == 0)
        return true;
    
    ResourceCache* cache = GetSubsystem<ResourceCache>();    
    String parentPath = GetParentPath(GetName());

    MAGIC_STATIC_ATLAS atlas;
    for (int i = 0; i < atlasCount; ++i)
    {
        Magic_GetStaticAtlas(file, i, &atlas);

        String textureFilePath;
        if (parentPath.Empty())
            textureFilePath = atlas.file;
        else
            textureFilePath = parentPath + "/" + atlas.file;

        SharedPtr<Texture2D> texture(cache->GetResource<Texture2D>(textureFilePath));
        if (!texture)
        {
            LOGERROR(String("Could not load texture ") + textureFilePath);
            return false;
        }

        textures_.Push(texture);
    }

    return true;
}

}
