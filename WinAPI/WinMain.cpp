#include "Stdafx.h"
#include "GameEngineBuilder.h"
#include "GameEngineImplement.h"

bool openGLWindowOpen = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {

	GameEngineBuilder builder(hInstance, nCmdShow);
	builder.SetEngineInstance(&GameEngineImplement::GetInstance());
	builder.SetWindowSize(WINSIZE_X, WINSIZE_Y);
	builder.SetWindowTitle("Hades");
	builder.SetUpdateDelay(1000000 / 60);
	builder.SetRenderDelay(1000000 / 60);
	builder.EnableRenderOnBackground();
	builder.EnableUpdateOnBackground();
	builder.Build()
		.launch();
	
	openGLWindowOpen = true;
	return 0;
}