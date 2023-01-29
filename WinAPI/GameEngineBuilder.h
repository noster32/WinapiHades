#pragma once
#include "EngineLauncher.h"

class GameEngineBuilder
{
private:
	GameEngine* instance;
	EngineInit param;
public:
	GameEngineBuilder(HINSTANCE hInstance, int nCmdShow);

	GameEngineBuilder& SetEngineInstance(GameEngine* instance);
	GameEngineBuilder& SetWindowSize(uint width, uint height);
	GameEngineBuilder& SetWindowTitle(string title);
	GameEngineBuilder& SetUpdateDelay(uint micros);
	GameEngineBuilder& SetRenderDelay(uint micros);
	GameEngineBuilder& EnableUpdateOnBackground();
	GameEngineBuilder& EnableRenderOnBackground();

	EngineLauncher Build();
};

