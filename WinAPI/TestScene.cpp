#include "Stdafx.h"
#include "TestScene.h"

const int FADE_IN_FRAME = 30;
const int FADE_OUT_FRAME = 30;

const Point2D PLAYER_SIZE = Point2D(416, 64);
const Point2D PLAYER2_SIZE = Point2D(128, 224);

void TestScene::Init()
{
	const string TEXTURE_DIR = "./WinAPI/Resources/Images/Object";

	srand(time(NULL));

	scene::AddSceneToMap(this, "game");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	nts.Add(gl.GenerateEmptyTexture(30, 30, 0xFFFFFFFF), "fade");
	nts.Add(gl.LoadTexture("Resources/Images/Object/Missile.bmp", param), "shork");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/idle.png", param), "test");
	nts.Add(gl.LoadTexture("Resources/Images/Object/RBackground.bmp", param), "gg");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/DeathArea_Tilesets53.png", param), "Sprite");

	RegisterObject(hidden);
	RegisterObject(fade);
	RegisterObject(bg);
	RegisterObject(player);
	RegisterObject(test);
	RegisterObject(testCut);
	RegisterObject(testSprite);
	RegisterObject(testAnim);

	vector<uint> uids = gl.LoadMultipleTexturesPng("Resources/Images/Anim/ZagreusIdle_Bink", ".png", 3, 10 ,param);
	nts.Add(gl.BuildAnimation(uids), "anim");

	uint cutTexId = gl.CutTexture(nts.Find("Sprite"), Rect2D(Point2D(0, 940), Point2D(229, 1381)));
	nts.Add(cutTexId, "cut");

	test.SetDepth(50);
	test.texture = nts.Find("test");
	test.renderOp = RenderObject::GIVEN_SIZE;
	test.transformation.position = Vector2D(WINSIZE_X /2 , WINSIZE_Y / 2);
	test.renderSize = PLAYER2_SIZE;
	hidden.SetDepth(50);
	test.transformation.anchor = Anchor::CENTER;
	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;

	bg.texture = nts.Find("gg");
	bg.SetDepth(60);

	testCut.texture = nts.Find("cut");
	testCut.SetDepth(10);

	testAnim.texture = nts.Find("anim");
	testAnim.SetDepth(2);

	//testSprite.texture = nts.Find("Sprite");
	//testSprite.renderOp = RenderObject::GIVEN_SIZE;
	//testSprite.renderSize = Point2D(850, 850);
	//testSprite.SetDepth(5);

}

void TestScene::OnBegin()
{
	frame = 0;
	tick = 90;
	increment = 1;
	jump = 0;
	gg = false;
	fade.enabled = true;
	bg.enabled = false;
	player.transformation.position = Vector2D(300, 0);
}

void TestScene::OnEnd()
{
	frame = 0;
	bg.enabled = false;
}

void TestScene::OnUpdate()
{
	TIMEMANAGER->update(60.0f);
	if (KEYMANAGER->isOnceKeyDown('H')) {
		fade.enabled = true;
		SceneEndOfUpdate();
		return;
	}
	
	
	test.transformation.anchor = Anchor::CENTER;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		masterSceneObject.transformation.position.x += 10;
		test.transformation.position.x -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		masterSceneObject.transformation.position.x-= 10;
		test.transformation.position.x += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		masterSceneObject.transformation.position.y -= 10;
		test.transformation.position.y += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		masterSceneObject.transformation.position.y += 10;
		test.transformation.position.y -= 10;
	}
	if (gg) return;
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
