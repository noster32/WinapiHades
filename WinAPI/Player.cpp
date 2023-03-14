#include "Stdafx.h"
#include "Player.h"

void Player::SetTexture()
{
	//TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	//this->texture = gl.LoadTexturePng("Resources/Images/Object/idle.png", param);
	//this->transformation.position = Vector2D(2000, 500);
}

void Player::SetFFmpeg()
{
	playerIdle.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusIdle_Bink.avi");
	playerRunAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusRun_Bink.avi");
	playerDashAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusDash_Bink.avi");
	playerDashVFX.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusDashVFX_Bink.avi");
	playerAttackSwordAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusSword_Bink.avi");
	playerSpacialAttackSwordAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusSwordParry_Bink.avi");
	playerAttackBowAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusBow_Bink.avi");
	playerSpecialAttackBowAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusBowRapidFire_Bink.avi");
	playerAttackFistAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusFistFlurryPunch_Bink.avi");
	playerSpecialAttackFistAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusFistFlashKick_Bink.avi");
	playerAttackSpearAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusSpear_Bink.avi");
	playerChargeAttackSpearAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusSpearSpin_Bink.avi");
	//playerIdle.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusIdle_Bink.avi");
	//playerRunAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusRun_Bink.avi");
	//playerDashAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDash_Bink.avi");
	//playerDashVFX.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDashVFX_Bink.avi");
	//playerAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSword_Bink.avi");
	//playerSpacialAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSwordParry_Bink.avi");
	//playerAttackBowAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusBow_Bink.avi");
	//playerSpecialAttackBowAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusBowRapidFire_Bink.avi");
	//playerAttackFistAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusFistFlurryPunch_Bink.avi");
	//playerSpecialAttackFistAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusFistFlashKick_Bink.avi");
	//playerAttackSpearAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSpear_Bink.avi");
	//playerChargeAttackSpearAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSpearSpin_Bink.avi");


	playerIdle.transformation.position = Vector2D(2500, 800);
	playerIdle.transformation.anchor = Anchor::CENTER;
	playerIdle.transformation.scale -= 0.1f;
	//testFFmpeg.SetDepth(20);
	playerRunAnim.transformation.position = playerIdle.transformation.position;
	playerRunAnim.transformation.anchor = Anchor::CENTER;
	playerRunAnim.transformation.scale -= 0.1f;
	//playerRunAnim.SetDepth(20);
	playerDashAnim.transformation.position = playerIdle.transformation.position;
	playerDashAnim.transformation.anchor = Anchor::CENTER;
	playerDashAnim.transformation.scale -= 0.1f;
	//playerDashAnim.SetDepth(20);
	playerDashVFX.transformation.position = playerIdle.transformation.position;
	playerDashVFX.transformation.anchor = Anchor::CENTER;
	playerDashVFX.transformation.scale -= 0.1f;
	//playerDashVFX.SetDepth(20);
	playerAttackSwordAnim.transformation.position = playerIdle.transformation.position + Vector2D(0, 10);
	playerAttackSwordAnim.transformation.anchor = Anchor::CENTER;
	playerAttackSwordAnim.transformation.scale -= 0.1f;
	//playerAttackSwordAnim.SetDepth(20);
	playerSpacialAttackSwordAnim.transformation.position = playerIdle.transformation.position;
	playerSpacialAttackSwordAnim.transformation.anchor = Anchor::CENTER;
	playerSpacialAttackSwordAnim.transformation.scale -= 0.1f;
	//playerSpacialAttackSwordAnim.SetDepth(20);
	playerAttackBowAnim.transformation.position = playerIdle.transformation.position;
	playerAttackBowAnim.transformation.anchor = Anchor::CENTER;
	playerAttackBowAnim.transformation.scale -= 0.1f;
	playerSpecialAttackBowAnim.transformation.position = playerIdle.transformation.position;
	playerSpecialAttackBowAnim.transformation.anchor = Anchor::CENTER;
	playerSpecialAttackBowAnim.transformation.scale -= 0.1f;
	playerAttackFistAnim.transformation.position = playerIdle.transformation.position;
	playerAttackFistAnim.transformation.anchor = Anchor::CENTER;
	playerAttackFistAnim.transformation.scale -= 0.1f;
	playerSpecialAttackFistAnim.transformation.position = playerIdle.transformation.position;
	playerSpecialAttackFistAnim.transformation.anchor = Anchor::CENTER;
	playerSpecialAttackFistAnim.transformation.scale -= 0.1f;
	playerAttackSpearAnim.transformation.position = playerIdle.transformation.position;
	playerAttackSpearAnim.transformation.anchor = Anchor::CENTER;
	playerAttackSpearAnim.transformation.scale -= 0.1f;

	SOUNDMANAGER->addSound("footstep", "Resources/Sounds/ZagFootstepsHardSurfaceRun_2.wav", false, true);
	SOUNDMANAGER->addSound("dash", "Resources/Sounds/ZagreusDash.wav", false, false);
	SOUNDMANAGER->addSound("BowCharge", "Resources/Sounds/ZagreusBowCharge2.wav", false, false);
	SOUNDMANAGER->addSound("BowFire", "Resources/Sounds/ZagreusBowFire2.wav", false, false);
	SOUNDMANAGER->addSound("ZagSwordAttackSound1", "Resources/Sounds/ZagreusEmoteAttackingSword_1.wav", false, false);
	SOUNDMANAGER->addSound("ZagSwordAttackSound2", "Resources/Sounds/ZagreusEmoteAttackingSword_3.wav", false, false);
	SOUNDMANAGER->addSound("ZagSwordAttackSound3", "Resources/Sounds/ZagreusEmoteAttackingSword_4.wav", false, false);
	SOUNDMANAGER->addSound("SwordAttackSound1", "Resources/Sounds/ZagreusSwordSwipe.wav", false, false);
	SOUNDMANAGER->addSound("SwordAttackSound2", "Resources/Sounds/ZagreusSwordOverhead.wav", false, false);
	SOUNDMANAGER->addSound("SwordAttackSound3", "Resources/Sounds/ZagreusSwordLunge.wav", false, false);
	SOUNDMANAGER->addSound("SwordParry", "Resources/Sounds/ZagreusSwordParry.wav", false, false);
	SOUNDMANAGER->addSound("BowRapidFire", "Resources/Sounds/ZagreusBowRapidFireAttack.wav", false, false);
	
	mPlayerStatus.insert(make_pair(IDLE, "IDLE"));
	mPlayerStatus.insert(make_pair(MOVE, "MOVE"));
	mPlayerStatus.insert(make_pair(DASH, "DASH"));
	mPlayerStatus.insert(make_pair(MOVESTOP, "MOVESTOP"));
	mPlayerStatus.insert(make_pair(ATTACK, "ATTACK"));
	mPlayerStatus.insert(make_pair(SPECIAL_ATTACK, "SPECIALATTACK"));
	mPlayerStatus.insert(make_pair(MAGIC, "MAGIC"));
	mPlayerStatus.insert(make_pair(CALL, "CALL"));
	mPlayerStatus.insert(make_pair(HIT, "HIT"));
	mPlayerStatus.insert(make_pair(DIE, "DIE"));
	mPlayerStatus.insert(make_pair(FISHING, "FISHING"));

	ePlayerStatus = IDLE;
	ePlayerWeapon = SPEAR;
	soundPlayOnce = false;

	//playerAttackHitbox = Rect2D()
}



