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
			PhysicsInfo(GameObject*, float, float);
			GameObject* obj;
			float mass;
			float drag;
			bool gravity;
		};
		static float Gravity = -0;
		void Update(float dt);
		static LinkedList<PhysicsInfo> physicsObjectsList;
		void Shutdown();
		void UpdateGravity(float g);
	}
}