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

enum playerWeapon {
	SWORD = 0,
	BOW,
	FIST,
	SPEAR,
	GUN
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
	playerStatus ePlayerStatus;
	playerWeapon ePlayerWeapon;

	nFFmpeg playerIdle;
	nFFmpeg playerRunAnim;
	nFFmpeg playerDashAnim;
	nFFmpeg playerDashVFX;
	nFFmpeg playerAttackSwordAnim;
	nFFmpeg playerSpacialAttackSwordAnim;
	nFFmpeg playerAttackBowAnim;

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
	Rect2D playerAttackHitbox;
public:
	uint texture;
	uint renderOp;
	Point2D renderSize;

public:
	string FindStatus(playerStatus ps);
	void tempPlayerStatueUpdate();
	void playerMove();
	void PlayerAttack();

	void playerUpdate();

	void playerCommand();
	

	Vector2D getPlayerPosition() { return playerIdle.transformation.position; }

	Player() : renderOp(RenderObject::TEXTURE_SIZE) { }
	void SetTexture();
	void SetFFmpeg();

	int GetPlayerDepth() { return playerIdle.transformation.position.x + (playerIdle.transformation.position.y - 112); }

	virtual void Render() override;
};

