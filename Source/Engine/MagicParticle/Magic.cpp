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
#include "Log.h"
#include "Magic.h"

#include "SDL.h"

#define FUNCTION(Function) T_##Function Function = 0

FUNCTION(Magic_GetVersion);

#ifdef MAGIC_3D
FUNCTION(Magic_GetCamera);
FUNCTION(Magic_SetCamera);
#endif
FUNCTION(Magic_GetAxis);
FUNCTION(Magic_SetAxis);
FUNCTION(Magic_UTF8to16);
FUNCTION(Magic_UTF8to32);
FUNCTION(Magic_UTF16to8);
FUNCTION(Magic_UTF16to32);
FUNCTION(Magic_UTF32to8);
FUNCTION(Magic_UTF32to16);
FUNCTION(MAGIC_ACTION_Identity);

FUNCTION(Magic_OpenFile);
FUNCTION(Magic_OpenFileInMemory);
FUNCTION(Magic_OpenStream);
FUNCTION(Magic_CloseFile);
FUNCTION(Magic_CloseAllFiles);
FUNCTION(Magic_GetCurrentFolder);
FUNCTION(Magic_SetCurrentFolder);
FUNCTION(Magic_FindFirst);
FUNCTION(Magic_FindNext);
FUNCTION(Magic_GetFileName);
FUNCTION(Magic_HasTextures);
FUNCTION(Magic_GetStaticAtlasCount);
FUNCTION(Magic_GetStaticAtlas);

FUNCTION(Magic_LoadEmitter);
FUNCTION(Magic_DuplicateEmitter);
FUNCTION(Magic_UnloadEmitter);
FUNCTION(Magic_UnloadAllEmitters);
FUNCTION(Magic_Update);
FUNCTION(Magic_Stop);
FUNCTION(Magic_Restart);
FUNCTION(Magic_IsInterrupt);
FUNCTION(Magic_SetInterrupt);
FUNCTION(Magic_GetUpdateTime);
FUNCTION(Magic_GetPosition);
FUNCTION(Magic_SetPosition);
FUNCTION(Magic_GetDuration);
FUNCTION(Magic_GetInterval1);
FUNCTION(Magic_SetInterval1);
FUNCTION(Magic_GetInterval2);
FUNCTION(Magic_SetInterval2);
FUNCTION(Magic_InInterval);
FUNCTION(Magic_EmitterToInterval1);
FUNCTION(Magic_IsInterval1);
FUNCTION(Magic_LoadArrayFromFile);
FUNCTION(Magic_SaveArrayToFile);
FUNCTION(Magic_IsInterpolationMode);
FUNCTION(Magic_SetInterpolationMode);
FUNCTION(Magic_IsRandomMode);
FUNCTION(Magic_SetRandomMode);
FUNCTION(Magic_GetLoopMode);
FUNCTION(Magic_SetLoopMode);
FUNCTION(Magic_GetColorMode);
FUNCTION(Magic_SetColorMode);
FUNCTION(Magic_GetTint);
FUNCTION(Magic_SetTint);
FUNCTION(Magic_GetTintStrength);
FUNCTION(Magic_SetTintStrength);
FUNCTION(Magic_GetScale);
FUNCTION(Magic_SetScale);
FUNCTION(Magic_SetData);
FUNCTION(Magic_GetData);

FUNCTION(Magic_GetBirthPlace);

FUNCTION(Magic_SetBirthPlace);
FUNCTION(Magic_GetEmitterName);
FUNCTION(Magic_GetEmitterType);
FUNCTION(Magic_GetEmitterID);
FUNCTION(Magic_GetUpdateSpeed);
FUNCTION(Magic_GetBackgroundRect);

#ifdef MAGIC_3D
FUNCTION(Magic_Is3d);
FUNCTION(Magic_GetView);
#else
FUNCTION(Magic_CorrectEmitterPosition);
#endif

