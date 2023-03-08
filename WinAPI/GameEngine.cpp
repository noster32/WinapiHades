#include "Stdafx.h"
#include "GameEngine.h"

GameEngine::GameEngine() : gl(GLAPI::GetInstance()),
                           eg(EngineAPI::GetInstance())
{
    setlocale(LC_ALL, "Korean");

    this->_mainhWnd = NULL;
    this->threadExit = false;
}

void GameEngine::SetInitialScene(scene* scene)
{
    if (sCurrent) return;
    sCurrent = scene;
    sCurrent->SetSceneState(scene::BEGIN);
}

HRESULT GameEngine::engineInitializer(EngineInit& param)
{
    this->_mainhWnd = param._hWnd;

    
    RECT rect;
    GetClientRect(_mainhWnd, &rect);
    gl.EnableOpenGL(_mainhWnd, &_hdc, &_hrc, WINSIZE_PT);
    updateOnBackground = param.updateOnBackground;
    renderOnBackground = param.renderOnBackground;
    RND->init();
    KEYMANAGER->init();
    SOUNDMANAGER->init();
    gl.EnableFreeType();
    CustomInitialize();
    engineStateUpdate();

    

    
    return S_OK;
}



void GameEngine::engineRelease(void)
{
    KillTimer(_mainhWnd, 1);
    CustomOnEngineRelease();
    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();
    FONTMANAGER->releaseSingleton();
    SOUNDMANAGER->release();
    SOUNDMANAGER->releaseSingleton();

    gl.DisableOpenGL(_mainhWnd, _hdc, _hrc);
    engineStateUpdate();
}

void GameEngine::engineUpdate(void)
{
    _mutex.lock();
    if (!isWindowsActive) {
        _mutex.unlock();
        return;
    }

    if (eg.InternalGetShutdown()) {
        _mutex.unlock();
        StopEngine();
        return;
    }

    POINT cpos;
    if (GetCursorPos(&cpos))
        if (ScreenToClient(_mainhWnd, &cpos))
            _ptMouse = Point2D(cpos.x, WINSIZE_Y - cpos.y);

    switch (sCurrent->GetSceneState()) {
    case scene::END:
        sCurrent->InternalOnEnd();

        if (scene::GetSwapFlag()) {
            scene* next = scene::GetNextScene();
            if (next != NULL)
                sCurrent = next;
            scene::ResetSwapFlag();
        }
        sCurrent->SetSceneState(scene::BEGIN);

    case scene::BEGIN:
        sCurrent->SetSceneState(scene::LOADING);
        sCurrent->InternalOnBegin();

    case scene::LOADING:
        sCurrent->InternalOnUpdateLoading();
        break;
    case scene::UPDATE:
        sCurrent->InternalOnUpdate();
        break;
    case scene::CLOSING:
        sCurrent->InternalOnRenderClosing();
        break;
    }
    _mutex.unlock();
}

void GameEngine::engineRender(void)
{
    _mutex.lock();
    isWindowsActive = GetActiveWindow() == _mainhWnd;
    
    if (!renderOnBackground && !isWindowsActive) {
        _mutex.unlock();
        return;
    }
    
    scene::SceneState state = sCurrent->GetSceneState();
    if (state == scene::BEGIN || state == scene::END) {
        _mutex.unlock();
        return;
    }

    gl.ClearBuffer();
    glClearColor(0, 0, 0, 0);
    gl.LoadIdentity();
    switch (state) {
    case scene::BEGIN:
    case scene::END:
        break;
    case scene::LOADING:
        sCurrent->InternalOnRenderLoading();
        break;
    case scene::UPDATE:
        sCurrent->InternalOnRender();
        break;
    case scene::CLOSING:
        sCurrent->InternalOnRenderClosing();
        break;
    }
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
        egState |= OPENGL_NOT_READY;

    if (sCurrent) {
        if (egState & NO_CURRENT_SCENE == NO_CURRENT_SCENE)
            egState ^= NO_CURRENT_SCENE;
    }
    else
        egState |= NO_CURRENT_SCENE;

        if (threadExit)
            egState != ENGINE_STOPPED;

    if (egState != GameEngine::OK) {
        stringstream ss;
        ss << "Incomplete Engine Initialization" << endl;
        ss << "State Code : " << egState << endl << endl;
        if (egState & GameEngine::OPENGL_NOT_READY)
            ss << "* GL API Not Initialized" << endl;
        if (egState & GameEngine::NO_CURRENT_SCENE)
            ss << "* No Initial Scene assigned." << endl;
        if (egState & GameEngine::ENGINE_STOPPED)
            ss << "*Engine Already Stopped" << endl;

        stateString = ss.str();
    }
}