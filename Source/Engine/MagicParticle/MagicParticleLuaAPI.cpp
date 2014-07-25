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

#ifdef URHO3D_LUA

#include "tolua++.h"
#include "../LuaScript/ToluaUtils.h"

/* Exported function */
TOLUA_API int tolua_MagicParticleLuaAPI_open (lua_State* tolua_S);

#include "MagicParticleEffect.h"
#include "MagicParticleEmitter.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Resource");
    tolua_usertype(tolua_S,"Material");
    tolua_usertype(tolua_S,"MagicParticleEmitter");
    tolua_usertype(tolua_S,"Drawable");
    tolua_usertype(tolua_S,"MagicParticleEffect");
}

/* method: GetNumEmitters of class  MagicParticleEffect */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEffect_GetNumEmitters00
static int tolua_MagicParticleLuaAPI_MagicParticleEffect_GetNumEmitters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const MagicParticleEffect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const MagicParticleEffect* self = (const MagicParticleEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumEmitters'", NULL);
#endif
        {
            unsigned tolua_ret = (unsigned)  self->GetNumEmitters();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'GetNumEmitters'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEmitter of class  MagicParticleEffect */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEffect_GetEmitter00
static int tolua_MagicParticleLuaAPI_MagicParticleEffect_GetEmitter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const MagicParticleEffect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const MagicParticleEffect* self = (const MagicParticleEffect*)  tolua_tousertype(tolua_S,1,0);
        unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEmitter'", NULL);
#endif
        {
            int tolua_ret = (int)  self->GetEmitter(index);
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'GetEmitter'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterial of class  MagicParticleEffect */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEffect_GetMaterial00
static int tolua_MagicParticleLuaAPI_MagicParticleEffect_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEffect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEffect* self = (MagicParticleEffect*)  tolua_tousertype(tolua_S,1,0);
        unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
        bool addMode = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaterial'", NULL);
#endif
        {
            Material* tolua_ret = (Material*)  self->GetMaterial(index,addMode);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"Material");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'GetMaterial'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: numEmitters of class  MagicParticleEffect */
#ifndef TOLUA_DISABLE_tolua_get_MagicParticleEffect_numEmitters
static int tolua_get_MagicParticleEffect_numEmitters(lua_State* tolua_S)
{
    MagicParticleEffect* self = (MagicParticleEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'numEmitters'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->GetNumEmitters());
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEffect of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"MagicParticleEffect",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
        MagicParticleEffect* effect = ((MagicParticleEffect*)  tolua_tousertype(tolua_S,2,0));
        int index = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEffect'", NULL);
#endif
        {
            self->SetEffect(effect,index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'SetEffect'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEffect of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect01
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"MagicParticleEffect",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
        MagicParticleEffect* effect = ((MagicParticleEffect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEffect'", NULL);
#endif
        {
            self->SetEffect(effect);
        }
    }
    return 0;
tolua_lerror:
    return tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIndex of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetIndex00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
        int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIndex'", NULL);
#endif
        {
            self->SetIndex(index);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'SetIndex'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Restart of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_Restart00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_Restart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Restart'", NULL);
#endif
        {
            self->Restart();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'Restart'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Stop of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_Stop00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'", NULL);
#endif
        {
            self->Stop();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Pause of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_Pause00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_Pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pause'", NULL);
#endif
        {
            self->Pause();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'Pause'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Resume of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_Resume00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_Resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Resume'", NULL);
#endif
        {
            self->Resume();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'Resume'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffect of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_GetEffect00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_GetEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const MagicParticleEmitter* self = (const MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffect'", NULL);
#endif
        {
            MagicParticleEffect* tolua_ret = (MagicParticleEffect*)  self->GetEffect();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"MagicParticleEffect");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'GetEffect'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndex of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_MagicParticleLuaAPI_MagicParticleEmitter_GetIndex00
static int tolua_MagicParticleLuaAPI_MagicParticleEmitter_GetIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"const MagicParticleEmitter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        const MagicParticleEmitter* self = (const MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndex'", NULL);
#endif
        {
            int tolua_ret = (int)  self->GetIndex();
            tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'GetIndex'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: effect of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_get_MagicParticleEmitter_effect_ptr
static int tolua_get_MagicParticleEmitter_effect_ptr(lua_State* tolua_S)
{
    MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'effect'",NULL);
#endif
    tolua_pushusertype(tolua_S,(void*)self->GetEffect(),"MagicParticleEffect");
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: effect of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_set_MagicParticleEmitter_effect_ptr
static int tolua_set_MagicParticleEmitter_effect_ptr(lua_State* tolua_S)
{
    MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'effect'",NULL);
    if (!tolua_isusertype(tolua_S,2,"MagicParticleEffect",0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->SetEffect(((MagicParticleEffect*)  tolua_tousertype(tolua_S,2,0)));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: index of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_get_MagicParticleEmitter_index
static int tolua_get_MagicParticleEmitter_index(lua_State* tolua_S)
{
    MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'index'",NULL);
#endif
    tolua_pushnumber(tolua_S,(lua_Number)self->GetIndex());
    return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: index of class  MagicParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_set_MagicParticleEmitter_index
static int tolua_set_MagicParticleEmitter_index(lua_State* tolua_S)
{
    MagicParticleEmitter* self = (MagicParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'index'",NULL);
    if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
    self->SetIndex(((int)  tolua_tonumber(tolua_S,2,0)));
    return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_MagicParticleLuaAPI_open (lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_types(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    tolua_cclass(tolua_S,"MagicParticleEffect","MagicParticleEffect","Resource",NULL);
    tolua_beginmodule(tolua_S,"MagicParticleEffect");
    tolua_function(tolua_S,"GetNumEmitters",tolua_MagicParticleLuaAPI_MagicParticleEffect_GetNumEmitters00);
    tolua_function(tolua_S,"GetEmitter",tolua_MagicParticleLuaAPI_MagicParticleEffect_GetEmitter00);
    tolua_function(tolua_S,"GetMaterial",tolua_MagicParticleLuaAPI_MagicParticleEffect_GetMaterial00);
    tolua_variable(tolua_S,"numEmitters",tolua_get_MagicParticleEffect_numEmitters,NULL);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"MagicParticleEmitter","MagicParticleEmitter","Drawable",NULL);
    tolua_beginmodule(tolua_S,"MagicParticleEmitter");
    tolua_function(tolua_S,"SetEffect",tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect00);
    tolua_function(tolua_S,"SetEffect",tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetEffect01);
    tolua_function(tolua_S,"SetIndex",tolua_MagicParticleLuaAPI_MagicParticleEmitter_SetIndex00);
    tolua_function(tolua_S,"Restart",tolua_MagicParticleLuaAPI_MagicParticleEmitter_Restart00);
    tolua_function(tolua_S,"Stop",tolua_MagicParticleLuaAPI_MagicParticleEmitter_Stop00);
    tolua_function(tolua_S,"Pause",tolua_MagicParticleLuaAPI_MagicParticleEmitter_Pause00);
    tolua_function(tolua_S,"Resume",tolua_MagicParticleLuaAPI_MagicParticleEmitter_Resume00);
    tolua_function(tolua_S,"GetEffect",tolua_MagicParticleLuaAPI_MagicParticleEmitter_GetEffect00);
    tolua_function(tolua_S,"GetIndex",tolua_MagicParticleLuaAPI_MagicParticleEmitter_GetIndex00);
    tolua_variable(tolua_S,"effect",tolua_get_MagicParticleEmitter_effect_ptr,tolua_set_MagicParticleEmitter_effect_ptr);
    tolua_variable(tolua_S,"index",tolua_get_MagicParticleEmitter_index,tolua_set_MagicParticleEmitter_index);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_MagicParticleLuaAPI (lua_State* tolua_S) {
    return tolua_MagicParticleLuaAPI_open(tolua_S);
};
#endif

#endif
