#pragma once
#include "GameEngine.h"
#include "nFFmpeg.h"

class EngineLauncher
{
private:
	static bool launched;
	static EngineLauncher* instance;
	thread updateThread;
	thread ffmpegThread;
	
	EngineInit param;
	HWND mainWnd;
	GameEngine& engine;
	nFFmpeg* ffmpeg;
	
	static const char szClassName[];
	static const char wdTitleText[];
	static const char wdAboutTitle[];
	static const char wdAboutText[];

	inline static LRESULT CALLBACK WndProcEntry(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);
	static DWORD ThreadUpdateEntry(void);
	static DWORD FFmpegThreadUpdateEntry(void);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);
	DWORD ThreadUpdate(void);
	DWORD FFmpegThreadUpdate(void);

	int InternalLaunch();

	void SetWindowSize(int x, int y, int width, int height);
public:
	EngineLauncher(GameEngine* instance, EngineInit init);
	int launch();

	
private:

};

