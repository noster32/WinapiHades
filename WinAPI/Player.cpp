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
	testFFmpeg.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusIdle_Bink.avi");
	playerRunAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusRun_Bink.avi");
	playerDashAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusDash_Bink.avi");
	playerDashVFX.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusDashVFX_Bink.avi");
	playerAttackSwordAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusSword_Bink.avi");
	playerSpacialAttackSwordAnim.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/ZagreusSwordParry_Bink.avi");
	//testFFmpeg.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusIdle_Bink.avi");
	//playerRunAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusRun_Bink.avi");
	//playerDashAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDash_Bink.avi");
	//playerDashVFX.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDashVFX_Bink.avi");
	//playerAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSword_Bink.avi");
	//playerSpacialAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSwordParry_Bink.avi");

	testFFmpeg.transformation.position = Vector2D(2500, 800);
	testFFmpeg.transformation.anchor = Anchor::CENTER;
	testFFmpeg.transformation.scale -= 0.1f;
	//testFFmpeg.SetDepth(20);
	playerRunAnim.transformation.position = testFFmpeg.transformation.position;
	playerRunAnim.transformation.anchor = Anchor::CENTER;
	playerRunAnim.transformation.scale -= 0.1f;
	//playerRunAnim.SetDepth(20);
	playerDashAnim.transformation.position = testFFmpeg.transformation.position;
	playerDashAnim.transformation.anchor = Anchor::CENTER;
	playerDashAnim.transformation.scale -= 0.1f;
	//playerDashAnim.SetDepth(20);
	playerDashVFX.transformation.position = testFFmpeg.transformation.position;
	playerDashVFX.transformation.anchor = Anchor::CENTER;
	playerDashVFX.transformation.scale -= 0.1f;
	//playerDashVFX.SetDepth(20);
	playerAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 10);
	playerAttackSwordAnim.transformation.anchor = Anchor::CENTER;
	playerAttackSwordAnim.transformation.scale -= 0.1f;
	//playerAttackSwordAnim.SetDepth(20);
	playerSpacialAttackSwordAnim.transformation.position = testFFmpeg.transformation.position;
	playerSpacialAttackSwordAnim.transformation.anchor = Anchor::CENTER;
	playerSpacialAttackSwordAnim.transformation.scale -= 0.1f;
	//playerSpacialAttackSwordAnim.SetDepth(20);



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

	ps = IDLE;
	SwordAttack1 = false;
	SwordAttack2 = false;
	SwordAttack3 = false;
}



string Player::FindStatus(playerStatus ps)
{
	map<playerStatus, string>::iterator iter(mPlayerStatus.find(ps));
	return (iter != mPlayerStatus.end()) ? iter->second : 0;
}

void Player::tempPlayerStatueUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || playerAttackSwordAnim.GetAnimPlaying())
	{
		ps = ATTACK;
	}
	else if (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || playerDashAnim.GetAnimPlaying())
		{
			ps = DASH;
		}
		else
			ps = MOVE;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || playerDashAnim.GetAnimPlaying())
	{
		ps = DASH;
	}
	else
		ps = IDLE;

	if (KEYMANAGER->isOnceKeyDown('Q') || playerSpacialAttackSwordAnim.GetAnimPlaying()) {
		ps = SPECIAL_ATTACK;
	}

	switch (ps)
	{
	case IDLE:
		testFFmpeg.SetEnable(true);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		break;
	case MOVE:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(true);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		break;
	case DASH:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(true);
		playerDashVFX.SetEnable(true);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(false);
		break;
	case MOVESTOP:
		break;
	case ATTACK:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(true);
		playerSpacialAttackSwordAnim.SetEnable(false);
		break;
	case SPECIAL_ATTACK:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		playerSpacialAttackSwordAnim.SetEnable(true);
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

	if (ps != ATTACK)
		attackResetDelay--;

	if (attackResetDelay <= 0) {
		attackResetDelay = 0;
		SwordAttack1 = false;
		SwordAttack2 = false;
		SwordAttack3 = false;
	}
		//cout << attackResetDelay << endl;
}

