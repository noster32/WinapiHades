#include "Stdafx.h"
#include "GameEngineBuilder.h"
#include "GameEngineImplement.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {

	GameEngineBuilder builder(hInstance, nCmdShow);
	builder.SetEngineInstance(&GameEngineImplement::GetInstance());
	builder.SetWindowSize(WINSIZE_X, WINSIZE_Y);
	builder.SetWindowTitle("Hades");
	builder.SetUpdateDelay(1000000 / 30);
	builder.SetRenderDelay(1000000 / 30);
	builder.Build()
		   .launch();
	
	return 0;
}