#pragma once

#include "IGameObject.h"

namespace Engine
{
	class PlayerController : public IGameObject
	{
	public:
		void SetGameObject(GameObject * iObject) override;
		void UpdateGameObject() override;
		Engine::Math::Vector2 GetMoveDirFromInput();
	private:
		GameObject * gameObject;
	};
}