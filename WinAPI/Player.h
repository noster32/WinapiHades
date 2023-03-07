#pragma once
#include "RenderObject.h"
#include "nFFmpeg.h"
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

class Player : public RenderObject
{
private:
	enum RenderingOption {
		TEXTURE_SIZE = (1 << 0),
		GIVEN_SIZE = (1 << 1),
		STRETCH_HOR = (1 << 2),
		STRETCH_VER = (1 << 3),
		FIT_TO_SCREEN = (STRETCH_HOR | STRETCH_VER),
		FIT_TO_SCREEN_KEEP_RATIO = (1 << 4)
	};
private:	
	map<playerStatus, string> mPlayerStatus;
	playerStatus ps;
	playerMoveDir pmr;

	nFFmpeg testFFmpeg;
	nFFmpeg playerRunAnim;
	nFFmpeg playerDashAnim;
	nFFmpeg playerDashVFX;
	nFFmpeg playerAttackSwordAnim;
	nFFmpeg playerSpacialAttackSwordAnim;

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
	int swordAttackAnimCount;
	int attackResetDelay;
	int attackAnimMin;

	Rect2D playerHitbox;
	Rect2D playerAttack;
public:
	uint texture;
	uint renderOp;
	Point2D renderSize;

public:
	string FindStatus(playerStatus ps);
	void tempPlayerStatueUpdate();
	void playerMove(playerMoveDir pmr);

	void playerUpdate();

	void playerCommand();
	

	Vector2D getPlayerPosition() { return testFFmpeg.transformation.position; }

	Player() : renderOp(RenderObject::TEXTURE_SIZE) { }
	void SetTexture();
	void SetFFmpeg();

	int GetPlayerDepth() { return testFFmpeg.transformation.position.x + (testFFmpeg.transformation.position.y - 112); }

	virtual void Render() override;
};

