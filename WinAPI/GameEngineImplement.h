#pragma once
#include "GameEngine.h"
#include "TestScene.h"

class GameEngineImplement : public GameEngine
{
private:
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

