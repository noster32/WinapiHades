#include "Stdafx.h"
#include "GameEngineImplement.h"

void GameEngineImplement::CustomInitialize()
{
	//Scene
	test.Init();
	SetInitialScene(&test);
}

void GameEngineImplement::CustomOnEngineRelease()
{
}
