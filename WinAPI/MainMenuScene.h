#pragma once
#include "scene.h"
#include "nFFmpeg.h"

class MainMenuScene : public scene
{
private:
	NamedTextureStorage nts;

	RenderObject startbutton;
	RenderObject endbutton;
	RenderObject testBox1;
	RenderObject testBox2;
	RenderObject testImg;

	nFFmpeg MainMenuIn;
	nFFmpeg MainMenuLoop;
	
	Rect2D startbuttonInter;
	bool start;
	bool startInEnd;

	Rect2D test;
	Rect2D test2;
public:
	void Init();

	virtual void OnBegin();
	virtual void OnEnd();

	virtual void OnUpdate();
	virtual void OnUpdateLoading();
	virtual void OnUpdateClosing();

	virtual void OnRenderLoading();
	virtual void OnRender();
	virtual void OnRenderClosing();
};

