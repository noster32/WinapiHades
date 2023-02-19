#pragma once
#include "GameEngine.h"
#include "TestScene.h"
#include "MainMenuScene.h"

class GameEngineImplement : public GameEngine
{
private:
	MainMenuScene sMainMenu;
	TestScene test;
public:

	static GameEngine& GetInstance() {
		static GameEngineImplement instance;
		return instance;
	}
protected:
	virtual void CustomInitialize();
	virtual void CustomOnEngineRelease();
private:
	GameEngineImplement() { }
};

