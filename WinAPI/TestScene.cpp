#include "Stdafx.h"
#include "TestScene.h"

const int FADE_IN_FRAME = 30;
const int FADE_OUT_FRAME = 30;

const Point2D PLAYER_SIZE = Point2D(416, 64);
const Point2D PLAYER2_SIZE = Point2D(128, 224);

void TestScene::Init()
{
	srand(time(NULL));

	scene::AddSceneToMap(this, "game");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	nts.Add(gl.GenerateEmptyTexture(30, 30, 0xFFFFFFFF), "fade");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/DeathArea_Tilesets53.png", param), "Sprite");
	nts.Add(gl.LoadTexturePng("Resources/Images/Map/TempMap.png", param), "TempMap");

	vector<uint> OrbUids = gl.LoadMultipleTexturesPng("Resources/Images/Object/Anim/Orb/Orb", ".png", 3, param);
	nts.Add(gl.BuildAnimation(OrbUids), "Orb");

	uint cutTexId = gl.CutTexture(nts.Find("Sprite"), Rect2D(Point2D(0, 940), Point2D(229, 1381)));
	nts.Add(cutTexId, "cut");
	vector<uint> uidsOrb = gl.LoadMultipleTexturesPng("Resources/Images/Object/Anim/Orb/Orb", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsOrb), "Orb");
	
	testFFmpeg.load_frame("Resources/Animation/ZagreusIdle_Bink.avi");
	playerRunAnim.load_frame("Resources/Animation/ZagreusRun_Bink.avi");
	playerAttackSwordAnim.load_frame("Resources/Animation/ZagreusSword_Bink.avi");


	Skelly.load_frame("Resources/Animation/SkellyAssistTrait_Bink.avi");
	

	RegisterObject(testFFmpeg);
	RegisterObject(playerRunAnim);
	RegisterObject(playerAttackSwordAnim);

	RegisterObject(Skelly);

	RegisterObject(Orb1);

	RegisterObject(fade);
	RegisterObject(testCut);
	RegisterObject(testSprite);
	RegisterObject(tempMap);
	RegisterObject(testOrb);
	
	//애니메이션 여러개 만들어서 활 당기는중일때는 "bow뭐시기" 하고 쏘면 -> "bow발사" 이런식으로 재생
	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;

	tempMap.texture = nts.Find("TempMap");
	tempMap.SetDepth(1);
	tempMap.transformation.scale -= 0.2f;

	testFFmpeg.transformation.position = Vector2D(1010, 300);
	testFFmpeg.transformation.anchor = Anchor::CENTER;
	testFFmpeg.transformation.scale -= 0.1f;
	testFFmpeg.SetDepth(20);
	playerRunAnim.transformation.position = testFFmpeg.transformation.position;
	playerRunAnim.transformation.anchor = Anchor::CENTER;
	playerRunAnim.transformation.scale -= 0.1f;
	playerRunAnim.SetDepth(20);
	playerAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 10);
	playerAttackSwordAnim.transformation.anchor = Anchor::CENTER;
	playerAttackSwordAnim.transformation.scale -= 0.1f;
	playerAttackSwordAnim.SetDepth(20);

	Skelly.transformation.position = Vector2D(1440, 520);
	Skelly.transformation.anchor = Anchor::CENTER;
	Skelly.transformation.scale -= 0.3f;
	Skelly.SetDepth(20);
	
	Orb1.texture = nts.Find("Orb");
	Orb1.transformation.position = Vector2D(2100, 900);
	Orb1.transformation.anchor = Anchor::CENTER;
	Orb1.SetDepth(10);

	masterSceneObject.transformation.anchor = Anchor::CENTER;
	

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

	tempX = 0;
	tempY = 0;
}

string TestScene::FindStatus(playerStatus ps)
{
	map<playerStatus, string>::iterator iter(mPlayerStatus.find(ps));
	return (iter != mPlayerStatus.end()) ? iter->second : 0;
}

void TestScene::tempPlayerStatueUpdate()
{
	if (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) || tempAnim.GetAnimDashPlaying())
		{
			ps = DASH;
		}
		else
			ps = MOVE;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_SPACE) || tempAnim.GetAnimDashPlaying())
	{
		ps = DASH;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		ps = ATTACK;
	}
	else
		ps = IDLE;
	

	switch (ps)
	{
	case IDLE:
		testFFmpeg.SetEnable(true);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		break;
	case MOVE:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(true);
		playerDashAnim.SetEnable(false);
		playerAttackSwordAnim.SetEnable(false);
		break;
	case DASH:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(true);
		playerAttackSwordAnim.SetEnable(false);
		break;
	case MOVESTOP:
		break;
	case ATTACK:
		testFFmpeg.SetEnable(false);
		playerRunAnim.SetEnable(false);
		playerDashAnim.SetEnable(false);
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
}

int TestScene::transformAngle(int angle, playerStatus ps)
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

