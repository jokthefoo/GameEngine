#pragma once

#include "IGameObject.h"

namespace Engine
{
	class TeleportController : public IGameObject
	{
	public:
		void SetGameObject(GameObject * iObject) override;
		void UpdateGameObject() override;
		Engine::Math::Vector2 GetRandLoc();
	private:
		GameObject * gameObject;
	};
}