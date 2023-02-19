#pragma once
#include "scene.h"

class BossScene : public scene
{
private:
	NamedTextureStorage nts;
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

