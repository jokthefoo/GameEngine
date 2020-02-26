#include "GameObject.h"
#include <lua.hpp>
#include <stdint.h>
#include <string.h>
#include "../Renderer.h"
#include "../PhysicsInfo.h"
#include "../BoxCollider.h"

Engine::GameObject::GameObject() :
	pos(0,0), velocity(0,0), rotation(0), oldPos(0,0), GameForce(0,0)
{
}

Engine::GameObject::GameObject(const Engine::Math::Vector2 & initPos) :
	pos(initPos), velocity(0, 0), rotation(0), oldPos(initPos), GameForce(0,0)
{
	gameObjectList.Add(*this);
}

Engine::GameObject::GameObject(const Engine::Math::Vector2 & initPos, float rot) :
	pos(initPos), velocity(0, 0), rotation(rot), oldPos(initPos), GameForce(0, 0)
{
	gameObjectList.Add(*this);
}

void Engine::GameObject::UpdatePos(const Engine::Math::Vector2 & movVec)
{
	oldPos = pos;
	pos = movVec;
}

Engine::Math::Vector2 Engine::GameObject::GetPos()
{
	return pos;
}

Engine::Math::Vector2 Engine::GameObject::GetVel()
{
	return velocity;
}

void Engine::GameObject::SetVel(Engine::Math::Vector2 newVel)
{
	velocity = newVel;
}

float Engine::GameObject::GetRot()
{
	return rotation;
}

void Engine::GameObject::UpdateRot(float i_rot)
{
	rotation = i_rot;
}

Engine::GameObject* Engine::CreateGameobject(const char * fileName)
{
	lua_State * pLuaState = luaL_newstate();
	assert(pLuaState);

	luaL_openlibs(pLuaState);

	int result = luaL_loadfile(pLuaState, fileName);
	assert(result == 0);

	result = lua_pcall(pLuaState, 0, 0, 0);
	assert(result == 0);

	int type = lua_getglobal(pLuaState, "Object");
	assert(type == LUA_TTABLE);


	lua_pushstring(pLuaState, "position");
	type = lua_gettable(pLuaState, -2);
	assert(type == LUA_TTABLE);
	lua_pushnil(pLuaState);
	float posFloats[2];
	int i = 0;
	while (lua_next(pLuaState, -2) != 0)
	{
		assert(lua_type(pLuaState, -1) == LUA_TNUMBER);

		lua_Number value = lua_tonumber(pLuaState, -1);
		posFloats[i] = float(value);
		// pop the value
		lua_pop(pLuaState, 1);
		i++;
	}
	lua_pop(pLuaState, 1);//pop position
	lua_pushstring(pLuaState, "rotation");
	type = lua_gettable(pLuaState, -2);
	lua_Number rotation = lua_tonumber(pLuaState, -1);
	lua_pop(pLuaState, 1);



	Engine::GameObject* playerRef = new Engine::GameObject(Engine::Math::Vector2(posFloats[0], posFloats[1]), float(rotation));


	float mass = 10;
	lua_pushstring(pLuaState, "physics_settings");
	type = lua_gettable(pLuaState, -2);
	if (type == LUA_TTABLE)
	{
		lua_pushstring(pLuaState, "mass");
		type = lua_gettable(pLuaState, -2);
		lua_Number Lmass = lua_tonumber(pLuaState, -1);
		lua_pop(pLuaState, 1);
		lua_pushstring(pLuaState, "drag");
		type = lua_gettable(pLuaState, -2);
		lua_Number drag = lua_tonumber(pLuaState, -1);
		lua_pop(pLuaState, 1);
		lua_pushstring(pLuaState, "gravity");
		type = lua_gettable(pLuaState, -2);
		int grav = lua_toboolean(pLuaState, -1);
		lua_pop(pLuaState, 1);
		lua_pushstring(pLuaState, "isStatic");
		type = lua_gettable(pLuaState, -2);
		int isStatic = lua_toboolean(pLuaState, -1);
		lua_pop(pLuaState, 1);

		mass = float(Lmass);
		if (isStatic)
		{
			mass = INFINITY;
		}

		Engine::Physics::PhysicsInfo guyPhys(playerRef, mass, float(drag), grav, isStatic);
	}
	lua_pop(pLuaState, 1);//pop physics


	lua_pushstring(pLuaState, "collider");
	type = lua_gettable(pLuaState, -2);
	if (type == LUA_TTABLE)
	{
		lua_pushstring(pLuaState, "center");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TTABLE);
		lua_pushnil(pLuaState);
		float centerFloats[2];
		int i = 0;
		while (lua_next(pLuaState, -2) != 0)
		{
			assert(lua_type(pLuaState, -1) == LUA_TNUMBER);

			lua_Number value = lua_tonumber(pLuaState, -1);
			centerFloats[i] = float(value);
			// pop the value
			lua_pop(pLuaState, 1);
			i++;
		}
		lua_pop(pLuaState, 1);//pop center

		lua_pushstring(pLuaState, "extents");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TTABLE);
		lua_pushnil(pLuaState);
		float extentFloats[2];
		i = 0;
		while (lua_next(pLuaState, -2) != 0)
		{
			assert(lua_type(pLuaState, -1) == LUA_TNUMBER);

			lua_Number value = lua_tonumber(pLuaState, -1);
			extentFloats[i] = float(value);
			// pop the value
			lua_pop(pLuaState, 1);
			i++;
		}
		lua_pop(pLuaState, 1);//pop extents

		Engine::Collision::BoxCollider colRef(playerRef, centerFloats, extentFloats, mass);
	}
	lua_pop(pLuaState, 1);//pop collider
	   


	lua_pushstring(pLuaState, "render_settings");
	type = lua_gettable(pLuaState, -2);
	if (type == LUA_TTABLE)
	{
		lua_pushstring(pLuaState, "sprite");
		type = lua_gettable(pLuaState, -2);
		const char * spriteName = lua_tostring(pLuaState, -1);
		if (spriteName)
		{
			spriteName = _strdup(spriteName);
		}
		lua_pop(pLuaState, 1);//pop sprite


		Engine::Renderer::ObjectRenderer guyRenderer(playerRef, Engine::Renderer::CreateSprite(spriteName));
		delete(spriteName);
	}
	lua_pop(pLuaState, 1);//pop render

	lua_pop(pLuaState, 1);//pop player

	//delete(pLuaState);
	lua_close(pLuaState);
	return playerRef;
}

void Engine::GameObjectShutdown()
{
	gameObjectList.DeleteList();
}
