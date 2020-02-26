#include "PlayerController.h"

void Engine::PlayerController::SetGameObject(GameObject * iObject)
{
	gameObject = iObject;
}

void Engine::PlayerController::UpdateGameObject()
{
	if (gameObject)
	{
		Engine::Math::Vector2 dir = GetMoveDirFromInput();
		gameObject->UpdatePos(gameObject->GetPos() + dir);
	}
}

Engine::Math::Vector2 Engine::PlayerController::GetMoveDirFromInput()
{
	return Engine::Math::Vector2(0,1);
}
