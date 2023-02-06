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
	
	
	vector<uint> uids = gl.LoadMultipleTexturesPng("Resources/Images/Anim/Idle/ZagreusIdle_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uids), "IDLE");
	vector<uint> uidsMove = gl.LoadMultipleTexturesPng("Resources/Images/Anim/IdleMove/ZagreusRun_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsMove), "MOVE");
	vector<uint> uidsDash = gl.LoadMultipleTexturesPng("Resources/Images/Anim/Dash/ZagreusDash_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsDash), "DASH");
	vector<uint> uidsDashVfx = gl.LoadMultipleTexturesPng("Resources/Images/Anim/DashVfx/ZagreusDashVFX_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsDashVfx), "DashVfx");
	vector<uint> uidsSwordAttack = gl.LoadMultipleTexturesPng("Resources/Images/Anim/SwordAttack/ZagreusSword_Bink", ".png", 4, param);
	nts.Add(gl.BuildAnimation(uidsSwordAttack), "SWORDATTACK");
	uint cutTexId = gl.CutTexture(nts.Find("Sprite"), Rect2D(Point2D(0, 940), Point2D(229, 1381)));
	nts.Add(cutTexId, "cut");

	RegisterObject(fade);
	RegisterObject(testCut);
	RegisterObject(testSprite);
	RegisterObject(testAnim);
	RegisterObject(testAnimVfx);
	RegisterObject(tempMap);
	//애니메이션 여러개 만들어서 활 당기는중일때는 "bow뭐시기" 하고 쏘면 -> "bow발사" 이런식으로 재생

	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;

	tempMap.texture = nts.Find("TempMap");
	tempMap.SetDepth(1);

	testCut.texture = nts.Find("cut");
	testCut.SetDepth(10);
	
	testAnim.SetDepth(15);
	testAnimVfx.SetDepth(16);
	testAnim.transformation.position = Vector2D(WINSIZE_X / 2, WINSIZE_Y / 2);
	//masterSceneObject.transformation.position = Vector2D(2590, 4250);
	testAnim.transformation.anchor = Anchor::CENTER;
	testAnim.transformation.scale += 0.1f;
	testAnimVfx.transformation.anchor = Anchor::CENTER;

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
	
	else
		ps = IDLE;
		
	switch (ps)
	{
	case IDLE:
		animLength = 24;
		animDelay = 3;
		break;
	case MOVE:
		animLength = 11;
		animDelay = 3;
		break;
	case DASH:
		animLength = 12;
		animDelay = 1;
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
}

int TestScene::transformAngle(int angle, playerStatus ps)
{
	int transAngle = angle;
	
	switch (ps)
	{
	case IDLE:
		break;
	case MOVE:
		if (angle == 1)
			angle = 0;
		else if (angle == 5)
			angle = 1;
		else if (angle == 9)
			angle = 2;
		else if (angle == 13)
			angle = 3;
		else if (angle == 17)
			angle = 4;
		else if (angle == 21)
			angle = 5;
		else if (angle == 25)
			angle = 6;
		else if (angle == 29)
			angle = 7;
		break;
	case DASH:
		if (angle == 1)
			angle = 0;
		else if (angle > 1 && angle < 5)
			angle = 1;
		else if (angle == 5)
			angle = 2;
		else if (angle > 5 && angle < 9)
			angle = 3;
		else if (angle == 9)
			angle = 4;
		else if (angle > 9 && angle < 13)
			angle = 5;
		else if (angle == 13)
			angle = 6;
		else if (angle > 13 && angle < 17)
			angle = 7;
		else if (angle == 17)
			angle = 8;
		else if (angle > 17 && angle < 21)
			angle = 9;
		else if (angle == 21)
			angle = 10;
		else if (angle > 21 && angle < 25)
			angle = 11;
		else if (angle == 25)
			angle = 12;
		else if (angle > 25 && angle < 29)
			angle = 13;
		else if (angle == 29)
			angle = 14;
		else if ((angle > 29 && angle < 32) || angle == 0)
			angle = 15;
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
			angle = 1;
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
}

void TestScene::playerMove(playerMoveDir pmr)
{
	if(ps = MOVE)
	{
		switch (pmr)
		{
		case RIGHT:
			masterSceneObject.transformation.position.x -= 10;
			testAnim.transformation.position.x += 10;
			break;
		case RIGHTUP:
			masterSceneObject.transformation.position -= Vector2D(10, 10);
			testAnim.transformation.position += Vector2D(10, 10);
			break;
		case UP:
			masterSceneObject.transformation.position.y -= 10;
			testAnim.transformation.position.y += 10;
			break;
		case LEFTUP:
			masterSceneObject.transformation.position.x += 10;
			testAnim.transformation.position.x -= 10;
			masterSceneObject.transformation.position.y -= 10;
			testAnim.transformation.position.y += 10;
			break;
		case LEFT:
			masterSceneObject.transformation.position.x += 10;
			testAnim.transformation.position.x -= 10;
			break;
		case LEFTDOWN:
			masterSceneObject.transformation.position.y += 10;
			testAnim.transformation.position.y -= 10;
			break;
		case DOWN:
			masterSceneObject.transformation.position.y += 10;
			testAnim.transformation.position.y -= 10;
			break;
		case RIGHTDOWN:
			masterSceneObject.transformation.position.x -= 10;
			testAnim.transformation.position.x += 10;
			masterSceneObject.transformation.position.y += 10;
			testAnim.transformation.position.y -= 10;
			break;
		}
	}
	else if (ps == DASH)
	{
		switch (pmr)
		{
		case RIGHT:
			masterSceneObject.transformation.position.x -= 30;
			testAnim.transformation.position.x += 30;
			break;
		case RIGHTUP:
			masterSceneObject.transformation.position -= Vector2D(30, 30);
			testAnim.transformation.position += Vector2D(30, 30);
			break;
		case UP:
			masterSceneObject.transformation.position.y -= 30;
			testAnim.transformation.position.y += 30;
			break;
		case LEFTUP:
			masterSceneObject.transformation.position.x += 30;
			testAnim.transformation.position.x -= 30;
			masterSceneObject.transformation.position.y -= 30;
			testAnim.transformation.position.y += 30;
			break;
		case LEFT:
			masterSceneObject.transformation.position.x += 30;
			testAnim.transformation.position.x -= 30;
			break;
		case LEFTDOWN:
			masterSceneObject.transformation.position.y += 30;
			testAnim.transformation.position.y -= 30;
			break;
		case DOWN:
			masterSceneObject.transformation.position.y += 30;
			testAnim.transformation.position.y -= 30;
			break;
		case RIGHTDOWN:
			masterSceneObject.transformation.position.x -= 30;
			testAnim.transformation.position.x += 30;
			masterSceneObject.transformation.position.y += 30;
			testAnim.transformation.position.y -= 30;
			break;
		}
	}
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
	testAnim.texture = nts.Find(FindStatus(ps));
	
	//if (KEYMANAGER->isOnceKeyDown('H')) {
	//	fade.enabled = true;
	//	SceneEndOfUpdate();
	//	return;
	//}
	


	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		testAnim.enabled = false;		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		testAnim.enabled = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//float tempAngle = getAngle(testAnim.transformation.position.x, testAnim.transformation.position.y, _ptMouse.x - masterSceneObject.transformation.position.x, _ptMouse.y - masterSceneObject.transformation.position.y);
		//angle = (360 - (tempAngle * 180 / PI)) / 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {

		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
	}


	setPlayerAngle();
	tempPlayerStatueUpdate();
	playerMove(pmr);


	if (ps == DASH)
	{
		testAnimVfx.texture = nts.Find("DashVfx");
		testAnimVfx.transformation.position = testAnim.transformation.position;
		//Dash 90' = 48  = 12장씩 /  4
		//Idle 90' = 240 = 24장씩 / 10
		//Move 90' = 104 = 6장씩 / 16
		tempAnimVfx.playAnimVFX(testAnimVfx, transformAngle(angle, ps), animLength, animDelay, ps);
		tempAnim.playAnim(testAnim, transformAngle(angle, ps), animLength, animDelay, false, ps);
	}
	else
		tempAnim.playAnim(testAnim, transformAngle(angle, ps), animLength, animDelay, true, ps);
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

}

void TestScene::OnRenderClosing()
{
	uchar c = (uchar)(frame * 0xFF / FADE_OUT_FRAME);
	uint rgba = 0x00000000 | c;
	gl.ClearTexture(nts.Find("fade"), rgba);
	masterSceneObject.Render();
}
