#pragma once
#include "GameObjects/GameObject.h"

namespace Engine
{
	namespace Collision
	{
		struct AABB {
			Engine::Math::Vector2 center;
			Engine::Math::Vector2 extents;
		};

		class BoxCollider
		{
		public:
			BoxCollider();
			BoxCollider(GameObject*, float center[2], float extents[2], float mass);
			GameObject* obj;
			AABB aabb;
			float mass;
		};
		void Update(float dt);
		void Shutdown();
		static LinkedList<BoxCollider> boxColliderList;
	}
}