#pragma once
#include "scene.h"
#include "Animation.h"

enum playerStatus {
	IDLE = 0,
	MOVE,
	DASH,
	STOP,
	ATTACK,
	SPECIAL_ATTACK,
	MAGIC,
	CALL,
	HIT,
	DIE,
	FISHING
};

class TestScene : public scene
{
private:
	map<playerStatus, string> mPlayerStatus;
	NamedTextureStorage nts;
	playerStatus ps;
	
	RenderObject fade;
	RenderObject bg;
	RenderObject player;
	RenderObject test;
	RenderObject testCut;
	RenderObject testSprite;
	RenderObject testAnim;
	RenderObject testAnimVfx;

	Animation tempAnim;
	Animation tempAnimVfx;

	SceneObject* animSelected;

	int frame;
	int tick, increment;
	int jump;
	bool gg;
	int angle;
	int animLength;
	int animDelay;

	int temp;
public:
	void Init();
	string FindStatus(playerStatus ps);
	void tempPlayerStatueUpdate();

	virtual void OnBegin();
	virtual void OnEnd();

	virtual void OnUpdate();
	virtual void OnUpdateLoading();
	virtual void OnUpdateClosing();

	virtual void OnRenderLoading();
	virtual void OnRender();
	virtual void OnRenderClosing();
};

