#include "PhysicsInfo.h"
#include "Matrix4x4.h"

Engine::Physics::PhysicsInfo::PhysicsInfo() :
	obj(NULL), mass(0), drag(0), gravity(true), accel(0, 0), isStatic(false)
{
}

Engine::Physics::PhysicsInfo::PhysicsInfo(GameObject * i_obj, float mas, float drg, int grav, int isStatic) :
	obj(i_obj), mass(mas), drag(drg), gravity(grav), accel(0,0), isStatic(isStatic)
{
	physicsObjectsList.Add(*this);
}

void Engine::Physics::Update(float dt)
{
	dt = dt / 1000;
	for (int i = 0; i < Engine::Physics::physicsObjectsList.Count(); i++)
	{
		Engine::Physics::PhysicsInfo objInf = Engine::Physics::physicsObjectsList.GetAt(i);

		if (objInf.isStatic)
		{
			//continue;
		}

		Engine::Math::Vector2 vel = objInf.obj->GetVel();
		Engine::Math::Vector2 dragForce = (vel * vel * -objInf.drag) / 2;

		if (vel.x < 0)
		{
			dragForce.x *= -1;
		}
		if (vel.y < 0)
		{
			dragForce.y *= -1;
		}

		Engine::Math::Vector2 prevAccel = objInf.accel;
		Engine::Math::Vector2 newPos = objInf.obj->GetPos() + vel * dt + (prevAccel * 0.5f * (dt * dt));
		objInf.obj->UpdatePos(newPos);

		Engine::Math::Vector2 grav = Engine::Math::Vector2(0, 0);
		if (objInf.gravity)
		{
			grav = Engine::Math::Vector2(0, -9.81) * objInf.mass;
		}
		Engine::Math::Vector2 forces = grav + dragForce + objInf.obj->GameForce * 10;

		objInf.accel = forces / objInf.mass;

		Engine::Math::Vector2 avgAccel = (prevAccel + objInf.accel) / 2;
		Engine::Math::Vector2 newVel = vel + avgAccel * dt;
		objInf.obj->SetVel(newVel);


		/*
		Engine::Math::Vector2 velDir(oldVel);
		velDir.Normalize();
		velDir *= -1;

		Engine::Math::Vector2 dragF = (oldVel * oldVel) * (velDir * objInf.drag);

		float grav = Gravity;
		if (!objInf.gravity)
		{
			grav = 0;
		}
		Engine::Math::Vector2 forces = objInf.obj->GameForce + Engine::Math::Vector2(0, (grav * objInf.mass)) + objInf.obj->GetVel() + dragF;*/
	}
}

void Engine::Physics::Shutdown()
{
	physicsObjectsList.DeleteList();
}

void Engine::Physics::UpdateGravity(float g)
{
	Gravity = g;
}
