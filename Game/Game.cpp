#include "Game.h"
#include "GLib.h"
#include "stdio.h"
#include "Engine-init.h"

Engine::GameObject* playerRef;
Engine::GameObject* enemyRef;

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
	if (i_VKeyID == 87 && bWentDown) //W Down
	{
		(*playerRef).GameForce = Engine::Math::Vector2(0, 80.0f);
	}
	else if (i_VKeyID == 87)
	{
		(*playerRef).GameForce = Engine::Math::Vector2(0, 0);
	}
	else if (i_VKeyID == 71 && bWentDown)
	{
		Engine::Physics::UpdateGravity(-1);
	}
}

int Game::GameInit()
{
	playerRef = new Engine::GameObject(Engine::Math::Vector2(-100, -200));
	Engine::Renderer::ObjectRenderer guyRenderer(playerRef, Engine::Renderer::CreateSprite("data\\GoodGuy.dds"));
	Engine::Physics::PhysicsInfo guyPhys(playerRef, 10, .0001f);

	enemyRef = new Engine::GameObject(Engine::Math::Vector2(100, -200));
	Engine::Renderer::ObjectRenderer enRenderer(enemyRef, Engine::Renderer::CreateSprite("data\\BadGuy.dds"));

	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
	return 1;
}

void Game::GameUpdate()
{
	static float			moveDist = .02f;
	static float			moveDir = -moveDist;

	static Engine::Math::Vector2	Offset = { 180.0f, -100.0f };

	if (Offset.x > 200.0f)
		moveDir = -moveDist;
	else if (Offset.x < 160.0f)
		moveDir = moveDist;

	Offset.x += moveDir;
	enemyRef->UpdatePos(Offset);
}

void Game::Shutdown()
{
	delete(playerRef);
	delete(enemyRef);
}