void Player::playerMove(playerMoveDir pmr)
{
	if (ps == DASH)
	{
		Point2D tempA = Point2D(testFFmpeg.transformation.position.x, testFFmpeg.transformation.position.y);
		Point2D tempB = Point2D(dashDistance.x, dashDistance.y);

		if (tempA != tempB)
		{
			testFFmpeg.transformation.position += dir * 80;
			cout << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
		}
	}
	
	playerRunAnim.transformation.position = testFFmpeg.transformation.position;
	playerDashAnim.transformation.position = testFFmpeg.transformation.position;
	playerDashVFX.transformation.position = testFFmpeg.transformation.position;
	playerAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 30);
	playerSpacialAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 30);
}

void Player::playerCommand()
{
	//Player Movemment
	if (ps == MOVE)
	{
		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A')) {
			//PlayerMove
			testFFmpeg.transformation.position.x -= 20;
			testFFmpeg.transformation.position.y += 20;

			//SetAngle
			angle = 12;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D')) {

			testFFmpeg.transformation.position += Vector2D(20, 20);

			angle = 4;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A')) {

			testFFmpeg.transformation.position -= Vector2D(20, 20);

			angle = 20;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D')) {

			testFFmpeg.transformation.position.x += 20;
			testFFmpeg.transformation.position.y -= 20;

			angle = 28;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('W')) {

			testFFmpeg.transformation.position.y += 20;

			angle = 8;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('A')) {

			testFFmpeg.transformation.position.x -= 20;

			angle = 16;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('S')) {

			testFFmpeg.transformation.position.y -= 20;

			angle = 24;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		else if (KEYMANAGER->isStayKeyDown('D')) {

			testFFmpeg.transformation.position.x += 20;

			angle = 0;

			cout << "playerPosition: " << testFFmpeg.transformation.position.x << testFFmpeg.transformation.position.y << endl;
		}
		if (KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D')
			|| KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D')) {
			testFFmpeg.SeekTo(angle, 32);
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
		dashDistance = testFFmpeg.transformation.position + dir * 320;
		cout << dashDistance.x << ", " << dashDistance.y << endl;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !playerAttackSwordAnim.GetAnimPlaying()) {
		float tempAngle = getAngle(testFFmpeg.transformation.position.x, testFFmpeg.transformation.position.y, 
							(_ptMouse.x - WINSIZE_X / 2) + testFFmpeg.transformation.position.x, 
							(_ptMouse.y - WINSIZE_Y / 2) + testFFmpeg.transformation.position.y);
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
		testFFmpeg.SeekTo(angle, 32);
	}
	
	if (KEYMANAGER->isOnceKeyDown('Q')) {
		printf("Special Attack");
		playerSpacialAttackSwordAnim.SeekTo(angle / 2, 16, attackAnimMin);
		playerSpacialAttackSwordAnim.SetAnimPlaying();
	}
}

void Player::playerUpdate()
{
	uint tempDepth = testFFmpeg.transformation.position.x + testFFmpeg.transformation.position.y;
	
	testFFmpeg.loop(angle, 32);
	playerRunAnim.loop(angle * 2, 64);
	playerDashAnim.playOnce(angle / 2, 16, 0, 1500000);
	playerDashVFX.playOnce(angle / 2, 16, 0, 1500000);
	playerSpacialAttackSwordAnim.playOnce(angle / 2, 16, 0, 2062500);

	if (swordAttackAnimCount == 3) {
		playerAttackSwordAnim.playOnce(angle, 32, 1600000, 3300000);
	}
	else if (swordAttackAnimCount == 2) {
		playerAttackSwordAnim.playOnce(angle, 32, 700000, 1500000);
	}
	else if (swordAttackAnimCount == 1) {
		playerAttackSwordAnim.playOnce(angle, 32, 0, 800000);
	}

	playerCommand();
	tempPlayerStatueUpdate();
	playerMove(pmr);

}

void Player::Render()
{
	if (!enabled) return;

	gl.PushMatrix();

	testFFmpeg.RenderTest();
	playerRunAnim.RenderTest();
	playerDashAnim.RenderTest();
	playerDashVFX.RenderTest();
	playerAttackSwordAnim.RenderTest();
	playerSpacialAttackSwordAnim.RenderTest();
	gl.DrawTextureAuto(transformation, texture, tick, Point2D(0,0));

	gl.PopMatrix();
}
