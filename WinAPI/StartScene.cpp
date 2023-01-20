#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    IMAGEMANAGER->addImage("����ȭ��", "Resources/Images/Background/SkyBG.bmp", WINSIZE_X, WINSIZE_Y);

    wsprintf(_text, "Start Scene");

    return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
    {
        SCENEMANAGER->changeScene("����");
    }
}

void StartScene::render(void)
{
    IMAGEMANAGER->render("����ȭ��", getMemDC());
    TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));
}
