#include "Stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{
	//QueryPerformanceFrequency(): 1초당 진동수를 체크하며
	//고성능 타이머를 지원하면 t / 아니라면 f 반환
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		//QueryPerformanceCounter(): 특정 시점에 몇번 진동을 했는지 체크하는 함수
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		
		//초당 시간을 계산할 수 있는 시간 주기
		_timeScale = 1.0f / _periodFrequency;
	}
	
	//고성능 타이머 지원을 안한다면
	else
	{
		_isHardware = false;

		//timeGetTime(): 보통 멀티미디어 타이머라고 불린다.
		//운영체제가 시작되고 현재까지 흐른 시간을 밀리 세컨 단위로 반환
		_lastTime = timeGetTime(); 
		//ㄴ GetTickCount()보다 정밀도가 훨씬 좋지만 하드웨어에 영향을 받기 때문에 좋진 않지만 어쩔수 없이 사용
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

//현재 시간 계산
void Timer::tick(float lockFPS) //lockFPS -> 최대 프레임을 막아주는 기능이 WINAPI에 없기 때문에 따로 제한을둠
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}

	else
	{
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재 시간의 경과량 측정
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