string Player::FindStatus(playerStatus ps)
{
	map<playerStatus, string>::iterator iter(mPlayerStatus.find(ps));
	return (iter != mPlayerStatus.end()) ? iter->second : 0;
}

void Player::tempPlayerStatueUpdate()
{
	//pw bow Ãß°¡
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isStayKeyDown(VK_LBUTTON) || playerAttackSwordAnim.GetAnimPlaying() || playerAttackFistAnim.GetAnimPlaying() || playerAttackSpearAnim.GetAnimPlaying())
	{
		ePlayerStatus = ATTACK;
	}

	else if (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || playerDashAnim.GetAnimPlaying())
		{
			ePlayerStatus = DASH;
		}
		else
			ePlayerStatus = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || playerDashAnim.GetAnimPlaying())
	{
		ePlayerStatus = DASH;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) || playerAttackBowAnim.GetAnimPlaying()) {
		ePlayerStatus = ATTACK_END;
	}
	else
		ePlayerStatus = IDLE;

	if (KEYMANAGER->isOnceKeyDown('Q') || playerSpacialAttackSwordAnim.GetAnimPlaying() || playerSpecialAttackBowAnim.GetAnimPlaying()) {
		ePlayerStatus = SPECIAL_ATTACK;
	}

	switch (ePlayerStatus)
	{
	case IDLE:
		playerIdle.SetEnable(true);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(false);
		playerAttackFistAnim.SetEnable(false);
		playerAttackSpearAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerSpecialAttackBowAnim.SetEnable(false);
		playerSpecialAttackFistAnim.SetEnable(false);
		break;
	case MOVE:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(true);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(false);
		playerAttackFistAnim.SetEnable(false);
		playerAttackSpearAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerSpecialAttackBowAnim.SetEnable(false);
		break;
	case DASH:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(true);
		playerDashVFX.SetEnable(true);
		playerAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(false);
		playerAttackFistAnim.SetEnable(false);
		playerAttackSpearAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerSpecialAttackBowAnim.SetEnable(false);
		break;
	case MOVESTOP:
		break;
	case ATTACK:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		if (ePlayerWeapon == SWORD) {
			playerAttackSwordAnim.SetEnable(true);
			playerAttackBowAnim.SetEnable(false);
			playerAttackFistAnim.SetEnable(false);
			playerAttackSpearAnim.SetEnable(false);
		}
		else if (ePlayerWeapon == BOW) {
			playerAttackSwordAnim.SetEnable(false);
			playerAttackBowAnim.SetEnable(true);
			playerAttackFistAnim.SetEnable(false);
			playerAttackSpearAnim.SetEnable(false);
		}
		else if (ePlayerWeapon == FIST) {
			playerAttackSwordAnim.SetEnable(false);
			playerAttackBowAnim.SetEnable(false);
			playerAttackFistAnim.SetEnable(true);
			playerAttackSpearAnim.SetEnable(false);
		}
		else if (ePlayerWeapon == SPEAR) {
			playerAttackSwordAnim.SetEnable(false);
			playerAttackBowAnim.SetEnable(false);
			playerAttackFistAnim.SetEnable(false);
			playerAttackSpearAnim.SetEnable(true);
		}
		else if (ePlayerWeapon == GUN) {
			playerAttackSwordAnim.SetEnable(false);
			playerAttackBowAnim.SetEnable(false);
			playerAttackFistAnim.SetEnable(false);
			playerAttackSpearAnim.SetEnable(false);
		}
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerSpecialAttackBowAnim.SetEnable(false);
		break;
	case SPECIAL_ATTACK:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(false);
		if (ePlayerWeapon == SWORD) {
			playerSpacialAttackSwordAnim.SetEnable(true);
			playerSpecialAttackBowAnim.SetEnable(false);
			playerSpecialAttackFistAnim.SetEnable(false);
		}
		else if (ePlayerWeapon == BOW) {
			playerSpacialAttackSwordAnim.SetEnable(false);
			playerSpecialAttackBowAnim.SetEnable(true);
			playerSpecialAttackFistAnim.SetEnable(false);
		}
		else if (ePlayerWeapon == FIST) {
			playerSpacialAttackSwordAnim.SetEnable(false);
			playerSpecialAttackBowAnim.SetEnable(false);
			playerSpecialAttackFistAnim.SetEnable(true);
		}
		break;
	case MAGIC:
		break;
	case CALL:
		break;
	case HIT:
		break;
	case DIE:
		break;
	case FISHING:
		break;
	default:
		animLength = 24;
		break;
	}

}

