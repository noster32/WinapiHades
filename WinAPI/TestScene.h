#pragma once
#include "scene.h"
#include "Animation.h"

class TestScene : public scene
{
private:
	NamedTextureStorage nts;
	
	RenderObject fade;
	RenderObject bg;
	RenderObject player;
	RenderObject test;
	RenderObject testCut;
	RenderObject testSprite;
	RenderObject testAnim;

	Animation tempAnim;

	SceneObject* animSelected;

	int frame;
	int tick, increment;
	int jump;
	bool gg;
	int angle;

	int temp;
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

