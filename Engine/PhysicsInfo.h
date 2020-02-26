#pragma once
#include "GameObjects/GameObject.h"

namespace Engine
{
	namespace Physics
	{
		class PhysicsInfo
		{
		public:
			PhysicsInfo();
			PhysicsInfo(GameObject*, float, float, int, int);
			GameObject* obj;
			float mass;
			float drag;
			Engine::Math::Vector2 accel;
			bool gravity;
			bool isStatic;
		};
		static float Gravity = -0;
		void Update(float dt);
		static LinkedList<PhysicsInfo> physicsObjectsList;
		void Shutdown();
		void UpdateGravity(float g);
	}
}