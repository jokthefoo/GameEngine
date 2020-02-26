#pragma once
#include "../Math/Vector2.h"
#include "../Containers/LinkedList.h"

namespace Engine
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(const Engine::Math::Vector2 & initPos);
		GameObject(const Engine::Math::Vector2 & initPos, float rot);
		void UpdatePos(const Engine::Math::Vector2 & movVec);
		void UpdateRot(float i_rot);
		Engine::Math::Vector2 GetPos();
		Engine::Math::Vector2 GetVel();
		void SetVel(Engine::Math::Vector2 newVel);
		float GetRot();
		Engine::Math::Vector2 oldPos;
		Engine::Math::Vector2 GameForce;
	protected:
		Engine::Math::Vector2 pos;
		Engine::Math::Vector2 velocity;
		float rotation;
	};
	GameObject* CreateGameobject(const char* fileName);
	static LinkedList<GameObject> gameObjectList;
	void GameObjectShutdown();
}