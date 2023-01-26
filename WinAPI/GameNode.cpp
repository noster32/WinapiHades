#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    RECT rect;
    GetClientRect(_hWnd, &rect);
    gl.EnableOpenGL(_hWnd, &_hdc, &_hrc, WINSIZE_PT);

    if (managerInit)
    {
        //������ ����
        //�� � �� ������� ���ڵ� / ����, �� ����� ������ �������� ���� �������ִ� �Լ�
        //LC_ALL: ���α׷� ���ݿ� ���ؼ� �����ϰڴ�.
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
}

void GameNode::update(void)
{
	// ���۸� ó���� Ÿ�̸Ӱ� ���� ������ �⺻ �Լ� ���
	// ���ΰ�ħ
	//InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
    gl.ClearBuffer();
    gl.LoadIdentity();
    gl.SwapBuffer();
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
