#pragma once
class Animation
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;

private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;				//프레임 수
	int _frameWidth;			//프레임 가로크기
	int _frameHeight;			//프레임 세로크기
	int _frameNumWidth;			//가로 프레임 총 갯수
	int _frameNumHeight;		//세로 프레임 총 갯수

	float _frameUpdateSec;		//초당 프레임 업데이트 수
	float _elapsedSec;			//프레임과 프레임 사이의 시간

	bool _isPlay;				//플레이중?
	bool _loop;					//반복중?
	DWORD _nowPlayIdx;			//현재 플레이 인덱스


public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);
	
	//frameRender 에서 반복여부랑, 역재생 여부
	void setDefPlayFrame(bool reverse = false, bool loop = false);
	//원하는 프레임만 출력해주기 위한 함수
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);
	//start ~ end 까지 반복할 수 있는 함수
	void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);

	//외부에서 사용할 수도 있기 떄문에 만들어둠
	void aniStart(void);
	void aniStop(void);
	void aniPause(void);
	void aniResume(void);

	//플레이 중인지?
	inline bool isPlay(void) { return _isPlay; }

	//프레임 위치 얻어온다. -> 캐릭터 죽는모션에 사용가능
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	// 현재 애니메이션의 프레임 순서를 얻어온다.
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	//프레임 가로 크기를 얻어온다.
	inline int getFrameWidth(void) { return _frameWidth; }
	//프레임 세로 크기를 얻어온다.
	inline int getFrameHeight(void) { return _frameHeight; }

	//현재 몇번째 프레임 순서인지 얻는다.
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }


	Animation(void);
	~Animation() {}
};

