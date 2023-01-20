#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),
                               _channel(nullptr),
                               _sound(nullptr)
{
}

HRESULT SoundManager::init(void)
{
    //사운드 시스템생성
    System_Create(&_system);
    // 0 -> driver data value
    //시스템 초기화
    _system->init(extraSoundChannel, FMOD_INIT_NORMAL, 0);

    //채널 수 만큼 메모리 버퍼 및 사운드를 생성하겠다.
    // ㄴ 채널수와 사운드 수는 맞춰 주는것이 좋다.
    _sound = new Sound * [extraSoundChannel];
    _channel = new Channel * [extraSoundChannel];

    //메모리 한번 밀자
    memset(_sound, 0, sizeof(Sound*) * (extraSoundChannel));
    memset(_channel, 0, sizeof(Channel*) * (extraSoundChannel));

    return S_OK ;
}

void SoundManager::release(void)
{
    //사운드 삭제
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
    
    //시스템 해제
    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }
}

void SoundManager::update(void)
{
    // FMOD 시스템 갱신
    // ㄴ 사운드 시스템 업데이트
    // ㄴ 볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼든등 다양한 작업을 자동으로 처리한
    _system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{

    if (loop)
    {
        if (background)
        {
            // 1대1 매칭
            _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }
        else
        {
            // 동시에 여러 음원 재생 가능. 다만, 안정성은 createStream()보다 떨어짐.
            _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }
    }
    else
    {
        _system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
    }

        // 맵에 사운드를 키 값과 함께 넣어준다.
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

