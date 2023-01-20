#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    IMAGEMANAGER->addImage("시작화면", "Resources/Images/Background/SkyBG.bmp", WINSIZE_X, WINSIZE_Y);

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
        SCENEMANAGER->changeScene("슈팅");
    }
}

void StartScene::render(void)
{
    IMAGEMANAGER->render("시작화면", getMemDC());
    TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));
}