void Player::playerMove()
{
	if (ePlayerStatus == DASH)
	{
		Point2D tempA = Point2D(playerIdle.transformation.position.x, playerIdle.transformation.position.y);
		Point2D tempB = Point2D(dashDistance.x, dashDistance.y);

		if (tempA != tempB)
		{
			playerIdle.transformation.position += dir * 80;
			cout << playerIdle.transformation.position.x << ", " << playerIdle.transformation.position.y << endl;
		}
	}
	
	playerRunAnim.transformation.position = playerIdle.transformation.position;
	playerDashAnim.transformation.position = playerIdle.transformation.position;
	playerDashVFX.transformation.position = playerIdle.transformation.position;
	playerAttackSwordAnim.transformation.position = playerIdle.transformation.position + Vector2D(0, 30);
	playerSpacialAttackSwordAnim.transformation.position = playerIdle.transformation.position + Vector2D(0, 30);
	playerAttackBowAnim.transformation.position = playerIdle.transformation.position;
	playerSpecialAttackBowAnim.transformation.position = playerIdle.transformation.position;
	playerAttackFistAnim.transformation.position = playerIdle.transformation.position;
	playerAttackSpearAnim.transformation.position = playerIdle.transformation.position;
}

void Player::PlayerAttack()
{
	if(ePlayerWeapon == SWORD) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !playerAttackSwordAnim.GetAnimPlaying()) {
			attackAngle = getAngle(playerIdle.transformation.position.x, playerIdle.transformation.position.y,
				(_ptMouse.x - WINSIZE_X / 2) + playerIdle.transformation.position.x,
				(_ptMouse.y - WINSIZE_Y / 2) + playerIdle.transformation.position.y);
			float tempAngle2 = (360 - (attackAngle * 180 / PI)) / 11.25f;
			angle = tempAngle2;
			if (swordAttackAnimCount == 3)
				swordAttackAnimCount = 1;
			else
				swordAttackAnimCount++;

			if (swordAttackAnimCount == 2) {
				attackAnimMin = 800000;
				SOUNDMANAGER->play("SwordAttackSound2", 0.5f);
				//SOUNDMANAGER->play("ZagSwordAttackSound2", 0.5f);
			}
			else if (swordAttackAnimCount == 3) {
				attackAnimMin = 1400000;
				SOUNDMANAGER->play("SwordAttackSound3", 0.5f);
				//SOUNDMANAGER->play("ZagSwordAttackSound3", 0.5f);
			}
			else {
				attackAnimMin = 0;
				SOUNDMANAGER->play("SwordAttackSound1", 0.5f);
				//SOUNDMANAGER->play("ZagSwordAttackSound1", 0.5f);
			}
				

			playerAttackSwordAnim.SeekTo(angle, 32, attackAnimMin);
			playerAttackSwordAnim.SetAnimPlaying();
			playerIdle.SeekTo(angle, 32);
		}

		if (KEYMANAGER->isOnceKeyDown('Q')) {
			printf("Special Attack");
			SOUNDMANAGER->play("SwordParry", 0.5f);
			playerSpacialAttackSwordAnim.SeekTo(angle / 2, 16);
			playerSpacialAttackSwordAnim.SetAnimPlaying();
			
		}

		if (swordAttackAnimCount == 3) {
			playerAttackSwordAnim.playOnce(angle, 32, 1600000, 3300000);
		}
		else if (swordAttackAnimCount == 2) {
			playerAttackSwordAnim.playOnce(angle, 32, 700000, 1500000);
		}
		else if (swordAttackAnimCount == 1) {
			playerAttackSwordAnim.playOnce(angle, 32, 0, 800000);
		}
	}
	else if (ePlayerWeapon == BOW) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			attackAngle = getAngle(playerIdle.transformation.position.x, playerIdle.transformation.position.y,
				(_ptMouse.x - WINSIZE_X / 2) + playerIdle.transformation.position.x,
				(_ptMouse.y - WINSIZE_Y / 2) + playerIdle.transformation.position.y);
			float tempAngle2 = (360 - (attackAngle * 180 / PI)) / 11.25f;
			angle = tempAngle2;

			playerAttackBowAnim.SeekTo(angle, 32, attackAnimMin);
			playerAttackBowAnim.SetAnimPlaying();
			playerIdle.SeekTo(angle, 32);
			swordAttackAnimCount == 0;
			SOUNDMANAGER->play("BowCharge", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {

			swordAttackAnimCount = 1;
			playerAttackBowAnim.SeekTo(angle, 32, 1800000);
			SOUNDMANAGER->play("BowFire", 0.3f);
			
		}

		if (KEYMANAGER->isOnceKeyDown('Q')) {
			printf("Special Attack");
			playerSpecialAttackBowAnim.SeekTo(angle / 2, 16);
			playerSpecialAttackBowAnim.SetAnimPlaying();
			SOUNDMANAGER->play("BowRapidFire", 0.5f);
		}

		if (swordAttackAnimCount == 0) {
			playerAttackBowAnim.chargeLoop(angle, 32, 500000, 1800000);
		}
		else if (swordAttackAnimCount == 1) {
			playerAttackBowAnim.playOnce(angle, 32, 1800000, 5000000);
		}
	}
	else if (ePlayerWeapon == FIST) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			attackAngle = getAngle(playerIdle.transformation.position.x, playerIdle.transformation.position.y,
				(_ptMouse.x - WINSIZE_X / 2) + playerIdle.transformation.position.x,
				(_ptMouse.y - WINSIZE_Y / 2) + playerIdle.transformation.position.y);
			float tempAngle2 = (360 - (attackAngle * 180 / PI)) / 11.25f;
			angle = tempAngle2;

			playerAttackFistAnim.SeekTo(angle, 32, attackAnimMin);
			playerAttackFistAnim.SetAnimPlaying();
			playerIdle.SeekTo(angle, 32);
			swordAttackAnimCount == 0;
		}

		playerAttackFistAnim.playOnce(angle, 32, 0, 2200000);

		if (KEYMANAGER->isOnceKeyDown('Q')) {
			printf("Special Attack");
			playerSpecialAttackFistAnim.SeekTo(angle / 2, 16);
			playerSpecialAttackFistAnim.SetAnimPlaying();
		}
	}
	else if (ePlayerWeapon == SPEAR) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			attackAngle = getAngle(playerIdle.transformation.position.x, playerIdle.transformation.position.y,
				(_ptMouse.x - WINSIZE_X / 2) + playerIdle.transformation.position.x,
				(_ptMouse.y - WINSIZE_Y / 2) + playerIdle.transformation.position.y);
			float tempAngle2 = (360 - (attackAngle * 180 / PI)) / 11.25f;
			angle = tempAngle2;


			if (swordAttackAnimCount == 3)
				swordAttackAnimCount = 1;
			else
				swordAttackAnimCount++;

			if (swordAttackAnimCount == 2) {
				attackAnimMin = 800000;
			}
			else if (swordAttackAnimCount == 3) {
				attackAnimMin = 1400000;
			}
			else
				attackAnimMin = 0;

			SOUNDMANAGER->play("SwordAttackSound1", 0.5f);
			playerAttackSpearAnim.SeekTo(angle * 2, 64, attackAnimMin);
			playerAttackSpearAnim.SetAnimPlaying();
			playerIdle.SeekTo(angle, 32);
		}

		if (swordAttackAnimCount == 3) {
			playerAttackSwordAnim.playOnce(angle * 2, 64, 1500000, 2200000);
		}
		else if (swordAttackAnimCount == 2) {
			playerAttackSwordAnim.playOnce(angle * 2, 64, 800000, 1500000);
		}
		else if (swordAttackAnimCount == 1) {
			playerAttackSwordAnim.playOnce(angle * 2, 64, 0, 800000);
		}
	}
	else if (ePlayerWeapon == GUN) {

	}
}

