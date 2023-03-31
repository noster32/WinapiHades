#pragma once
#include "scene.h"
#include "nFFmpeg.h"

class MainMenuScene : public scene
{
private:
	NamedTextureStorage nts;

	RenderObject startbutton;
	RenderObject endbutton;

	nFFmpeg MainMenuLoop;
	
	Rect2D startbuttonInter;
	Rect2D stopbuttonInter; 
	bool start;
	bool startInEnd;

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

