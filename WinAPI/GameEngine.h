#pragma once

struct EngineInit {
	HWND _hWnd;
	uint updateDelay;
	uint renderDelay;
	bool updateOnBackground;
	bool renderOnBackground;
};

class GameEngine
{
public:
	enum EngineState {
		OK = 0,
		OPENGL_NOT_READY = (1 << 0),
		NO_CURRENT_SCENE = (1 << 1),
		ENGINE_STOPPED = (1 << 2)
	};
private:

	HDC _hdc;
	HGLRC _hrc;
	bool isWindowsActive;
	int visibleHeight;

	//OpenGL API
	GLAPI gl;

	//��Ƽ �������
	mutex _mutex;
	bool threadExit;

	//���� State
	int egState;
	string stateString;

	bool updateOnBackground;
	bool renderOnBackground;

public: 
	HRESULT engineInitializer(EngineInit& param);
	void engineRelease(void);
	void engineUpdate(void);
	void engineRender(void);

	void engineStateUpdate(void);
	int GetEngineState() { return egState; }
	string GetEngineStateString() { return stateString; }

	void SetExitThread() { threadExit = true; }
	bool GetExitThread() { return threadExit; }

	void StopEngine() { PostMessage(_hWnd, WM_CLOSE, 0, 0); }
};

