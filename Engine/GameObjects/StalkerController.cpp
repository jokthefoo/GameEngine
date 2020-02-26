#include "StalkerController.h"
#include "cstdlib"

void Engine::StalkerController::SetGameObject(GameObject * iObject)
{
	gameObject = iObject;
}

void Engine::StalkerController::UpdateGameObject()
{
	Engine::Math::Vector2 dir;
	if (target)
	{
		dir = target->GetPos() - gameObject->GetPos();
		dir.Normalize();
	}
	else
	{
		dir = GetRandDir();
	}
	gameObject->UpdatePos(gameObject->GetPos() + dir);
}

void Engine::StalkerController::SetTargetGameObject(GameObject * i_target)
{
	target = i_target;
}

Engine::Math::Vector2 Engine::StalkerController::GetRandDir()
{
	int randXY = (rand() % 2);
	int randPosNe = (rand() % 2);
	if (randXY == 0)
	{
		if (randPosNe == 0)
		{
			return Engine::Math::Vector2(-1,0);
		}
		return Engine::Math::Vector2(1,0);
	}
	else
	{
		if (randPosNe == 0)
		{
			return Engine::Math::Vector2(0,-1);
		}
		return Engine::Math::Vector2(0,1);
	}
}
