#include "Stdafx.h"
#include "GameNode.h"


GameNode::GameNode() : gl(GLAPI::GetInstance())
{
    this->threadExit = false;
}

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    if (managerInit)
    {
        //로케일 설정
        //ㄴ 어떤 언어를 기반으로 인코딩 / 문자, 열 출력을 결정할 것인지에 대해 설정해주는 함수
        //LC_ALL: 프로그램 전반에 대해서 적용하겠다.
        setlocale(LC_ALL, "Korean");

        SetTimer(_hWnd, 1, 10, NULL);

        RND->init();
        KEYMANAGER->init();
        IMAGEMANAGER->init();
        TEMPSOUNDMANAGER->init();
        TIMEMANAGER->init();
        SCENEMANAGER->init();
        SOUNDMANAGER->init();
    }

    return S_OK;
}

HRESULT GameNode::init(bool managerInit, EngineInit& param)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    RECT rect;
    GetClientRect(_hWnd, &rect);
    gl.EnableOpenGL(_hWnd, &_hdc, &_hrc, WINSIZE_PT);
    updateOnBackground = param.updateOnBackground;
    renderOnBackground = param.renderOnBackground;
    engineStateUpdate();

    if (managerInit)
    {
        setlocale(LC_ALL, "Korean");

        SetTimer(_hWnd, 1, 10, NULL);
        thread t1(&GameNode::update, this);

        RND->init();
        KEYMANAGER->init();
        IMAGEMANAGER->init();
        TEMPSOUNDMANAGER->init();
        TIMEMANAGER->init();
        SCENEMANAGER->init();
        SOUNDMANAGER->init();
    }

    return S_OK;
}



void GameNode::release(void)
{
    if (_managerInit)
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
    }
    _ptMouse;
    ReleaseDC(_hWnd, _hdc);
    gl.DisableOpenGL(_hWnd, _hdc, _hrc);
    _mutex.unlock();
    engineStateUpdate();
}

void GameNode::update(void)
{
    //??
    _mutex.lock();

    _mutex.unlock();
}

void GameNode::render(void)
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

void GameNode::engineStateUpdate(void)
{
    if (gl.GetSuccess()) {
        if (egState & OPENGL_NOT_READY == OPENGL_NOT_READY)
            egState ^= OPENGL_NOT_READY;
    } else

    if (threadExit)
        egState != ENGINE_STOPPED;

    if (egState != GameNode::OK) {
        stringstream ss;
        ss << "Incomplete Engine Initialization" << endl;
        ss << "State Code : " << egState << endl << endl;
        if (egState & GameNode::OPENGL_NOT_READY)
            ss << "* GL API Not Initialized" << endl;
        if (egState & GameNode::ENGINE_STOPPED)
            ss << "*Engine Already Stopped" << endl;

        stateString = ss.str();
    }
}

LRESULT GameNode::MainProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (IMessage)
    {
    case WM_CREATE:
        _hWnd = hWnd;

    case WM_TIMER:
        this->render();
        break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;

    case WM_LBUTTONDOWN:
   
        break;
    case WM_RBUTTONDOWN:
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;

        case VK_RIGHT:
            break;

        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_DESTROY: 
        PostQuitMessage(0);
        return 0;
    }

    return (DefWindowProc(hWnd, IMessage, wParam, lParam));
}

