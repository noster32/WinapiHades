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
	
	vector<uint> uids = gl.LoadMultipleTexturesPng("Resources/Images/Anim/Idle/ZagreusIdle_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uids), "IDLE");
	vector<uint> uidsMove = gl.LoadMultipleTexturesPng("Resources/Images/Anim/IdleMove/ZagreusRun_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsMove), "MOVE");
	vector<uint> uidsDash = gl.LoadMultipleTexturesPng("Resources/Images/Anim/Dash/ZagreusDash_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsDash), "DASH");
	vector<uint> uidsDashVfx = gl.LoadMultipleTexturesPng("Resources/Images/Anim/DashVfx/ZagreusDashVFX_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsDashVfx), "DashVfx");
	uint cutTexId = gl.CutTexture(nts.Find("Sprite"), Rect2D(Point2D(0, 940), Point2D(229, 1381)));
	nts.Add(cutTexId, "cut");

	RegisterObject(fade);
	RegisterObject(testCut);
	RegisterObject(testSprite);
	RegisterObject(testAnim);
	RegisterObject(testAnimVfx);
	//애니메이션 여러개 만들어서 활 당기는중일때는 "bow뭐시기" 하고 쏘면 -> "bow발사" 이런식으로 재생

	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;


	testCut.texture = nts.Find("cut");
	testCut.SetDepth(10);

	
	testAnim.SetDepth(15);
	testAnimVfx.SetDepth(16);
	testAnim.transformation.position = Vector2D(WINSIZE_X / 2, WINSIZE_Y / 2);
	testAnim.transformation.anchor = Anchor::CENTER;
	testAnimVfx.transformation.anchor = Anchor::CENTER;
	mPlayerStatus.insert(make_pair(IDLE, "IDLE"));
	mPlayerStatus.insert(make_pair(MOVE, "MOVE"));
	mPlayerStatus.insert(make_pair(DASH, "DASH"));
	mPlayerStatus.insert(make_pair(STOP, "STOP"));
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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		ps = MOVE;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_SPACE))
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
		animDelay = 5;
		break;
	case DASH:
		animLength = 11;
		animDelay = 3;
		break;
	case STOP:
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
	

	if (KEYMANAGER->isOnceKeyDown('H')) {
		fade.enabled = true;
		SceneEndOfUpdate();
		return;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//float tempAngle = getAngle(testAnim.transformation.position.x, testAnim.transformation.position.y, _ptMouse.x - masterSceneObject.transformation.position.x, _ptMouse.y - masterSceneObject.transformation.position.y);
		//angle = (360 - (tempAngle * 180 / PI)) / 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		masterSceneObject.transformation.position.x += 10;
		testAnim.transformation.position.x -= 10;
		if (KEYMANAGER->isStayKeyDown(VK_UP))
			angle = 14;
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			angle = 22;
		else
			angle = 18;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		masterSceneObject.transformation.position.x-= 10;
		testAnim.transformation.position.x += 10;
		if (KEYMANAGER->isStayKeyDown(VK_UP))
			angle = 4;
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			angle = 32;
		else
			angle = 0;
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		masterSceneObject.transformation.position.y -= 10;
		testAnim.transformation.position.y += 10;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			angle = 13;
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			angle = 5;
		else
			angle = 9;
		
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {

		masterSceneObject.transformation.position.y += 10;
		testAnim.transformation.position.y -= 10;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			angle = 23;
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			angle = 31;
		else
			angle = 27;
	}
	
	
	tempPlayerStatueUpdate();
	if (ps == DASH)
	{

		testAnimVfx.texture = nts.Find("DashVfx");
		testAnimVfx.transformation.position = testAnim.transformation.position;
		tempAnimVfx.playAnim(testAnimVfx, angle * animLength, animLength, animDelay, false);
		tempAnim.playAnim(testAnim, angle * animLength, animLength, animDelay, false);
	}
	else
		tempAnim.playAnim(testAnim, angle * animLength, animLength, animDelay, true);
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
