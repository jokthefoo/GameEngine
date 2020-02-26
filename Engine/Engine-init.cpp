#include "Engine-init.h"
#include "stdio.h"
#include <Windows.h>
#include "Memory/HeapManagerProxy.h"
#include "GLib.h"
#include "Timing.h"
#include "Renderer.h"
#include <string>
#include "BoxCollider.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

bool Engine::Initialize()
{
	printf("\n--Engine initialized--\n\n");
	Engine::Timing::Init();
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(GetModuleHandle(NULL), 10, "GLibTest", -1, 800, 600);
	return bSuccess;
}



bool Engine::Run()
{
	bool bQuit = false;

	// IMPORTANT: We need to let GLib do it's thing.
	GLib::Service(bQuit);

	float dt = Timing::CalcTimeSinceLastCall();
	
	if (dt > 50)
	{
		std::string s = "DT: " + std::to_string(dt) + "\n";
		OutputDebugString((LPCSTR)s.c_str());
	}

	//input?

	//Run physics
	Engine::Physics::Update(dt);

	//Run collisions
	Engine::Collision::Update(dt);

	//Render sprites
	Renderer::RenderSprites();

	return bQuit;
}

void Engine::Shutdown()
{
	Renderer::Shutdown();
	Physics::Shutdown();
	Collision::Shutdown();
	GameObjectShutdown();
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}