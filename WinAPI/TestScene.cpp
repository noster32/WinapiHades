#include "Stdafx.h"
#include "TestScene.h"

const int FADE_IN_FRAME = 30;
const int FADE_OUT_FRAME = 30;

const Point2D PLAYER_SIZE = Point2D(75, 84);

void TestScene::Init()
{
	const string TEXTURE_DIR = "./Resources/Images/Object";

	scene::AddSceneToMap(this, "game");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	nts.Add(gl.GenerateEmptyTexture(30, 30, 0xFFFFFFFF), "fade");
	nts.Add(gl.LoadTexture(TEXTURE_DIR + "Rocket.bmp", param), "shork");
	nts.Add(gl.LoadTexture(TEXTURE_DIR + "RBackground.bmp", param), "gg");

	RegisterObject(hidden);
	RegisterObject(fade);
	RegisterObject(bg);
	RegisterObject(player);

	hidden.SetDepth(50);

	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;

	bg.texture = nts.Find("gg");
	bg.SetDepth(60);

	player.texture = nts.Find("shork");
	player.SetDepth(30);
	player.renderOp = RenderObject::GIVEN_SIZE;
	player.renderSize = PLAYER_SIZE;
	player.transformation.position = Vector2D(300, 0);
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
	if (KEYMANAGER->isOnceKeyDown('H')) {
		fade.enabled = true;
		SceneEndOfUpdate();
		return;
	}

	if (gg) return;

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		player.transformation.position.x -= 13;
		player.transformation.scale.x = 1.0f;
		player.transformation.anchor = Anchor::LEFT_BOTTOM;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		player.transformation.position.x += 13;
		player.transformation.scale.x = -1.0f;
		player.transformation.anchor = Anchor::RIGHT_BOTTOM;
	}

	if (player.transformation.position.x < 0)
		player.transformation.position.x = 0;
	else if (player.transformation.position.x > WINSIZE_X)
		player.transformation.position.x = WINSIZE_X;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && (player.transformation.position.y < 1.0f))
		jump = 20;

	if (jump > 0 || player.transformation.position.y > 0.0f) {
		player.transformation.position.y += jump;
		jump--;
	}

	if (player.transformation.position.y < 0)
		player.transformation.position.y = 0;
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
