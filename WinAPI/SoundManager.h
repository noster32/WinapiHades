#pragma once
#include "SingletonBase.h"

#pragma region FMOD
/*
FMOD
- Soud Engine ���̺귯��
- �𸮾�� ����Ƽ���� ���̼��� �Ծ����� �⺻����
- �̿� �����غ�
- ex CoCos2D

- fmode ��ǥ��
- ���̿� ��ũ

�� constexpr (Const Exdpression)

- C++ 11���� �߰��� Ű����
- ��ü�� �Լ� �տ� ���� �� �ִ� Ű����� �ش� ��ü�� �Լ��� ���ϰ��� ������ Ÿ�ӿ� �� �� ����


*/
#pragma endregion


//const / constexpr -> c++

constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;
//constexpr-> ���ø��̶� ��︰��

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