void Player::playerCommand()
{
	//Player Movemment
	if (ePlayerStatus == MOVE)
	{
		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A')) {
			//PlayerMove
			playerIdle.transformation.position.x -= 20;
			playerIdle.transformation.position.y += 20;

			//SetAngle
			angle = 12;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D')) {

			playerIdle.transformation.position += Vector2D(20, 20);

			angle = 4;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A')) {

			playerIdle.transformation.position -= Vector2D(20, 20);

			angle = 20;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D')) {

			playerIdle.transformation.position.x += 20;
			playerIdle.transformation.position.y -= 20;

			angle = 28;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('W')) {

			playerIdle.transformation.position.y += 20;

			angle = 8;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('A')) {

			playerIdle.transformation.position.x -= 20;

			angle = 16;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('S')) {

			playerIdle.transformation.position.y -= 20;

			angle = 24;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('D')) {

			playerIdle.transformation.position.x += 20;

			angle = 0;

			cout << "playerPosition: " << playerIdle.transformation.position.x << playerIdle.transformation.position.y << endl;
		}
		if (KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D')
			|| KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D')) {
			playerIdle.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
	}

	

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		playerDashAnim.SeekTo(angle / 2, 16);
		playerDashAnim.SetAnimPlaying();
		playerDashVFX.SeekTo(angle / 2, 16);
		playerDashVFX.SetAnimPlaying();
		float fAngle;
		if (angle != 0)
			fAngle = ((angle - 1) * 11.25) * PI / 180;
		else
			fAngle = (31 * 11.25) * PI / 180;

		dir = Vector2D(cos(fAngle), sin(fAngle));
		dashDistance = playerIdle.transformation.position + dir * 320;
		cout << dashDistance.x << ", " << dashDistance.y << endl;
		SOUNDMANAGER->play("dash", 0.5f);
	}
}

