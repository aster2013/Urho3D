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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRNTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"

#ifdef URHO3D_ANGELSCRIPT

#include "APITemplates.h"
#include "MagicParticleEffect.h"
#include "MagicParticleEmitter.h"

#include <angelscript.h>

#ifdef _MSC_VER
#pragma warning(disable:4345)
#endif

namespace Urho3D
{

static void RegisterMagicParticleEffect(asIScriptEngine* engine)
{
    RegisterResource<MagicParticleEffect>(engine, "MagicParticleEffect");
    engine->RegisterObjectMethod("MagicParticleEffect", "uint get_numEmitters() const", asMETHOD(MagicParticleEffect, GetNumEmitters), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEffect", "int GetEmitter(uint)", asMETHOD(MagicParticleEffect, GetEmitter), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEffect", "Material@+ GetMaterial(uint, bool)", asMETHOD(MagicParticleEffect, GetMaterial), asCALL_THISCALL);
}

static void RegisterMagicParticleEmitter(asIScriptEngine* engine)
{
    RegisterDrawable<MagicParticleEmitter>(engine, "MagicParticleEmitter");
    engine->RegisterObjectMethod("MagicParticleEmitter", "void SetEffect(MagicParticleEffect@+, uint)", asMETHODPR(MagicParticleEmitter, SetEffect, (MagicParticleEffect*, int), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "void set_effect(MagicParticleEffect@+)", asMETHODPR(MagicParticleEmitter, SetEffect, (MagicParticleEffect*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "MagicParticleEffect@+ get_effect()", asMETHOD(MagicParticleEmitter, GetEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "void set_index(int)", asMETHOD(MagicParticleEmitter, SetIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "int get_index() const", asMETHOD(MagicParticleEmitter, GetIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "void Restart()", asMETHOD(MagicParticleEmitter, Restart), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "void Stop()", asMETHOD(MagicParticleEmitter, Stop), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "void Pause()", asMETHOD(MagicParticleEmitter, Pause), asCALL_THISCALL);
    engine->RegisterObjectMethod("MagicParticleEmitter", "void Resume()", asMETHOD(MagicParticleEmitter, Resume), asCALL_THISCALL);
}

void RegisterMagicParticleAPI(asIScriptEngine* engine)
{
    RegisterMagicParticleEffect(engine);
    RegisterMagicParticleEmitter(engine);
}

}

#endif // URHO3D_ANGELSCRIPT
