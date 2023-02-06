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


class Player : public scene
{
private:
	map<playerStatus, string> mPlayerStatus;
	playerStatus ps;
	NamedTextureStorage nts;

	RenderObject testSprite;
	RenderObject testAnim;
	RenderObject testAnimVfx;

	Animation tempAnim;
	Animation tempAnimVfx;

	int angle;
	int dashAngle;
	int animLength;
	int animDelay;
public:
	string FindStatus(playerStatus ps);
	void tempPlayerStatueUpdate();

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

