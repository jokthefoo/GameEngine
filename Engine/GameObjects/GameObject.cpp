#include "GameObject.h"

Engine::GameObject::GameObject() :
	pos(0,0), velocity(0,0), rotation(0), oldPos(0,0), GameForce(0,0)
{
}

Engine::GameObject::GameObject(const Engine::Math::Vector2 & initPos) :
	pos(initPos), velocity(0, 0), rotation(0), oldPos(initPos), GameForce(0,0)
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

void Engine::GameObjectShutdown()
{
	gameObjectList.DeleteList();
}
