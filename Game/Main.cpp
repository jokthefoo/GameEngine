#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

//#define _PROFILE

#include "Engine-init.h"
#include "Game.h"

#if defined _PROFILE
#include "CollisionUnitTest.h"
#endif

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	if (Engine::Initialize())
	{
#if defined _PROFILE
		CollisionTesting::SetupTest();
		while (1)
		{
			if (CollisionTesting::RunTest())
			{
				break;
			}
		}
		CollisionTesting::Shutdown();
#else
		if (Game::GameInit())
		{
			while(1)
			{
				if (Engine::Run())
				{
					break;
				}
				Game::GameUpdate();
			}
		}
		Game::Shutdown();
#endif
		Engine::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 1;
}