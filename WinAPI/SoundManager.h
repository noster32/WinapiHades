#pragma once
#include "SingletonBase.h"

#pragma region FMOD
/*
FMOD
- Soud Engine 라이브러리
- 언리얼과 유니티에는 라이선스 게약으로 기본내장
- 이외 선행준비
- ex CoCos2D

- fmode 대표작
- 바이오 쇼크

▶ constexpr (Const Exdpression)

- C++ 11에서 추가된 키워드
- 객체나 함수 앞에 붙일 수 있는 키워드로 해당 객체나 함수의 리턴값을 컴파일 타임에 알 수 없다


*/
#pragma endregion


//const / constexpr -> c++

constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;
//constexpr-> 탬플릿이랑 어울린다

//templet 
using namespace FMOD;

class SoundManager : public SingletonBase <SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;

	System* _system;
	Sound** _sound;
	Channel** _channel;
	//project -> * FMOD.hpp -> * core File

	arrSounds _mTotalSounds;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool background, bool loop);
	void play(string keyName, float volume);
	void pause(string keyName);
	void stop(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	SoundManager();
	~SoundManager() {}
};

