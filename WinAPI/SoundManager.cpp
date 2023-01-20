#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
                               _channel(nullptr),
                               _sound(nullptr)
{
}

HRESULT SoundManager::init(void)
{
    //���� �ý��ۻ���
    System_Create(&_system);
    // 0 -> driver data value
    //�ý��� �ʱ�ȭ
    _system->init(extraSoundChannel, FMOD_INIT_NORMAL, 0);

    //ä�� �� ��ŭ �޸� ���� �� ���带 �����ϰڴ�.
    // �� ä�μ��� ���� ���� ���� �ִ°��� ����.
    _sound = new Sound * [extraSoundChannel];
    _channel = new Channel * [extraSoundChannel];

    //�޸� �ѹ� ����
    memset(_sound, 0, sizeof(Sound*) * (extraSoundChannel));
    memset(_channel, 0, sizeof(Channel*) * (extraSoundChannel));

    return S_OK ;
}

void SoundManager::release(void)
{
    //���� ����
    if (_channel != nullptr || _sound != nullptr)
    {
        for (int i = 0; i < extraSoundChannel; i++)
        {
            if (_channel != nullptr)
            {
                if (_channel[i]) _channel[i]->stop();;
            }

            if (_sound != nullptr)
            {
                if (_sound != nullptr) _sound[i]->release();
            }
        }
    }

    SAFE_DELETE_ARRAY(_channel);
    SAFE_DELETE_ARRAY(_sound);
    
    //�ý��� ����
    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }
}

void SoundManager::update(void)
{
    // FMOD �ý��� ����
    // �� ���� �ý��� ������Ʈ
    // �� ������ �ٲ�ų� ����� ���� ���带 ä�ο��� ����� �پ��� �۾��� �ڵ����� ó����
    _system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{

    if (loop)
    {
        if (background)
        {
            // 1��1 ��Ī
            _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }
        else
        {
            // ���ÿ� ���� ���� ��� ����. �ٸ�, �������� createStream()���� ������.
            _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }
    }
    else
    {
        _system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
    }

        // �ʿ� ���带 Ű ���� �Բ� �־��ش�.
    _mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

}

void SoundManager::play(string keyName, float volume)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            //_system->playSound(_sound[count], NULL, false, &_channel[count]);
            _system->playSound(*iter->second, NULL, false, &_channel[count]);

            _channel[count]->setVolume(volume);

            break;
        }
    }
}

void SoundManager::stop(string keyName)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->stop();
            break;
        }
    }
}

void SoundManager::pause(string keyName)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(true);
            break;
        }
    }
}


void SoundManager::resume(string keyName)
{
    arrSoundIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(false);
            break;
        }
    }
}

bool SoundManager::isPlaySound(string keyName)
{
    bool isPlay;
    int count = 0;

    arrSoundIter iter = _mTotalSounds.begin();
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPlay);
            break;
        }
    }

    return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
    bool isPause;
    int count = 0;

    arrSoundIter iter = _mTotalSounds.begin();
    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPause);
            break;
        }
    }

    return isPause;
}

