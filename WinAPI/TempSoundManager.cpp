#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
    return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
    // mp3 ���� ��ü ��������, mp3 Ÿ���� ã�� �ڵ�
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    // mciSendString(): ��ġ�� ���� ��ɾ �����Ͽ� ������Ų��.
    //  �� ����: ���ڿ� ��ɾ�, ��ȯ���� �˷��� ���ڿ�, ��ȯ�� ����, �ݹ� (�ڵ�)
    // mp3 Ÿ���� ������ ����.
    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveaudio alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
    //PlaySound(): ���� ��� �Լ�. ���迡�� �׽�Ʈ������ ���� ����. ������.
    //  �� ����: ���� �̸�(���� ���), ���ҽ��� ����ϸ� �ش� �ν��Ͻ� �ڵ�, fdwSound( �ɼ� | �ɼ� | �ɼ� )

    /*
       SND_ASYNC: �񵿱� �ɼ�. ����ϸ鼭 ���� �ڵ� ���� (�񵿱� �÷���)
       SND_LOOP: �ݺ� ���
       SND_NODEFAULT: ���� ��ο� ������ ��� ������(�����) ��� X.
    */

    PlaySound(fileName, NULL, SND_ASYNC);
}

void TempSoundManager::playSoundWithKey(string key)
{
    string first = "play ";
    string finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
    string first = "stop ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}