#pragma once
enum playerStatus {
	IDLE = 0,
	MOVE,
	DASH,
	MOVESTOP,
	ATTACK,
	ATTACK_END,
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


class PlayerImgVer
{
private:
	map<playerStatus, string> mPlayerStatus;
	playerStatus ePlayerStatus;
	playerWeapon ePlayerWeapon;

	int angle;
	int attackAngle;
	int dashAngle;
	int animLength;
	int animDelay;

	int tempX;
	int tempY;

	int temp;

	Vector2D dashDistance;
	Vector2D dir;

	int attackAnimCount;
	int attackResetDelay;
	int attackAnimMin;

	Rect2D playerHitbox;
	Rect2D playerAttackHitbox;

	uint animCount;
	bool soundPlayOnce;

public:
	uint texture;
	uint renderOp;
	Point2D renderSize;
	//비트 0x000001 = 정상
	//     0x000010 = 독 -> 플레이어 상태
public:
	string FindStatus(playerStatus ps);
	void tempPlayerStatueUpdate();
	void playerMove();
	void PlayerAttack();

	void playerUpdate();

	void playerCommand();

	Rect2D GetPlayerAttackHitBox() { return playerAttackHitbox; }
	int GetPlayerAngle() { return attackAngle; }

	//Vector2D getPlayerPosition() { return playerIdle.transformation.position; }

	void SetTexture();
	void SetFFmpeg();

	//int GetPlayerDepth() { return playerIdle.transformation.position.x + (playerIdle.transformation.position.y - 112); }

	//virtual void Render() override;
};

