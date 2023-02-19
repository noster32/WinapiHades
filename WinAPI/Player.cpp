#include "Stdafx.h"
#include "Player.h"



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


	switch (ps)
	{
	case IDLE:
		testFFmpeg.SetEnable(true);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		break;
	case MOVE:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(true);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		break;
	case DASH:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(true);
		playerDashVFX.SetEnable(true);
		playerAttackSwordAnim.SetEnable(false);
		break;
	case MOVESTOP:
		break;
	case ATTACK:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerDashVFX.SetEnable(false);
		playerAttackSwordAnim.SetEnable(true);
		break;
	case SPECIAL_ATTACK:
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
	else
		cout << attackResetDelay << endl;
}

int Player::transformAngle(int angle, playerStatus ps)
{
	int transAngle = angle;

	switch (ps)
	{
	case IDLE:
		break;
	case MOVE:

		break;
	case DASH:

		break;
	case MOVESTOP:
		break;
	case ATTACK:
		break;
	case SPECIAL_ATTACK:
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

	transAngle = angle * animLength;
	return transAngle;
}

void Player::setPlayerAngle(void)
{
		if (KEYMANAGER->isStayKeyDown('A')) {
			if (KEYMANAGER->isStayKeyDown('W')) {
				pmr = LEFTUP;
				angle = 13;
			}
			else if (KEYMANAGER->isStayKeyDown('S')) {
				pmr = LEFTDOWN;
				angle = 21;
			}
			else {
				pmr = LEFT;
				angle = 17;
			}
		}
		else if (KEYMANAGER->isStayKeyDown('D')) {
			if (KEYMANAGER->isStayKeyDown('W')) {
				pmr = RIGHTUP;
				angle = 5;
			}
			else if (KEYMANAGER->isStayKeyDown('S')) {
				pmr = RIGHTDOWN;
				angle = 29;
			}
			else {
				pmr = RIGHT;
				angle = 0;
			}
		}
		else if (KEYMANAGER->isStayKeyDown('W')) {
			if (KEYMANAGER->isStayKeyDown('A')) {
				pmr = LEFTUP;
				angle = 13;
			}
			else if (KEYMANAGER->isStayKeyDown('D')) {
				pmr = RIGHTUP;
				angle = 5;
			}
			else {
				pmr = UP;
				angle = 9;
			}
		}
		else if (KEYMANAGER->isStayKeyDown('S')) {
			if (KEYMANAGER->isStayKeyDown('A')) {
				pmr = LEFTDOWN;
				angle = 21;
			}
			else if (KEYMANAGER->isStayKeyDown('D')) {
				pmr = RIGHTDOWN;
				angle = 29;
			}
			else {
				pmr = DOWN;
				angle = 25;
			}
		}


	//Set Player FFmpeg
	if (KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('D')) {
		testFFmpeg.SeekTo(angle, 32);
		playerRunAnim.SeekTo(angle * 2, 64);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !playerAttackSwordAnim.GetAnimPlaying() && attackResetDelay != 20) {
		cout << "Mouse : " << (_ptMouse.x - WINSIZE_X / 2) + testFFmpeg.transformation.position.x << ", " << (_ptMouse.y - WINSIZE_Y / 2) + testFFmpeg.transformation.position.y << endl;
		float tempAngle = getAngle(testFFmpeg.transformation.position.x, testFFmpeg.transformation.position.y, (_ptMouse.x - WINSIZE_X / 2) + testFFmpeg.transformation.position.x, (_ptMouse.y - WINSIZE_Y / 2) + testFFmpeg.transformation.position.y);
		float tempAngle2 = (360 - (tempAngle * 180 / PI)) / 11;
		cout << tempAngle2 << endl;
		angle = tempAngle2;

		SwordAttack1 = true;
		attackAnimMin = 0;

		if (attackResetDelay > 0 && SwordAttack2) {
			SwordAttack3 = true;
			attackAnimMin = 1400000;
			cout << "SwordAttack3" << endl;

		}
		else if (attackResetDelay > 0) {

			SwordAttack2 = true;
			attackAnimMin = 800000;
			cout << "SwordAttack2" << endl;
			attackResetDelay = 20;
		}
		else {
			cout << "SwordAttack1" << endl;
			attackResetDelay = 20;
		}


		playerAttackSwordAnim.SeekTo(angle, 32, attackAnimMin);
		playerAttackSwordAnim.SetAnimPlaying();
		testFFmpeg.SeekTo(angle, 32);

		//cout << test1.leftBottom.x << ", " << test1.leftBottom.y << ", " << test1.rightTop.x << ", " << test1.rightTop.y << endl;
		//cout << playerAttack.transformation.position.x - 91 << ", " << playerAttack.transformation.position.y - 100 << ", " << playerAttack.transformation.position.x + 91 << ", " << playerAttack.transformation.position.y + 100 << endl;
		//if (test1.IntersectRect2D(test2))
		//	printf("Hit!");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		playerDashAnim.SeekTo(angle / 2, 32);
		playerDashAnim.SetAnimPlaying();
		playerDashVFX.SeekTo(angle / 2, 32);
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
}

void Player::playerMove(playerMoveDir pmr)
{
	if (ps == MOVE)
	{
		switch (pmr)
		{
		case RIGHT:
			testFFmpeg.transformation.position.x += 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case RIGHTUP:
			testFFmpeg.transformation.position += Vector2D(20, 20);
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case UP:
			testFFmpeg.transformation.position.y += 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case LEFTUP:
			testFFmpeg.transformation.position.x -= 20;
			testFFmpeg.transformation.position.y += 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case LEFT:
			testFFmpeg.transformation.position.x -= 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case LEFTDOWN:
			testFFmpeg.transformation.position.y -= 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case DOWN:
			testFFmpeg.transformation.position.y -= 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case RIGHTDOWN:
			testFFmpeg.transformation.position.x += 20;
			testFFmpeg.transformation.position.y -= 20;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		}
	}

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



	//masterSceneObject.transformation.position = testFFmpeg.transformation.position * -1.0f;
	playerRunAnim.transformation.position = testFFmpeg.transformation.position;
	playerDashAnim.transformation.position = testFFmpeg.transformation.position;
	playerDashVFX.transformation.position = testFFmpeg.transformation.position;
	playerAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 30);
}

void Player::playerUpdate()
{
	uint tempDepth = testFFmpeg.transformation.position.x + testFFmpeg.transformation.position.y;
	testFFmpeg.SetDepth(tempDepth);
	playerRunAnim.SetDepth(tempDepth);

	//if (angle > 28 || angle <= 4) {
	//	playerAttack.enabled = true;
	//	playerAttack2.enabled = false;
	//	test1 = Rect2D(testFFmpeg.transformation.position.x + 100, testFFmpeg.transformation.position.y - 40, 182, 200, 0);
	//	playerAttack.transformation.position = Vector2D(test1.center.x, test1.center.y);
	//}
	//if (angle > 4 && angle <= 12)
	//{
	//	playerAttack.enabled = false;
	//	playerAttack2.enabled = true;
	//	test1 = Rect2D(testFFmpeg.transformation.position.x, testFFmpeg.transformation.position.y + 20, 200, 182, 0);
	//	playerAttack2.transformation.position = Vector2D(test1.center.x, test1.center.y);
	//}
	//if (angle > 12 && angle <= 20)
	//{
	//	playerAttack.enabled = true;
	//	playerAttack2.enabled = false;
	//	test1 = Rect2D(testFFmpeg.transformation.position.x - 100, testFFmpeg.transformation.position.y - 40, 182, 200, 0);
	//	playerAttack.transformation.position = Vector2D(test1.center.x, test1.center.y);
	//}
	//if (angle > 20 && angle <= 28)
	//{
	//	playerAttack.enabled = false;
	//	playerAttack2.enabled = true;
	//	test1 = Rect2D(testFFmpeg.transformation.position.x, testFFmpeg.transformation.position.y - 150, 200, 182, 0);
	//	playerAttack2.transformation.position = Vector2D(test1.center.x, test1.center.y);
	//}
	//



	//player
	//test1 = Rect2D(playerAttack.transformation.position.x - 91, playerAttack.transformation.position.y - 100, playerAttack.transformation.position.x + 91, playerAttack.transformation.position.y + 100);

	testFFmpeg.loop(angle, 32);
	playerRunAnim.loop(angle * 2, 64);
	playerDashAnim.playOnce(angle / 2, 16, 0, 1500000);
	playerDashVFX.playOnce(angle / 2, 16, 0, 1500000);



	if (SwordAttack3 && SwordAttack2 && SwordAttack1) {
		playerAttackSwordAnim.playOnce(angle, 32, 1600000, 3300000);
	}
	else if (SwordAttack2 && SwordAttack1) {
		playerAttackSwordAnim.playOnce(angle, 32, 700000, 1500000);
	}
	else if (SwordAttack1) {
		playerAttackSwordAnim.playOnce(angle, 32, 0, 800000);
	}




	if (attackResetDelay <= 0) {
		attackResetDelay = 0;
		SwordAttack1 = false;
		SwordAttack2 = false;
		SwordAttack3 = false;
	}

	setPlayerAngle();
	tempPlayerStatueUpdate();
	playerMove(pmr);
	//cout << ps << endl;
}

void Player::SetTexture()
{
	//TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	//this->texture = gl.LoadTexturePng("Resources/Images/Object/idle.png", param);
	//this->transformation.position = Vector2D(2000, 500);
}

void Player::SetFFmpeg()
{
	//testFFmpeg.load_frame("Resources/Animation/ZagreusIdle_Bink.avi");
	//playerRunAnim.load_frame("Resources/Animation/ZagreusRun_Bink.avi");
	//playerDashAnim.load_frame("Resources/Animation/ZagreusDash_Bink.avi");
	//playerDashVFX.load_frame("Resources/Animation/ZagreusDashVFX_Bink.avi");
	//playerAttackSwordAnim.load_frame("Resources/Animation/ZagreusSword_Bink.avi");
	testFFmpeg.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusIdle_Bink.avi");
	playerRunAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusRun_Bink.avi");
	playerDashAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDash_Bink.avi");
	playerDashVFX.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusDashVFX_Bink.avi");
	playerAttackSwordAnim.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/ZagreusSword_Bink.avi");

	testFFmpeg.transformation.position = Vector2D(2500, 800);
	testFFmpeg.transformation.anchor = Anchor::CENTER;
	testFFmpeg.transformation.scale -= 0.1f;
	testFFmpeg.SetDepth(20);
	playerRunAnim.transformation.position = testFFmpeg.transformation.position;
	playerRunAnim.transformation.anchor = Anchor::CENTER;
	playerRunAnim.transformation.scale -= 0.1f;
	playerRunAnim.SetDepth(20);
	playerDashAnim.transformation.position = testFFmpeg.transformation.position;
	playerDashAnim.transformation.anchor = Anchor::CENTER;
	playerDashAnim.transformation.scale -= 0.1f;
	playerDashAnim.SetDepth(20);
	playerDashVFX.transformation.position = testFFmpeg.transformation.position;
	playerDashVFX.transformation.anchor = Anchor::CENTER;
	playerDashVFX.transformation.scale -= 0.1f;
	playerDashVFX.SetDepth(20);
	playerAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 10);
	playerAttackSwordAnim.transformation.anchor = Anchor::CENTER;
	playerAttackSwordAnim.transformation.scale -= 0.1f;
	playerAttackSwordAnim.SetDepth(20);
	
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

void Player::Render()
{
	if (!enabled) return;

	gl.PushMatrix();

	Point2D arg;
	if (renderOp & RenderObject::FIT_TO_SCREEN_KEEP_RATIO) {
		const TextureSource& ref = gl.GetTextureInformation(texture);
		Point2D usedRange = Point2D(ref.range.rightTop) - ref.range.leftBottom;
		float aspect = (float)usedRange.x / usedRange.y;

		Point2D winsize = gl.GetWindowSize();
		Vector2D stretchRatio = Vector2D(winsize) / usedRange;

		if (stretchRatio.x < stretchRatio.y) {
			arg = Point2D(winsize.x, (int)(stretchRatio.x * usedRange.y));
		}
		else {
			arg = Point2D((int)(stretchRatio.y * usedRange.x), winsize.y);
		}
	}
	else {
		if (renderOp & RenderObject::TEXTURE_SIZE) {
			arg = Point2D();
		}
		else if (renderOp & RenderObject::GIVEN_SIZE) {
			arg = renderSize;
		}
	}

	if (renderOp & RenderObject::STRETCH_HOR)
		arg.x = gl.GetWindowSize().x;

	if (renderOp & RenderObject::STRETCH_VER)
		arg.y = gl.GetWindowSize().y;

	testFFmpeg.RenderTest();
	playerRunAnim.RenderTest();
	playerDashAnim.RenderTest();
	playerDashVFX.RenderTest();
	playerAttackSwordAnim.RenderTest();
	gl.DrawTextureAuto(transformation, texture, tick, arg);

	vector<SceneObject*>& children = GetChildrenVector();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->Render();
	}

	gl.PopMatrix();
}
