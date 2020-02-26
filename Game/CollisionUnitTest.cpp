#include "CollisionUnitTest.h"
#include "GameObjects/GameObject.h"
#include "PhysicsInfo.h"
#include "BoxCollider.h"
#include "GLib.h"
#include "Timing.h"
#include <ctime>
#include <vector>

Engine::GameObject* objects[100];

void CollisionTesting::SetupTest()
{
	srand(static_cast<unsigned>(time(0)));
	for (int i = 0; i < 100; i++)
	{
		//Random pos 0-1000
		float posX = static_cast<float> (rand() / static_cast<float>(RAND_MAX));
		posX *= 1000;
		float posY = static_cast<float> (rand() / static_cast<float>(RAND_MAX));
		posX *= 1000;

		//Random rotation from 0-360
		float rot = static_cast<float> (rand() / static_cast<float>(RAND_MAX));
		rot *= 360;

		Engine::GameObject* gRef = new Engine::GameObject(Engine::Math::Vector2(posX, posY), rot);

		//50 by 50 cubes
		float center[2] = { 0, 50 };
		float extents[2] = { 50, 50 };
		Engine::Collision::BoxCollider col(gRef, center, extents, 10);
		// 10 mass, 0 drag, no gravity
		Engine::Physics::PhysicsInfo p(gRef, 10.0f, 0.0f, false, false);

		objects[i] = gRef;
	}
}

bool CollisionTesting::RunTest()
{
	bool bQuit = false;

	GLib::Service(bQuit);
	float dt = Engine::Timing::CalcTimeSinceLastCall();

	//Run physics
	Engine::Physics::Update(dt);

	//Run collisions
	Engine::Collision::Update(dt);

	return bQuit;
}

void CollisionTesting::Shutdown()
{
	for (int i = 0; i < 100; i++)
	{
		delete(objects[i]);
	}
}
