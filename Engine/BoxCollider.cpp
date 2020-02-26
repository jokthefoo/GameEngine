#include "BoxCollider.h"
#include "stdio.h"
#include "Matrix4x4.h"
#include "PhysicsInfo.h"

#ifdef _DEBUG
#include <Windows.h>
#endif

Engine::Collision::BoxCollider::BoxCollider()
{
}

Engine::Collision::BoxCollider::BoxCollider(GameObject * i_obj, float center[2], float extents[2], float mass) :
	obj(i_obj), mass(mass)
{
	aabb.center = Engine::Math::Vector2(center[0], center[1]);
	aabb.extents = Engine::Math::Vector2(extents[0], extents[1]);
	boxColliderList.Add(*this);
}

void Engine::Collision::Update(float dt)
{
	for (int a = 0; a < boxColliderList.Count(); a++)
	{
		BoxCollider A = boxColliderList.GetAt(a);
		for (int b = a; b < boxColliderList.Count(); b++)
		{
			BoxCollider B = boxColliderList.GetAt(b);
			if (a != b)
			{
				Engine::Matrix::Matrix mRot = Engine::Matrix::CreateZRot(A.obj->GetRot());
				Engine::Matrix::Matrix mTrans = Engine::Matrix::CreateTranslate(A.obj->GetPos());
				
				Engine::Matrix::Matrix mAToWorld = mTrans * mRot;
				Engine::Matrix::Matrix mWorldToA = mAToWorld.Inverse();

				mRot = Engine::Matrix::CreateZRot(B.obj->GetRot());
				mTrans = Engine::Matrix::CreateTranslate(B.obj->GetPos());

				Engine::Matrix::Matrix mBToWorld = mTrans * mRot;
				Engine::Matrix::Matrix mWorldToB = mBToWorld.Inverse();

				Engine::Matrix::Matrix mAToB = mWorldToB * mAToWorld;
				Engine::Math::Vector4 ABBCenterInB = mAToB * Engine::Math::Vector4(A.aabb.center.x, A.aabb.center.y, 0.0f, 1.0f);
				Engine::Math::Vector4 AExtentsXInB = mAToB * Engine::Math::Vector4(A.aabb.extents.x, 0, 0, 0);
				Engine::Math::Vector4 AExtentsYInB = mAToB * Engine::Math::Vector4(0, A.aabb.extents.y, 0, 0);

				// Check A onto B x axis
				double AProjOntoB_X = fabs(AExtentsXInB.x) + fabs(AExtentsYInB.x);
				bool isSep = fabs(ABBCenterInB.x - B.aabb.center.x) > B.aabb.extents.x + AProjOntoB_X;
				if (isSep)
				{
					continue;
				}

				// Check A onto B y axis
				double AProjOntoB_Y = fabs(AExtentsXInB.y) + fabs(AExtentsYInB.y);
				isSep = fabs(ABBCenterInB.y - B.aabb.center.y) > B.aabb.extents.y + AProjOntoB_Y;
				if (isSep)
				{
					continue;
				}


				Engine::Matrix::Matrix mBToA = mWorldToA * mBToWorld;
				Engine::Math::Vector4 BBBCenterInA = mBToA * Engine::Math::Vector4(B.aabb.center.x, B.aabb.center.y, 0.0f, 1.0f);
				Engine::Math::Vector4 BExtentsXInA = mBToA * Engine::Math::Vector4(B.aabb.extents.x, 0, 0, 0);
				Engine::Math::Vector4 BExtentsYInA = mBToA * Engine::Math::Vector4(0, B.aabb.extents.y, 0, 0);

				// Check B onto A x axis
				double BProjOntoA_X = fabs(BExtentsXInA.x) + fabs(BExtentsYInA.x);
				isSep = fabs(BBBCenterInA.x - A.aabb.center.x) > A.aabb.extents.x + BProjOntoA_X;
				if (isSep)
				{
					continue;
				}

				// Check B onto A y axis
				double BProjOntoA_Y = fabs(BExtentsXInA.y) + fabs(BExtentsYInA.y);
				isSep = fabs(BBBCenterInA.y - A.aabb.center.y) > A.aabb.extents.y + BProjOntoA_Y;
				if (isSep)
				{
					continue;
				}

				// If we didn't find seperation then we have collision
				OutputDebugString("Collision!\n");
				float aMass = A.mass;
				float bMass = B.mass;
				Engine::Math::Vector2 aVp;
				Engine::Math::Vector2 bVp;
				if (aMass == INFINITY)
				{
					aVp = Engine::Math::Vector2(A.obj->GetVel());
					bVp = Engine::Math::Vector2(B.obj->GetVel() * Engine::Math::Vector2(1.0f, -1.0f));
				} 
				else if (bMass == INFINITY)
				{
					aVp = Engine::Math::Vector2(A.obj->GetVel() * Engine::Math::Vector2(1.0f, -1.0f));
					bVp = Engine::Math::Vector2(B.obj->GetVel());
				}
				else
				{
					aVp = Engine::Math::Vector2(A.obj->GetVel() * ((aMass - bMass) / (aMass + bMass)) + B.obj->GetVel() * ((2 * bMass) / (aMass + bMass)));
					bVp = Engine::Math::Vector2(B.obj->GetVel() * ((bMass - aMass) / (aMass + bMass)) + A.obj->GetVel() * ((2 * aMass) / (aMass + bMass)));
				}
				A.obj->SetVel(aVp);
				B.obj->SetVel(bVp);
			}
		}
	}
}

void Engine::Collision::Shutdown()
{
	boxColliderList.DeleteList();
}