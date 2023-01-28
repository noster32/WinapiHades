#include "Stdafx.h"
#include "GameEngine.h"

HRESULT GameEngine::engineInitializer(EngineInit& param)
{
    _hdc = GetDC(_hWnd);

    RECT rect;
    GetClientRect(_hWnd, &rect);
    gl.EnableOpenGL(_hWnd, &_hdc, &_hrc, WINSIZE_PT);
    updateOnBackground = param.updateOnBackground;
    renderOnBackground = param.renderOnBackground;
    engineStateUpdate();

    return S_OK;
}



void GameEngine::engineRelease(void)
{
    gl.DisableOpenGL(_hWnd, _hdc, _hrc);
    _mutex.unlock();
    engineStateUpdate();
}

void GameEngine::engineUpdate(void)
{
    _mutex.lock();
    _mutex.unlock();
}

void GameEngine::engineRender(void)
{
    _mutex.lock();
    isWindowsActive = GetActiveWindow() == _hWnd;
    if (!renderOnBackground && !isWindowsActive) {
        _mutex.unlock();
        return;
    }
    gl.ClearBuffer();
    gl.LoadIdentity();
    gl.SwapBuffer();
    _mutex.unlock();
}

void GameEngine::engineStateUpdate(void)
{
    if (gl.GetSuccess()) {
        if (egState & OPENGL_NOT_READY == OPENGL_NOT_READY)
            egState ^= OPENGL_NOT_READY;
    }
    else

        if (threadExit)
            egState != ENGINE_STOPPED;

    if (egState != GameEngine::OK) {
        stringstream ss;
        ss << "Incomplete Engine Initialization" << endl;
        ss << "State Code : " << egState << endl << endl;
        if (egState & GameEngine::OPENGL_NOT_READY)
            ss << "* GL API Not Initialized" << endl;
        if (egState & GameEngine::ENGINE_STOPPED)
            ss << "*Engine Already Stopped" << endl;

        stateString = ss.str();
    }
}