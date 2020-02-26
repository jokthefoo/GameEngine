#pragma once
#include "GameObject.h"
#include "../Math/Vector2.h"

namespace Engine
{
	class IGameObject
	{
	public:
		virtual void SetGameObject(GameObject * iObject) = 0;
		virtual void UpdateGameObject() {}
	};
}