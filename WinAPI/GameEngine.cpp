#include "Stdafx.h"
#include "GameEngine.h"

GameEngine::GameEngine() : gl(GLAPI::GetInstance())
{
    setlocale(LC_ALL, "Korean");

    RND->init();
    KEYMANAGER->init();
    IMAGEMANAGER->init();
    TEMPSOUNDMANAGER->init();
    TIMEMANAGER->init();
    SCENEMANAGER->init();
    SOUNDMANAGER->init();

    this->_mainhWnd = NULL;
    this->threadExit = false;
}

HRESULT GameEngine::engineInitializer(EngineInit& param)
{
    this->_mainhWnd = param._hWnd;

    
    RECT rect;
    GetClientRect(_mainhWnd, &rect);
    gl.EnableOpenGL(_mainhWnd, &_hdc, &_hrc, WINSIZE_PT);
    updateOnBackground = param.updateOnBackground;
    renderOnBackground = param.renderOnBackground;
    engineStateUpdate();

    return S_OK;
}



void GameEngine::engineRelease(void)
{
    KillTimer(_hWnd, 1);

    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();
    IMAGEMANAGER->release();
    IMAGEMANAGER->releaseSingleton();
    FONTMANAGER->releaseSingleton();
    TEMPSOUNDMANAGER->releaseSingleton();
    TIMEMANAGER->release();
    TIMEMANAGER->releaseSingleton();
    SCENEMANAGER->release();
    SCENEMANAGER->releaseSingleton();
    SOUNDMANAGER->release();
    SOUNDMANAGER->releaseSingleton();

    gl.DisableOpenGL(_mainhWnd, _hdc, _hrc);
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