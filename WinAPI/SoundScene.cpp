#include "Stdafx.h"
#include "SoundScene.h"
//using namespace
HRESULT SoundScene::init(void)
{
    IMAGEMANAGER->addImage("데스 스페이스", "Resources/Images/Background/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

    SOUNDMANAGER->addSound("찬란", "Resources/Sounds/Ilios - LostArk.mp3", true, true);


    return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        SOUNDMANAGER->play("찬란", 1.0f);
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SOUNDMANAGER->stop("찬란");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
    {
        SOUNDMANAGER->pause("찬란");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
    {
        SOUNDMANAGER->resume("찬란");
    }
    //
    SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
   // IMAGEMANAGER->render("데드 스페이스", getMemDC());

}

/*
과제1. 내일 오전 9시 까지

- 메일로 제출
ㄴ 제목: 플밍37기_이름_한달PPT
ㄴ 메일 내용에는 선정게임

-한달 포트폴리오 PPT제출

*/