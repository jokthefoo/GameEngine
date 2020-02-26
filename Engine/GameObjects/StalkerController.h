#pragma once

#include "IGameObject.h"

namespace Engine
{
	class StalkerController : public IGameObject
	{
	public:
		void SetGameObject(GameObject * iObject) override;
		void UpdateGameObject() override;
		void SetTargetGameObject(GameObject * i_target);
		Engine::Math::Vector2 GetRandDir();
	private:
		GameObject * gameObject;
		GameObject * target;
	};
}