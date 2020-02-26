#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "Engine-init.h"
#include "Game.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	if (Engine::Initialize())
	{
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
		Engine::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 1;
}