#include "Stdafx.h"
#include "TempSoundScene.h"

HRESULT TempSoundScene::init(void)
{
    TEMPSOUNDMANAGER->addMp3FileWithKey("����", "Resources/Sounds/MP3BGM.mp3");

    return S_OK;
}

void TempSoundScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('P'))
    {
        TEMPSOUNDMANAGER->playSoundWithKey("����");
    }
    if (KEYMANAGER->isOnceKeyDown('A'))
    {
        TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sounds/WAVBGM.wav");
    }
}
