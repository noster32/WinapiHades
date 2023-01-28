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
}

void GameNode::update(void)
{
}

void GameNode::render(void)
{
}



