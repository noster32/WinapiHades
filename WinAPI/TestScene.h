#pragma once
#include "scene.h"

class TestScene : public scene
{
private:
	NamedTextureStorage nts;
	
	SceneObject hidden;
	RenderObject fade;
	RenderObject bg;
	RenderObject player;
	RenderObject test;

	int frame;
	int tick, increment;
	int jump;
	bool gg;

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

