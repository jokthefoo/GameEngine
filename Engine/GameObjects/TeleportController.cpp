#include "TeleportController.h"
#include "cstdlib"

void Engine::TeleportController::SetGameObject(GameObject * iObject)
{
	gameObject = iObject;
}

void Engine::TeleportController::UpdateGameObject()
{
	if (gameObject)
	{
		Engine::Math::Vector2 loc = GetRandLoc();
		gameObject->UpdatePos(loc);
	}
}

Engine::Math::Vector2 Engine::TeleportController::GetRandLoc()
{
	float x = rand() % 100;
	float y = rand() % 100;
	return Engine::Math::Vector2(x,y);
}