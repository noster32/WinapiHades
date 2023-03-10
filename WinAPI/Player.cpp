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
	//playerIdle.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusIdle_Bink.avi");
	//playerRunAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusRun_Bink.avi");
	//playerDashAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDash_Bink.avi");
	//playerDashVFX.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDashVFX_Bink.avi");
	//playerAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSword_Bink.avi");
	//playerSpacialAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSwordParry_Bink.avi");

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
	ePlayerWeapon = BOW;
}



string Player::FindStatus(playerStatus ps)
{
	map<playerStatus, string>::iterator iter(mPlayerStatus.find(ps));
	return (iter != mPlayerStatus.end()) ? iter->second : 0;
}

void Player::tempPlayerStatueUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || playerAttackSwordAnim.GetAnimPlaying() || KEYMANAGER->isStayKeyDown(VK_LBUTTON))
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
	else
		ePlayerStatus = IDLE;

	if (KEYMANAGER->isOnceKeyDown('Q') || playerSpacialAttackSwordAnim.GetAnimPlaying()) {
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
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(true);
		break;
	case MOVE:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(true);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(false);
		break;
	case DASH:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(true);
		playerDashVFX.SetEnable(true);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		playerAttackBowAnim.SetEnable(false);
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
		}
		else if (ePlayerWeapon == BOW) {
			playerAttackSwordAnim.SetEnable(false);
			playerAttackBowAnim.SetEnable(true);
		}
		playerSpacialAttackSwordAnim.SetEnable(false);
		break;
	case SPECIAL_ATTACK:
		playerIdle.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(true);
		playerAttackBowAnim.SetEnable(false);
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

	if (ePlayerStatus != ATTACK)
		attackResetDelay--;

	if (attackResetDelay <= 0) {
		attackResetDelay = 0;
		SwordAttack1 = false;
		SwordAttack2 = false;
		SwordAttack3 = false;
	}
		//cout << attackResetDelay << endl;
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
}

void Player::PlayerAttack()
{
	if(ePlayerWeapon == SWORD) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !playerAttackSwordAnim.GetAnimPlaying()) {
			float tempAngle = getAngle(playerIdle.transformation.position.x, playerIdle.transformation.position.y,
				(_ptMouse.x - WINSIZE_X / 2) + playerIdle.transformation.position.x,
				(_ptMouse.y - WINSIZE_Y / 2) + playerIdle.transformation.position.y);
			float tempAngle2 = (360 - (tempAngle * 180 / PI)) / 11.25f;
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

			playerAttackSwordAnim.SeekTo(angle, 32, attackAnimMin);
			playerAttackSwordAnim.SetAnimPlaying();
			playerIdle.SeekTo(angle, 32);
		}

		if (KEYMANAGER->isOnceKeyDown('Q')) {
			printf("Special Attack");
			playerSpacialAttackSwordAnim.SeekTo(angle / 2, 16, attackAnimMin);
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
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
			float tempAngle = getAngle(playerIdle.transformation.position.x, playerIdle.transformation.position.y,
				(_ptMouse.x - WINSIZE_X / 2) + playerIdle.transformation.position.x,
				(_ptMouse.y - WINSIZE_Y / 2) + playerIdle.transformation.position.y);
			float tempAngle2 = (360 - (tempAngle * 180 / PI)) / 11.25f;
			angle = tempAngle2;

			playerAttackBowAnim.SeekTo(angle, 32, attackAnimMin);
			playerAttackBowAnim.SetAnimPlaying();
			playerIdle.SeekTo(angle, 32);

			
		}
	}
	else if (ePlayerWeapon == FIST) {

	}
	else if (ePlayerWeapon == SPEAR) {

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
	}
}

void Player::playerUpdate()
{
	uint tempDepth = playerIdle.transformation.position.x + playerIdle.transformation.position.y;
	
	playerIdle.loop(angle, 32);
	playerRunAnim.loop(angle * 2, 64);
	playerDashAnim.playOnce(angle / 2, 16, 0, 1500000);
	playerDashVFX.playOnce(angle / 2, 16, 0, 1500000);
	playerSpacialAttackSwordAnim.playOnce(angle / 2, 16, 0, 2062500);
	//playerAttackBowAnim.loop(angle, 32, 0, 500000);
	//playerAttackBowAnim.loop(angle, 32, 500000, 1800000);
	//playerAttackBowAnim.loop(angle, 32, 1800000, 5000000);
	PlayerAttack();
	playerCommand();
	tempPlayerStatueUpdate();
	playerMove();

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
	gl.DrawTextureAuto(transformation, texture, tick, Point2D(0,0));

	gl.PopMatrix();
}