FUNCTION(Magic_GetEmitterPosition);
FUNCTION(Magic_SetEmitterPosition);
FUNCTION(Magic_SetEmitterPositionWithTail);
FUNCTION(Magic_GetEmitterPositionMode);
FUNCTION(Magic_SetEmitterPositionMode);
FUNCTION(Magic_MoveEmitterParticles);
FUNCTION(Magic_GetEmitterDirection);
FUNCTION(Magic_SetEmitterDirection);
FUNCTION(Magic_GetEmitterDirectionMode);
FUNCTION(Magic_SetEmitterDirectionMode);
FUNCTION(Magic_RotateEmitterParticles);
FUNCTION(Magic_IsFolder);
FUNCTION(Magic_GetEmitterCount);
FUNCTION(Magic_GetEmitter);
FUNCTION(Magic_CreateFirstRenderedParticlesList);
FUNCTION(Magic_CreateNextRenderedParticlesList);
FUNCTION(Magic_GetNextParticleVertexes);
FUNCTION(Magic_GetSortingMode);
FUNCTION(Magic_SetSortingMode);
FUNCTION(Magic_GetBBox);
FUNCTION(Magic_GetBBoxPeriod);
FUNCTION(Magic_SetBBoxPeriod);
FUNCTION(Magic_RecalcBBox);
FUNCTION(Magic_GetEmitterVariableCount);
FUNCTION(Magic_GetEmitterVariable);

FUNCTION(Magic_GetParticlesTypeName);
FUNCTION(Magic_GetParticlesTypeCount);
FUNCTION(Magic_LockParticlesType);
FUNCTION(Magic_UnlockParticlesType);
FUNCTION(Magic_GetTextureCount);
FUNCTION(Magic_GetTexture);
FUNCTION(Magic_SetTextureUV);
FUNCTION(Magic_GetTextureID);
FUNCTION(Magic_SetTextureID);
FUNCTION(Magic_IsIntensive);

#ifdef MAGIC_3D
FUNCTION(Magic_GetOrientation);
FUNCTION(Magic_SetOrientation);
#endif

FUNCTION(Magic_GetTailProperties);
FUNCTION(Magic_SetTailProperties);
FUNCTION(Magic_GetNextParticle);
FUNCTION(Magic_MoveParticle);
FUNCTION(Magic_RotateParticle);
FUNCTION(Magic_GetParticlesTypeVariableCount);
FUNCTION(Magic_GetParticlesTypeVariable);
FUNCTION(Magic_GetActionCount);
FUNCTION(Magic_GetAction);
FUNCTION(Magic_CreateAction);
FUNCTION(Magic_DestroyAction);
FUNCTION(Magic_GetAttachedPhysicObjectsCount);
FUNCTION(Magic_GetAttachedPhysicObjects);

FUNCTION(Magic_SetCleverModeForAtlas);
FUNCTION(Magic_IsCleverModeForAtlas);
FUNCTION(Magic_GetNextAtlasChange);
FUNCTION(Magic_CreateAtlases);
FUNCTION(Magic_CreateAtlasesForEmitters);
FUNCTION(Magic_SetStartingScaleForAtlas);
FUNCTION(Magic_GetStartingScaleForAtlas);
FUNCTION(Magic_GetAtlasCount);
FUNCTION(Magic_GetAtlas);

FUNCTION(Magic_IsDiagramEnabled);
FUNCTION(Magic_GetDiagramFactor);
FUNCTION(Magic_SetDiagramFactor);
FUNCTION(Magic_GetDiagramEmitterFactor);
FUNCTION(Magic_SetDiagramEmitterFactor);
FUNCTION(Magic_GetDiagramAddition);
FUNCTION(Magic_SetDiagramAddition);
FUNCTION(Magic_GetDiagramEmitterAddition);
FUNCTION(Magic_SetDiagramEmitterAddition);
FUNCTION(Magic_ChangeImage);
FUNCTION(Magic_ChangeModel);

FUNCTION(Magic_CreateKey);
FUNCTION(Magic_DeleteKey);
FUNCTION(Magic_GetKeyCount);
FUNCTION(Magic_GetKey);
FUNCTION(Magic_SetKey);

