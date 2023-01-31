#include "Stdafx.h"
#include "SoundScene.h"
//using namespace
HRESULT SoundScene::init(void)
{
    IMAGEMANAGER->addImage("���� �����̽�", "Resources/Images/Background/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

    SOUNDMANAGER->addSound("����", "Resources/Sounds/Ilios - LostArk.mp3", true, true);


    return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        SOUNDMANAGER->play("����", 1.0f);
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        SOUNDMANAGER->stop("����");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
    {
        SOUNDMANAGER->pause("����");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
    {
        SOUNDMANAGER->resume("����");
    }
    //
    SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
   // IMAGEMANAGER->render("���� �����̽�", getMemDC());

}

/*
����1. ���� ���� 9�� ����

- ���Ϸ� ����
�� ����: �ù�37��_�̸�_�Ѵ�PPT
�� ���� ���뿡�� ��������

-�Ѵ� ��Ʈ������ PPT����

*/