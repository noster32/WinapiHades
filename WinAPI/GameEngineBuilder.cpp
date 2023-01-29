#include "Stdafx.h"
#include "GameEngineBuilder.h"

GameEngineBuilder::GameEngineBuilder(HINSTANCE hInstance, int nCmdShow)
{
    instance = NULL;
    param.hInstance = hInstance;
    param.nCmdShow = nCmdShow;
    param.windowSize = WINSIZE_PT;
    param.title = "Hades";
    param.updateDelay = 62500;
    param.renderDelay = 62500;
    param.updateOnBackground = false;
    param.renderOnBackground = false;
}

GameEngineBuilder& GameEngineBuilder::SetEngineInstance(GameEngine* instance)
{
    this->instance = instance;
    return *this;
}

GameEngineBuilder& GameEngineBuilder::SetWindowSize(uint width, uint height)
{
    param.windowSize = Point2D(width, height);
    return *this;
}

GameEngineBuilder& GameEngineBuilder::SetWindowTitle(string title)
{
    param.title = title;
    return *this;
}

GameEngineBuilder& GameEngineBuilder::SetUpdateDelay(uint micros)
{
    param.updateDelay = micros;
    return *this;
}

GameEngineBuilder& GameEngineBuilder::SetRenderDelay(uint micros)
{
    param.renderDelay = micros;
    return *this;
}

GameEngineBuilder& GameEngineBuilder::EnableUpdateOnBackground()
{
    param.updateOnBackground = true;
    return *this;
}

GameEngineBuilder& GameEngineBuilder::EnableRenderOnBackground()
{
    param.renderOnBackground = true;
    return *this;
}

EngineLauncher GameEngineBuilder::Build()
{
    if (!this->instance)
        throw invalid_argument("Engine Instance is not set");
    return EngineLauncher(instance, param);
}