FUNCTION(Magic_CreateObstacle);
FUNCTION(Magic_GetObstacleData);
FUNCTION(Magic_SetObstacleData);
FUNCTION(Magic_GetObstaclePosition);
FUNCTION(Magic_SetObstaclePosition);
FUNCTION(Magic_CreateWind);
FUNCTION(Magic_GetWindData);
FUNCTION(Magic_SetWindData);
FUNCTION(Magic_DestroyPhysicObject);
FUNCTION(Magic_DestroyAllPhysicObjects);
FUNCTION(Magic_DuplicatePhysicObject);

FUNCTION(Magic_GetNextEvent);
FUNCTION(Magic_ParticleGetData);
FUNCTION(Magic_ParticleSetData);
FUNCTION(Magic_ParticleGetPosition);
FUNCTION(Magic_ParticleSetPosition);
FUNCTION(Magic_ParticleGetProperty);
FUNCTION(Magic_ParticleSetProperty);
FUNCTION(Magic_ParticleGetProperties);
FUNCTION(Magic_ParticleSetProperties);
FUNCTION(Magic_ParticleGetRadius);
FUNCTION(Magic_ParticleDetaching);
FUNCTION(Magic_ParticleDestruction);

FUNCTION(Magic_StreamOpenFile);
FUNCTION(Magic_StreamOpenMemory);
FUNCTION(Magic_StreamClose);
FUNCTION(Magic_StreamCloseAll);
FUNCTION(Magic_StreamGetLength);
FUNCTION(Magic_StreamGetPosition);
FUNCTION(Magic_StreamSetPosition);
FUNCTION(Magic_StreamGetMode);
FUNCTION(Magic_StreamSetMode);
FUNCTION(Magic_StreamGetFileName);
FUNCTION(Magic_StreamRead);
FUNCTION(Magic_StreamWrite);
FUNCTION(Magic_LoadArrayFromStream);
FUNCTION(Magic_SaveArrayToStream);
FUNCTION(Magic_EmitterToInterval1_Stream);

FUNCTION(Magic_DestroyAll);
FUNCTION(Magic_SetEmitterPositionWithAttachedPhysicObjects);

