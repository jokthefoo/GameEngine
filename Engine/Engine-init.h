#pragma once
#include "Math/Vector2.h"
#include "Containers/LinkedList.h"
#include "Memory/HeapManager.h"
#include "GameObjects/GameObject.h"
#include "Renderer.h"
#include "PhysicsInfo.h"

namespace Engine
{
	bool Initialize();
	bool Run();
	void Shutdown();
}