void TestScene::setPlayerAngle(void)
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

	if (KEYMANAGER->isOnceKeyDown('A')) {
		if (KEYMANAGER->isOnceKeyDown('W')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else if (KEYMANAGER->isOnceKeyDown('S')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}

	}
	else if (KEYMANAGER->isOnceKeyDown('D')) {
		if (KEYMANAGER->isOnceKeyDown('W')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else if (KEYMANAGER->isOnceKeyDown('S')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('W')) {
		if (KEYMANAGER->isOnceKeyDown('A')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else if (KEYMANAGER->isOnceKeyDown('D')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('S')) {
		if (KEYMANAGER->isOnceKeyDown('A')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else if (KEYMANAGER->isOnceKeyDown('D')) {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
		else {
			testFFmpeg.SeekTo(angle, 32);
			playerRunAnim.SeekTo(angle * 2, 64);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << "Mouse : " << (_ptMouse.x - WINSIZE_X / 2) + testFFmpeg.transformation.position.x << ", " << (_ptMouse.y - WINSIZE_Y / 2) + testFFmpeg.transformation.position.y << endl;
		float tempAngle = getAngle(testFFmpeg.transformation.position.x, testFFmpeg.transformation.position.y, (_ptMouse.x - WINSIZE_X / 2) + testFFmpeg.transformation.position.x, (_ptMouse.y - WINSIZE_Y / 2) + testFFmpeg.transformation.position.y);
		float tempAngle2 = (360 - (tempAngle * 180 / PI)) / 11;
		cout << tempAngle2 << endl;
		angle = tempAngle2;
		playerAttackSwordAnim.SeekTo(angle, 32);
		testFFmpeg.SeekTo(angle, 32);
	}
}

void TestScene::playerMove(playerMoveDir pmr)
{
	if(ps == MOVE)
	{
		switch (pmr)
		{
		case RIGHT:
			testFFmpeg.transformation.position.x += 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case RIGHTUP:
			testFFmpeg.transformation.position += Vector2D(10, 10);
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case UP:
			testFFmpeg.transformation.position.y += 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case LEFTUP:
			testFFmpeg.transformation.position.x -= 10;
			testFFmpeg.transformation.position.y += 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case LEFT:
			testFFmpeg.transformation.position.x -= 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case LEFTDOWN:
			testFFmpeg.transformation.position.y -= 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case DOWN:
			testFFmpeg.transformation.position.y -= 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		case RIGHTDOWN:
			testFFmpeg.transformation.position.x += 10;
			testFFmpeg.transformation.position.y -= 10;
			cout << "position : " << testFFmpeg.transformation.position.x << ", " << testFFmpeg.transformation.position.y << endl;
			cout << "masterPosition : " << masterSceneObject.transformation.position.x << ", " << masterSceneObject.transformation.position.y << endl;
			cout << "angle : " << angle << endl;
			break;
		}
	}
	else if (ps == DASH)
	{
		float fAngle;
		if (angle != 0)
			fAngle = ((angle - 1) * 11.25) * PI / 180;
		else
			fAngle = (31 * 11.25) * PI / 180;

		Vector2D dir = Vector2D(cos(fAngle), sin(fAngle));

		//testAnim.transformation.position += dir * 30;
	}

	

	masterSceneObject.transformation.position = testFFmpeg.transformation.position * -1.0f * 1.9f;
	playerRunAnim.transformation.position = testFFmpeg.transformation.position;
	playerAttackSwordAnim.transformation.position = testFFmpeg.transformation.position + Vector2D(0, 10);
}

void TestScene::OnBegin()
{
}

void TestScene::OnEnd()
{
	//frame = 0;
	bg.enabled = false;
}

void TestScene::OnUpdate()
{
	setPlayerAngle();
	tempPlayerStatueUpdate();
	playerMove(pmr);

	testFFmpeg.loop(angle, 32);
	playerRunAnim.loop(angle * 2, 64);
	playerAttackSwordAnim.loop(angle, 32);
	Skelly.loop();


	if (ps == DASH)
	{
		//testAnimVfx.texture = nts.Find("DashVfx");
		//testAnimVfx.transformation.position = testAnim.transformation.position;
		//Dash 90' = 48  = 12장씩 /  4
		//Idle 90' = 240 = 24장씩 / 10
		//Move 90' = 104 = 6장씩 / 16
		//tempAnimVfx.playAnimVFX(testAnimVfx, transformAngle(angle, ps), animLength, animDelay, ps);
		//tempAnim.playAnim(testAnim, transformAngle(angle, ps), animLength, animDelay, false, ps);
	}
	else
		//tempAnim.playAnim(testAnim, transformAngle(angle, ps), animLength, animDelay, true, ps);

	OrbAnim.playObjAnim(Orb1, 39, 2);
	tempObjAnim.playObjAnim(testOrb, 39, 2);
}

void TestScene::OnUpdateLoading()
{
	if (frame >= FADE_IN_FRAME) {
		SceneEndOfLoading();
		frame = 0;
		fade.enabled = false;
	}
	else {
		frame++;
	}
}

void TestScene::OnUpdateClosing()
{
	if (frame >= FADE_OUT_FRAME) {
		frame = 0;
		fade.enabled = false;
		QueueSceneSwap("sample");
		SceneEndOfClosing();
	}
	else {
		frame++;
	}
}

void TestScene::OnRenderLoading()
{
	uchar c = (uchar)(frame * 0xFF / FADE_IN_FRAME);
	uint rgba = 0x00000000 | ((uchar)0xFF - c);
	gl.ClearTexture(nts.Find("fade"), rgba);
	masterSceneObject.Render();
	

}

void TestScene::OnRender()
{
	//gl.DrawQuadVideoTexture(128, 224, testFFmpeg);
}

void TestScene::OnRenderClosing()
{
	uchar c = (uchar)(frame * 0xFF / FADE_OUT_FRAME);
	uint rgba = 0x00000000 | c;
	gl.ClearTexture(nts.Find("fade"), rgba);
	masterSceneObject.Render();
}
