#include "Stdafx.h"
#include "Animation.h"

							//멤버 이니셜라이져
Animation::Animation(void) : _frameNum(0),
							 _frameWidth(0),
							 _frameHeight(0),
							 _frameNumWidth(0),
							 _frameNumHeight(0),
							 _frameUpdateSec(0),
							 _elapsedSec(0),
							 _nowPlayIdx(0),
							 _isPlay(false),
							 _loop(false)
{
}

HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH)
{
	// 가로 프레임 수
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	_frameList.clear();

	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	// 기본 프레임 셋팅
	setDefPlayFrame();

	return S_OK;
}

void Animation::release(void)
{
	//! Do Nothing
}

// 기본 프레임 셋팅
void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	//다시 돌아오냐? (왕복)
	if (reverse)
	{
		//루프?
		if (_loop)
		{
			//정방향 순환 (갈떄)
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때) //-2를 한 이유는 aniStart()의 예외처리
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}

		else
		{
			//정방향 순환 (갈떄)
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때)
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//편도
	else
	{
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//원하는 프레임만 재생
void Animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (_loop)
	{
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}

		for (int i = arrLen - 2; i > 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}

		for (int i = arrLen - 2; i >= 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
}

//구간을 잘라서 재생
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (start <= 0) start = 0;
	if (end >= _frameNum) end = _frameNum;
	if (start > end)
	{
		int temp = start;
		start = end;
		end = temp;
	}

	//다시 돌아오냐? (왕복)
	if (reverse)
	{
		//루프?
		if (_loop)
		{
			//정방향 순환 (갈떄)
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때) //-2를 한 이유는 aniStart()의 예외처리
			for (int i = end - 2; i > start; i--)
			{
				_playList.push_back(i);
			}
		}

		else
		{
			//정방향 순환 (갈떄)
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때)
			for (int i = end - 2; i >= start; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//편도
	else
	{
		for (int i = start; i < end; i++)
		{
			_playList.push_back(i);
		}
	}
}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1 / (float)framePerSec ;
}

void Animation::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;
		cout << _elapsedSec << endl;

		//프레임 업데이트 시간이 되었으면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;

			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIdx = 0;
				}


				else
				{
					_nowPlayIdx--;
					_isPlay = false;
				}

			}
		}
	}

}

void Animation::aniStart(void)
{
	_isPlay = true;
	_nowPlayIdx = 0;
}

void Animation::aniStop(void)
{
	_isPlay = false;
	_nowPlayIdx = 0;
}

void Animation::aniPause(void)
{
	_isPlay = false;
}

void Animation::aniResume(void)
{
	_isPlay = true;
}

/*
과제 1. 애니메이션 클래스

- 미완성 함수 완성 시키기
ㄴ 원하는 프레임만 재생 -> setPlayFrame()
ㄴ 구간을 잘라서 재생 -> setPlayFrame()
ㄴ 초당 프레임 갱신 횟수 -> setFPS()


★ Semi Portfolio - 1945같은 게임, 한쪽만 부서지는거 -> 픽충으로 가능
ㄴ 28일까지
과제 2. 비행기 슈팅 게임

- 팀간 상의하여 일정 조율
- 세로운 이미지 필수
- 스타트 씬과 / 게임 씬으로 구성
- 적을 죽이면 점수를 획득 / 플레이어의 체력이 일정 이하로 떨어지면 게임 오버
- 적을 모두 죽이면 스테이지가 바뀌면서 보스 출현 (자연스럽게)
- 보스를 죽이면 게임 클리어
*/