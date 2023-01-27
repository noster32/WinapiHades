#pragma once
#include "GImage.h"

struct EngineInit {
	uint updateDelay;
	uint renderDelay;
	bool updateOnBackground;
	bool renderOnBackground;
};

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
public:
	enum EngineState {
		OK					= 0,
		OPENGL_NOT_READY	= (1<<0),
		NO_CURRENT_SCENE	= (1<<1),
		ENGINE_STOPPED		= (1<<2)
	};
private:
	
	HDC _hdc;
	HGLRC _hrc;
	bool _managerInit;
	bool isWindowsActive;
	int visibleHeight;

	//OpenGL API
	GLAPI gl;

	//멀티 쓰레드용
	mutex _mutex;
	bool threadExit;

	//엔진 State
	int egState;
	string stateString;
	
	bool updateOnBackground;
	bool renderOnBackground;

public:
	// HRESULT: 함수가 성공적으로 실행되었는지 체크
	// ㄴ 32비트 signed 정수(음수가 아닌 값들은 성공을 의미하며 음수값들은 실패를 의미한다.)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(bool managerInit, EngineInit& param);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void engineStateUpdate(void);

	GImage* getBackBuffer(void) { return _backBuffer; }

	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기(화면 DC)
	HDC getHDC() { return _hdc; }

	int GetEngineState() { return egState; }
	string GetEngineStateString() { return stateString; }

	void SetExitThread() { threadExit = true; }
	bool GetExitThread() { return threadExit; }

	LRESULT MainProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode() {}
};

