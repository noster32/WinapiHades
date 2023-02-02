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
	nts.Add(gl.BuildAnimation(uids), "anim");
	vector<uint> uidsMove = gl.LoadMultipleTexturesPng("Resources/Images/Anim/IdleMove/ZagreusRun_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsMove), "animMove");
	uint cutTexId = gl.CutTexture(nts.Find("Sprite"), Rect2D(Point2D(0, 940), Point2D(229, 1381)));
	nts.Add(cutTexId, "cut");

	RegisterObject(fade);
	RegisterObject(testCut);
	RegisterObject(testSprite);
	RegisterObject(testAnim);
	//애니메이션 여러개 만들어서 활 당기는중일때는 "bow뭐시기" 하고 쏘면 -> "bow발사" 이런식으로 재생

	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;


	testCut.texture = nts.Find("cut");
	testCut.SetDepth(10);

	testAnim.texture = nts.Find("anim");
	testAnim.SetDepth(2);
	testAnim.transformation.position = Vector2D(WINSIZE_X / 2, WINSIZE_Y / 2);
	testAnim.transformation.anchor = Anchor::CENTER;
	
	
}

void TestScene::OnBegin()
{
	animSelected = &testAnim;
	frame = 0;
	increment = 1;
	gg = false;
	fade.enabled = true;
	bg.enabled = false;
	player.transformation.position = Vector2D(300, 0);
}

void TestScene::OnEnd()
{
	//frame = 0;
	bg.enabled = false;
}

void TestScene::OnUpdate()
{
	

	if (KEYMANAGER->isOnceKeyDown('H')) {
		fade.enabled = true;
		SceneEndOfUpdate();
		return;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		float tempAngle = getAngle(testAnim.transformation.position.x, testAnim.transformation.position.y, _ptMouse.x, _ptMouse.y);
		angle = (360 - (tempAngle * 180 / PI)) / 11;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		masterSceneObject.transformation.position.x += 10;
		testAnim.transformation.position.x -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		masterSceneObject.transformation.position.x-= 10;
		testAnim.transformation.position.x += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		masterSceneObject.transformation.position.y -= 10;
		testAnim.transformation.position.y += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		masterSceneObject.transformation.position.y += 10;
		testAnim.transformation.position.y -= 10;
	}

	tempAnim.playAnim(testAnim, angle * 24, 22, 3, true);

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