bool InitMagic()
{
#if defined(ANDROID)
    void* magic3d = SDL_LoadObject("Data/MagicParticle/Android/libamagic3d.so");
#elif defined(WIN32)
    void* magic3d = SDL_LoadObject("Data/MagicParticle/Windows/magic3d.dll");
#elif defined(__APPLE__)
    void* magic3d = SDL_LoadObject("Data/MagicParticle/Mac/magic3d.dylib");
#elif defined(__linux__)
    void* magic3d = SDL_LoadObject("Data/MagicParticle/Linux/libumagic3d.so");
#else
    void* magic3d = 0;
#endif

    if (!magic3d)
    {
        LOGERROR("Could not load magic3d shared library, may be it not support your platform");
        return false;
    }

#define LOAD_FUNCTION(Function) Function = (T_##Function)SDL_LoadFunction(magic3d, #Function); if (!Function) return false

    LOAD_FUNCTION(Magic_GetVersion);

#ifdef MAGIC_3D
    LOAD_FUNCTION(Magic_GetCamera);
    LOAD_FUNCTION(Magic_SetCamera);
#endif
    LOAD_FUNCTION(Magic_GetAxis);
    LOAD_FUNCTION(Magic_SetAxis);
    LOAD_FUNCTION(Magic_UTF8to16);
    LOAD_FUNCTION(Magic_UTF8to32);
    LOAD_FUNCTION(Magic_UTF16to8);
    LOAD_FUNCTION(Magic_UTF16to32);
    LOAD_FUNCTION(Magic_UTF32to8);
    LOAD_FUNCTION(Magic_UTF32to16);
    LOAD_FUNCTION(MAGIC_ACTION_Identity);

    LOAD_FUNCTION(Magic_OpenFile);
    LOAD_FUNCTION(Magic_OpenFileInMemory);
    LOAD_FUNCTION(Magic_OpenStream);
    LOAD_FUNCTION(Magic_CloseFile);
    LOAD_FUNCTION(Magic_CloseAllFiles);
    LOAD_FUNCTION(Magic_GetCurrentFolder);
    LOAD_FUNCTION(Magic_SetCurrentFolder);
    LOAD_FUNCTION(Magic_FindFirst);
    LOAD_FUNCTION(Magic_FindNext);
    LOAD_FUNCTION(Magic_GetFileName);
    LOAD_FUNCTION(Magic_HasTextures);
    LOAD_FUNCTION(Magic_GetStaticAtlasCount);
    LOAD_FUNCTION(Magic_GetStaticAtlas);

    LOAD_FUNCTION(Magic_LoadEmitter);
    LOAD_FUNCTION(Magic_DuplicateEmitter);
    LOAD_FUNCTION(Magic_UnloadEmitter);
    LOAD_FUNCTION(Magic_UnloadAllEmitters);
    LOAD_FUNCTION(Magic_Update);
    LOAD_FUNCTION(Magic_Stop);
    LOAD_FUNCTION(Magic_Restart);
    LOAD_FUNCTION(Magic_IsInterrupt);
    LOAD_FUNCTION(Magic_SetInterrupt);
    LOAD_FUNCTION(Magic_GetUpdateTime);
    LOAD_FUNCTION(Magic_GetPosition);
    LOAD_FUNCTION(Magic_SetPosition);
    LOAD_FUNCTION(Magic_GetDuration);
    LOAD_FUNCTION(Magic_GetInterval1);
    LOAD_FUNCTION(Magic_SetInterval1);
    LOAD_FUNCTION(Magic_GetInterval2);
    LOAD_FUNCTION(Magic_SetInterval2);
    LOAD_FUNCTION(Magic_InInterval);
    LOAD_FUNCTION(Magic_EmitterToInterval1);
    LOAD_FUNCTION(Magic_IsInterval1);
    LOAD_FUNCTION(Magic_LoadArrayFromFile);
    LOAD_FUNCTION(Magic_SaveArrayToFile);
    LOAD_FUNCTION(Magic_IsInterpolationMode);
    LOAD_FUNCTION(Magic_SetInterpolationMode);
    LOAD_FUNCTION(Magic_IsRandomMode);
    LOAD_FUNCTION(Magic_SetRandomMode);
    LOAD_FUNCTION(Magic_GetLoopMode);
    LOAD_FUNCTION(Magic_SetLoopMode);
    LOAD_FUNCTION(Magic_GetColorMode);
    LOAD_FUNCTION(Magic_SetColorMode);
    LOAD_FUNCTION(Magic_GetTint);
    LOAD_FUNCTION(Magic_SetTint);
    LOAD_FUNCTION(Magic_GetTintStrength);
    LOAD_FUNCTION(Magic_SetTintStrength);
    LOAD_FUNCTION(Magic_GetScale);
    LOAD_FUNCTION(Magic_SetScale);
    LOAD_FUNCTION(Magic_SetData);
    LOAD_FUNCTION(Magic_GetData);

    LOAD_FUNCTION(Magic_GetBirthPlace);

    LOAD_FUNCTION(Magic_SetBirthPlace);
    LOAD_FUNCTION(Magic_GetEmitterName);
    LOAD_FUNCTION(Magic_GetEmitterType);
    LOAD_FUNCTION(Magic_GetEmitterID);
    LOAD_FUNCTION(Magic_GetUpdateSpeed);
    LOAD_FUNCTION(Magic_GetBackgroundRect);

#ifdef MAGIC_3D
    LOAD_FUNCTION(Magic_Is3d);
    LOAD_FUNCTION(Magic_GetView);
#else
    LOAD_FUNCTION(Magic_CorrectEmitterPosition);
#endif

    LOAD_FUNCTION(Magic_GetEmitterPosition);
    LOAD_FUNCTION(Magic_SetEmitterPosition);
    LOAD_FUNCTION(Magic_SetEmitterPositionWithTail);
    LOAD_FUNCTION(Magic_GetEmitterPositionMode);
    LOAD_FUNCTION(Magic_SetEmitterPositionMode);
    LOAD_FUNCTION(Magic_MoveEmitterParticles);
    LOAD_FUNCTION(Magic_GetEmitterDirection);
    LOAD_FUNCTION(Magic_SetEmitterDirection);
    LOAD_FUNCTION(Magic_GetEmitterDirectionMode);
    LOAD_FUNCTION(Magic_SetEmitterDirectionMode);
    LOAD_FUNCTION(Magic_RotateEmitterParticles);
    LOAD_FUNCTION(Magic_IsFolder);
    LOAD_FUNCTION(Magic_GetEmitterCount);
    LOAD_FUNCTION(Magic_GetEmitter);
    LOAD_FUNCTION(Magic_CreateFirstRenderedParticlesList);
    LOAD_FUNCTION(Magic_CreateNextRenderedParticlesList);
    LOAD_FUNCTION(Magic_GetNextParticleVertexes);
    LOAD_FUNCTION(Magic_GetSortingMode);
    LOAD_FUNCTION(Magic_SetSortingMode);
    LOAD_FUNCTION(Magic_GetBBox);
    LOAD_FUNCTION(Magic_GetBBoxPeriod);
    LOAD_FUNCTION(Magic_SetBBoxPeriod);
    LOAD_FUNCTION(Magic_RecalcBBox);
    LOAD_FUNCTION(Magic_GetEmitterVariableCount);
    LOAD_FUNCTION(Magic_GetEmitterVariable);

    LOAD_FUNCTION(Magic_GetParticlesTypeName);
    LOAD_FUNCTION(Magic_GetParticlesTypeCount);
    LOAD_FUNCTION(Magic_LockParticlesType);
    LOAD_FUNCTION(Magic_UnlockParticlesType);
    LOAD_FUNCTION(Magic_GetTextureCount);
    LOAD_FUNCTION(Magic_GetTexture);
    LOAD_FUNCTION(Magic_SetTextureUV);
    LOAD_FUNCTION(Magic_GetTextureID);
    LOAD_FUNCTION(Magic_SetTextureID);
    LOAD_FUNCTION(Magic_IsIntensive);

#ifdef MAGIC_3D
    LOAD_FUNCTION(Magic_GetOrientation);
    LOAD_FUNCTION(Magic_SetOrientation);
#endif

    LOAD_FUNCTION(Magic_GetTailProperties);
    LOAD_FUNCTION(Magic_SetTailProperties);
    LOAD_FUNCTION(Magic_GetNextParticle);
    LOAD_FUNCTION(Magic_MoveParticle);
    LOAD_FUNCTION(Magic_RotateParticle);
    LOAD_FUNCTION(Magic_GetParticlesTypeVariableCount);
    LOAD_FUNCTION(Magic_GetParticlesTypeVariable);
    LOAD_FUNCTION(Magic_GetActionCount);
    LOAD_FUNCTION(Magic_GetAction);
    LOAD_FUNCTION(Magic_CreateAction);
    LOAD_FUNCTION(Magic_DestroyAction);
    LOAD_FUNCTION(Magic_GetAttachedPhysicObjectsCount);
    LOAD_FUNCTION(Magic_GetAttachedPhysicObjects);

    LOAD_FUNCTION(Magic_SetCleverModeForAtlas);
    LOAD_FUNCTION(Magic_IsCleverModeForAtlas);
    LOAD_FUNCTION(Magic_GetNextAtlasChange);
    LOAD_FUNCTION(Magic_CreateAtlases);
    LOAD_FUNCTION(Magic_CreateAtlasesForEmitters);
    LOAD_FUNCTION(Magic_SetStartingScaleForAtlas);
    LOAD_FUNCTION(Magic_GetStartingScaleForAtlas);
    LOAD_FUNCTION(Magic_GetAtlasCount);
    LOAD_FUNCTION(Magic_GetAtlas);

    LOAD_FUNCTION(Magic_IsDiagramEnabled);
    LOAD_FUNCTION(Magic_GetDiagramFactor);
    LOAD_FUNCTION(Magic_SetDiagramFactor);
    LOAD_FUNCTION(Magic_GetDiagramEmitterFactor);
    LOAD_FUNCTION(Magic_SetDiagramEmitterFactor);
    LOAD_FUNCTION(Magic_GetDiagramAddition);
    LOAD_FUNCTION(Magic_SetDiagramAddition);
    LOAD_FUNCTION(Magic_GetDiagramEmitterAddition);
    LOAD_FUNCTION(Magic_SetDiagramEmitterAddition);
    LOAD_FUNCTION(Magic_ChangeImage);
    LOAD_FUNCTION(Magic_ChangeModel);

    LOAD_FUNCTION(Magic_CreateKey);
    LOAD_FUNCTION(Magic_DeleteKey);
    LOAD_FUNCTION(Magic_GetKeyCount);
    LOAD_FUNCTION(Magic_GetKey);
    LOAD_FUNCTION(Magic_SetKey);

    LOAD_FUNCTION(Magic_CreateObstacle);
    LOAD_FUNCTION(Magic_GetObstacleData);
    LOAD_FUNCTION(Magic_SetObstacleData);
    LOAD_FUNCTION(Magic_GetObstaclePosition);
    LOAD_FUNCTION(Magic_SetObstaclePosition);
    LOAD_FUNCTION(Magic_CreateWind);
    LOAD_FUNCTION(Magic_GetWindData);
    LOAD_FUNCTION(Magic_SetWindData);
    LOAD_FUNCTION(Magic_DestroyPhysicObject);
    LOAD_FUNCTION(Magic_DestroyAllPhysicObjects);
    LOAD_FUNCTION(Magic_DuplicatePhysicObject);

    LOAD_FUNCTION(Magic_GetNextEvent);
    LOAD_FUNCTION(Magic_ParticleGetData);
    LOAD_FUNCTION(Magic_ParticleSetData);
    LOAD_FUNCTION(Magic_ParticleGetPosition);
    LOAD_FUNCTION(Magic_ParticleSetPosition);
    LOAD_FUNCTION(Magic_ParticleGetProperty);
    LOAD_FUNCTION(Magic_ParticleSetProperty);
    LOAD_FUNCTION(Magic_ParticleGetProperties);
    LOAD_FUNCTION(Magic_ParticleSetProperties);
    LOAD_FUNCTION(Magic_ParticleGetRadius);
    LOAD_FUNCTION(Magic_ParticleDetaching);
    LOAD_FUNCTION(Magic_ParticleDestruction);

    LOAD_FUNCTION(Magic_StreamOpenFile);
    LOAD_FUNCTION(Magic_StreamOpenMemory);
    LOAD_FUNCTION(Magic_StreamClose);
    LOAD_FUNCTION(Magic_StreamCloseAll);
    LOAD_FUNCTION(Magic_StreamGetLength);
    LOAD_FUNCTION(Magic_StreamGetPosition);
    LOAD_FUNCTION(Magic_StreamSetPosition);
    LOAD_FUNCTION(Magic_StreamGetMode);
    LOAD_FUNCTION(Magic_StreamSetMode);
    LOAD_FUNCTION(Magic_StreamGetFileName);
    LOAD_FUNCTION(Magic_StreamRead);
    LOAD_FUNCTION(Magic_StreamWrite);
    LOAD_FUNCTION(Magic_LoadArrayFromStream);
    LOAD_FUNCTION(Magic_SaveArrayToStream);
    LOAD_FUNCTION(Magic_EmitterToInterval1_Stream);


    LOAD_FUNCTION(Magic_DestroyAll);
    LOAD_FUNCTION(Magic_SetEmitterPositionWithAttachedPhysicObjects);

    return true;
}