void Player::playerUpdate()
{
	animCount++;
	uint tempDepth = playerIdle.transformation.position.x + playerIdle.transformation.position.y;
	
	playerIdle.loop(angle, 32);
	playerRunAnim.loop(angle * 2, 64);
	playerDashAnim.playOnce(angle / 2, 16, 0, 1500000);
	playerDashVFX.playOnce(angle / 2, 16, 0, 1500000);
	
	if (ePlayerWeapon == SWORD) {
		playerSpacialAttackSwordAnim.playOnce(angle / 2, 16, 0, 2062500);
	}
	else if (ePlayerWeapon == BOW) {
		playerSpecialAttackBowAnim.playOnce(angle / 2, 16, 0, 2333333);
	}
	else if (ePlayerWeapon == FIST) {
		playerSpecialAttackFistAnim.playOnce(angle / 2, 16, 0, 2333333);
	}

	//playerAttackSpearAnim.loop(angle, 32, 0, 4400000);
	//playerAttackSpearAnim.loop(angle, 32, 0, 800000);
	//playerAttackSpearAnim.loop(angle, 32, 800000, 1500000);
	//playerAttackSpearAnim.loop(angle * 2, 64, 1500000, 2200000);
	PlayerAttack();
	playerCommand();
	tempPlayerStatueUpdate();
	playerMove();

	if (ePlayerStatus == IDLE) {
		if (animCount % 20 == 0) {
			animCount = 0;
			swordAttackAnimCount = 0;
		}
	}
	
	if (ePlayerStatus == MOVE) {
		if (!soundPlayOnce) {
			SOUNDMANAGER->play("footstep", 0.2f);
			soundPlayOnce = true;
		}
	}
	else {
		SOUNDMANAGER->pause("footstep");
		soundPlayOnce = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		ePlayerWeapon = SWORD;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) {
		ePlayerWeapon = BOW;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3)) {
		ePlayerWeapon = FIST;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) {
		ePlayerWeapon = SPEAR;
	}

}

void Player::Render()
{
	if (!enabled) return;

	gl.PushMatrix();

	playerIdle.RenderTest();
	playerRunAnim.RenderTest();
	playerDashAnim.RenderTest();
	playerDashVFX.RenderTest();
	playerAttackSwordAnim.RenderTest();
	playerSpacialAttackSwordAnim.RenderTest();
	playerAttackBowAnim.RenderTest();
	playerSpecialAttackBowAnim.RenderTest();
	playerAttackFistAnim.RenderTest();
	playerSpecialAttackFistAnim.Render();
	playerAttackSpearAnim.RenderTest();
	gl.DrawTextureAuto(transformation, texture, tick, Point2D(0,0));

	gl.PopMatrix();
}
