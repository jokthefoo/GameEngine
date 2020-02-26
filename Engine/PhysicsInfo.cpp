#include "PhysicsInfo.h"

Engine::Physics::PhysicsInfo::PhysicsInfo() :
	obj(NULL), mass(0), drag(0), gravity(true)
{
}

Engine::Physics::PhysicsInfo::PhysicsInfo(GameObject * i_obj, float mas, float drg) :
	obj(i_obj), mass(mas), drag(drg), gravity(true)
{
	physicsObjectsList.Add(*this);
}

void Engine::Physics::Update(float dt)
{
	for (int i = 0; i < Engine::Physics::physicsObjectsList.Count(); i++)
	{
		Engine::Physics::PhysicsInfo objInf = Engine::Physics::physicsObjectsList.GetAt(i);

		Engine::Math::Vector2 oldVel = objInf.obj->GetVel();

		Engine::Math::Vector2 velDir(oldVel);
		velDir.Normalize();
		velDir *= -1;

		Engine::Math::Vector2 dragF = (oldVel * oldVel) * (velDir * objInf.drag);

		float grav = Gravity;
		if (!objInf.gravity)
		{
			grav = 0;
		}
		Engine::Math::Vector2 forces = objInf.obj->GameForce + Engine::Math::Vector2(0, (grav * objInf.mass)) + objInf.obj->GetVel() + dragF;

		objInf.obj->SetVel(forces);
		objInf.obj->UpdatePos(objInf.obj->GetPos() + ((oldVel + forces) / 2) * (dt / 1000));
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
