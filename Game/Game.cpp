#include "Game.h"
#include "GLib.h"
#include "stdio.h"
#include "Engine-init.h"

Engine::GameObject* gCubeRef;
Engine::GameObject* topWallRef;
Engine::GameObject* botWallRef;
Engine::GameObject* bCubeRef;
Engine::GameObject* puckRef;

Engine::GameObject* scoreg2Ref;
Engine::GameObject* scoreg1Ref;
Engine::GameObject* scoreg0Ref;
Engine::GameObject* scoreb2Ref;
Engine::GameObject* scoreb1Ref;
Engine::GameObject* scoreb0Ref;
Engine::GameObject* bwin;
Engine::GameObject* gwin;

float puckSpeed = 250.0f;
float moveSpeed = 750.0f;
int greenScore = 0;
int blueScore = 0;
bool gameOver = false;

void Game::Controls(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG

	if (!gameOver)
	{
		//Player 1 controls
		if (i_VKeyID == 0x57 && bWentDown) //W Down
		{
			bCubeRef->GameForce = Engine::Math::Vector2(0, moveSpeed);
		}
		else if (i_VKeyID == 0x57) //W Up
		{
			bCubeRef->GameForce = Engine::Math::Vector2(0, 0);
		}
		else if (i_VKeyID == 0x53 && bWentDown) //S Down
		{
			bCubeRef->GameForce = Engine::Math::Vector2(0.0f, -moveSpeed);
		}
		else if (i_VKeyID == 0x53) //S up
		{
			bCubeRef->GameForce = Engine::Math::Vector2(0.0f, 0.0f);
		}

		//Player 2 controls
		if (i_VKeyID == 0x49 && bWentDown) //W Down
		{
			gCubeRef->GameForce = Engine::Math::Vector2(0, moveSpeed);
		}
		else if (i_VKeyID == 0x49) //W Up
		{
			gCubeRef->GameForce = Engine::Math::Vector2(0, 0);
		}
		else if (i_VKeyID == 0x4b && bWentDown) //S Down
		{
			gCubeRef->GameForce = Engine::Math::Vector2(0.0f, -moveSpeed);
		}
		else if (i_VKeyID == 0x4b) //S up
		{
			gCubeRef->GameForce = Engine::Math::Vector2(0.0f, 0.0f);
		}
	}
}

int Game::GameInit()
{
	//Scoreboard for green
	scoreg2Ref = Engine::CreateGameobject("data\\scoreG2.lua");
	scoreg1Ref = Engine::CreateGameobject("data\\scoreG1.lua");
	scoreg0Ref = Engine::CreateGameobject("data\\scoreG0.lua");
	gwin = Engine::CreateGameobject("data\\greenwin.lua");

	//Scoreboard for blue
	scoreb2Ref = Engine::CreateGameobject("data\\scoreB2.lua");
	scoreb1Ref = Engine::CreateGameobject("data\\scoreB1.lua");
	scoreb0Ref = Engine::CreateGameobject("data\\scoreB0.lua");
	bwin = Engine::CreateGameobject("data\\bluewin.lua");

	//Walls
	topWallRef = Engine::CreateGameobject("data\\blackWall1.lua");
	botWallRef = Engine::CreateGameobject("data\\blackWall2.lua");

	//Players and ball
	gCubeRef = Engine::CreateGameobject("data\\gCube.lua");
	bCubeRef = Engine::CreateGameobject("data\\BlueCube.lua");
	puckRef = Engine::CreateGameobject("data\\puck.lua");
	
	puckRef->SetVel(Engine::Math::Vector2(-puckSpeed, 0.0f));

	GLib::SetKeyStateChangeCallback(Game::Controls);
	return 1;
}

void Game::GameUpdate()
{
	if (!gameOver)
	{
		//Lock the players X movement
		bCubeRef->UpdatePos(Engine::Math::Vector2(-400.0f, bCubeRef->GetPos().y));
		gCubeRef->UpdatePos(Engine::Math::Vector2(400.0f, gCubeRef->GetPos().y));
		//Keep the puck at a constant speed
		if (puckRef->GetVel().Length() < puckSpeed)
		{
			float mul = puckSpeed / puckRef->GetVel().Length();
			puckRef->SetVel(puckRef->GetVel() * mul);
		}

		//Score a goal
		if (puckRef->GetPos().x > 400.0f)
		{
			printf("SCORE! points for blue");
			puckRef->SetVel(Engine::Math::Vector2(puckSpeed, 0.0f));
			ResetPositions();

			greenScore++;
			switch (greenScore)
			{
			case 1:
				scoreb0Ref->UpdatePos(Engine::Math::Vector2(5000.0f, 0.0f));
				break;
			case 2:
				scoreb1Ref->UpdatePos(Engine::Math::Vector2(5000.0f, 0.0f));
				break;
			case 3:
				bwin->UpdatePos(Engine::Math::Vector2(0.0f, 200.0f));
				gameOver = true;
				puckRef->SetVel(Engine::Math::Vector2(0.0f, 0.0f));
				break;
			}
		}
		if (puckRef->GetPos().x < -400.0f)
		{
			printf("SCORE! points for green");
			puckRef->SetVel(Engine::Math::Vector2(-puckSpeed, 0.0f));
			ResetPositions();

			blueScore++;
			switch (blueScore)
			{
			case 1:
				scoreg0Ref->UpdatePos(Engine::Math::Vector2(5000.0f, 0.0f));
				break;
			case 2:
				scoreg1Ref->UpdatePos(Engine::Math::Vector2(5000.0f, 0.0f));
				break;
			case 3:
				gwin->UpdatePos(Engine::Math::Vector2(0.0f, 200.0f));
				gameOver = true;
				puckRef->SetVel(Engine::Math::Vector2(0.0f, 0.0f));
				break;
			}
		}
	}
}

void Game::ResetPositions()
{
	puckRef->UpdatePos(Engine::Math::Vector2(0.0f, 0.0f));

	bCubeRef->SetVel(Engine::Math::Vector2(0.0f, 0.0f));
	gCubeRef->SetVel(Engine::Math::Vector2(0.0f, 0.0f));

	bCubeRef->UpdatePos(Engine::Math::Vector2(-400.0f, 0.0f));
	gCubeRef->UpdatePos(Engine::Math::Vector2(400.0f, 0.0f));
}

void Game::Shutdown()
{
	delete(gCubeRef);
	delete(bCubeRef);

	delete(topWallRef);
	delete(botWallRef);
	delete(puckRef);

	delete(scoreg1Ref);
	delete(scoreg0Ref);
	delete(scoreg2Ref);
	delete(scoreb1Ref);
	delete(scoreb0Ref);
	delete(scoreb2Ref);

	delete(bwin);
	delete(gwin);
}