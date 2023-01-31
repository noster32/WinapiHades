#pragma once
#include "Engineapi.h"
#include "scene.h"

struct EngineInit {
	HINSTANCE hInstance;
	int nCmdShow;
	HWND _hWnd;
	Point2D windowSize;
	string title;
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
	HWND _mainhWnd;
	HDC _hdc;
	HGLRC _hrc;
	bool isWindowsActive;
	int visibleHeight;

	//API
	EngineAPI& eg;
	GLAPI& gl;

	//멀티 쓰레드용
	mutex _mutex;
	bool threadExit;

	//엔진 State
	int egState;
	string stateString;

	scene* sCurrent;

	bool updateOnBackground;
	bool renderOnBackground;

	

public: 
	// Init, Release, Stop
	HRESULT engineInitializer(EngineInit& param);
	void engineRelease(void);
	void StopEngine() { PostMessage(_mainhWnd, WM_CLOSE, 0, 0); }

	// GameEngine Update
	void engineUpdate(void);
	void engineRender(void);

	// GameEngine State
	void engineStateUpdate(void);
	int GetEngineState() { return egState; }
	string GetEngineStateString() { return stateString; }

	//Threading Functions
	void SetExitThread() { threadExit = true; }
	bool GetExitThread() { return threadExit; }

protected:
	GameEngine();
	void SetInitialScene(scene* scene);
	virtual void CustomInitialize() { }
	virtual void CustomOnEngineRelease() { }
};

