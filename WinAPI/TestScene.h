#pragma once
#include "scene.h"
#include "Animation.h"

enum playerStatus {
	IDLE = 0,
	MOVE,
	DASH,
	MOVESTOP,
	ATTACK,
	SPECIAL_ATTACK,
	MAGIC,
	CALL,
	HIT,
	DIE,
	FISHING
};

enum playerMoveDir {
	RIGHT,
	RIGHTUP,
	UP,
	LEFTUP,
	LEFT,
	LEFTDOWN,
	DOWN,
	RIGHTDOWN
};

class TestScene : public scene
{
private:
	map<playerStatus, string> mPlayerStatus;
	NamedTextureStorage nts;
	playerStatus ps;
	playerMoveDir pmr;
	
	RenderObject fade;
	RenderObject bg;
	RenderObject test;
	RenderObject testCut;
	RenderObject testSprite;
	RenderObject tempMap;
	RenderObject testOrb;
	RenderObject Orb1;
	RenderObject enemyHitbox;

	nFFmpeg testFFmpeg;
	nFFmpeg playerRunAnim;
	nFFmpeg playerDashAnim;
	nFFmpeg playerDashVFX;
	nFFmpeg playerAttackSwordAnim;

	
	nFFmpeg Skelly;

	Animation tempAnim;
	Animation tempAnimVfx;
	Animation tempObjAnim;
	Animation OrbAnim;

	SceneObject* animSelected;

	int frame;
	int tick, increment;
	int jump;
	bool gg;
	int angle;
	int dashAngle;
	int animLength;
	int animDelay;


	int tempX;
	int tempY;

	int temp;

	Vector2D dashDistance;
	Vector2D dir;

	bool SwordAttack1;
	bool SwordAttack2;
	bool SwordAttack3;
	int attackResetDelay;
	int attackAnimMin;
public:
	void Init();
	string FindStatus(playerStatus ps);
	void tempPlayerStatueUpdate();
	int transformAngle(int angle, playerStatus ps);
	void setPlayerAngle(void);
	void playerMove(playerMoveDir pmr);

	virtual void OnBegin();
	virtual void OnEnd();

	virtual void OnUpdate();
	virtual void OnUpdateLoading();
	virtual void OnUpdateClosing();

	virtual void OnRenderLoading();
	virtual void OnRender();
	virtual void OnRenderClosing();
};

