#include "Stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{
	//QueryPerformanceFrequency(): 1�ʴ� �������� üũ�ϸ�
	//���� Ÿ�̸Ӹ� �����ϸ� t / �ƴ϶�� f ��ȯ
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		//QueryPerformanceCounter(): Ư�� ������ ��� ������ �ߴ��� üũ�ϴ� �Լ�
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		
		//�ʴ� �ð��� ����� �� �ִ� �ð� �ֱ�
		_timeScale = 1.0f / _periodFrequency;
	}
	
	//���� Ÿ�̸� ������ ���Ѵٸ�
	else
	{
		_isHardware = false;

		//timeGetTime(): ���� ��Ƽ�̵�� Ÿ�̸Ӷ�� �Ҹ���.
		//�ü���� ���۵ǰ� ������� �帥 �ð��� �и� ���� ������ ��ȯ
		_lastTime = timeGetTime(); 
		//�� GetTickCount()���� ���е��� �ξ� ������ �ϵ��� ������ �ޱ� ������ ���� ������ ��¿�� ���� ���
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

//���� �ð� ���
void Timer::tick(float lockFPS) //lockFPS -> �ִ� �������� �����ִ� ����� WINAPI�� ���� ������ ���� ��������
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}

	else
	{
		_curTime = timeGetTime();
	}

	//������ �ð��� ���� �ð��� ����� ����
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::getFrameRate(char* str) const
{
	if (str != nullptr)
	{
		wsprintf(str, "FPS: %d", _frameRate);
	}



	return _frameRate;
}
