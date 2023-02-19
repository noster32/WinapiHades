#include "Stdafx.h"
#include "GameEngineImplement.h"

void GameEngineImplement::CustomInitialize()
{
	//Scene
	sMainMenu.Init();
	test.Init();
	SetInitialScene(&sMainMenu);
}

void GameEngineImplement::CustomOnEngineRelease()
{
}
