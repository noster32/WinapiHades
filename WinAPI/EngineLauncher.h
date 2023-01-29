#pragma once
#include "GameEngine.h"

class EngineLauncher
{
private:
	static bool launched;
	static EngineLauncher* instance;
	
	EngineInit param;
	HWND mainWnd;
	GameEngine& engine;
	
	static const char szClassName[];
	static const char wdTitleText[];
	static const char wdAboutTitle[];
	static const char wdAboutText[];

	inline static LRESULT CALLBACK WndProcEntry(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);
	static DWORD ThreadUpdateEntry(void);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);
	DWORD ThreadUpdate(void);

	int InternalLaunch();

	void SetWindowSize(int x, int y, int width, int height);
public:
	EngineLauncher(GameEngine* instance, EngineInit init);
	int launch();

	
private:

};

