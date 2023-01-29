#pragma once
#include "GameEngine.h"

class GameEngineImplement : public GameEngine
{
private:
	//Input Scene
public:
	static GameEngine& GetInstance() {
		static GameEngineImplement instance;
		return instance;
	}
protected:
	virtual void CustomInitialize();
	virtual void CustomOnEngineRelease();
};

