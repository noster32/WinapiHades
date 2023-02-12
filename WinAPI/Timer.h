#pragma once

#pragma region 타이머
/*
	▶ 타이머

	 - 기존에 사용한 API 공용 함수 (게임 쪽으로는 효율이 아주 별로)
	  ㄴ GetTickCount();
	  ㄴ GetTickCount64();

	 - 시간을 측정하는 함수들은 기본적으로 윈도우가 시작된 이후 지난 시간을 밀리 세컨드 단위로 반환한다.
	 - 밀리 세컨드보다 좀 더 정밀한 타이머를 원한다면 고성능 타이머를 구현해야 한다.
	 - 보통 타이머를 구현할 때는 두 가지를 기억하자.
	 ★★★★★
	  ㄴ 1. 해상도
	  ㄴ 2. 클럭 (진동 수)

	   ▷ 해상도란?
	    - 다양한 시간 함수들은 시간을 측정하기 위한 Tick 계산 로직이 있다.
		 ㄴ 보통 1분을 기준으로 얼마나 많은 프레임으로 나눌 수 있는지 계산.
		- 1분 동안 얼마나 많은 Tick으로 나눠서 시간의 정확도를 높이느냐가
		고해상도와 저해상도의 차이점이자 판단 기준.

	   ▷ Clock
	    - 타이머에서 얘기하는 클럭은 보통 CPU Clock을 의미한다.
		
		- 클럭이란?
		 ㄴ 클럭은 디지털 회로의 전기적 진동 수이며 Hz 단위로 표기.
		 ㄴ ex) 1초에 1Hz면 신호를 한 번 준다. (0 또는 1). 
		 ㄴ 1Ghz는 10의 9제곱 -> 1초에 10억 번 비트를 옮긴다.

	    - 타이머 단위
		 ㄴ Milli Second
		 ㄴ 10 Milli Second
		 ㄴ 100 Milli Second

		 ※ 고성능 타이머의 경우 중첩을 시키면 중첩을 시킨 만큼 효율이 올라간다. ★★★★★★★★★★
		  ㄴ 다만, 하지 말아야 할 업계 관행. 거지같은 코드를 짜고 하드웨어 로드율을 강제로 올린다.
		  ㄴ 타이머는 CPU와 램에서만 동작하기에 CPU와 램은 로드율이 높고, GPU는 낮은 현상이 발생.


	 - 
*/
#pragma endregion

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	double getElapsedTime();
	double getElapsedTimeInSec();
	double getElapsedTimeInMilliSec();
	double getElapsedTimeInMicroSec();


private:
	double startTimeInMicroSec;
	double endTimeInMicroSec;
	int stopped;

	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
};