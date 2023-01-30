#include "Stdafx.h"
#include "TestScene.h"

const Point2D PLAYER_SIZE = Point2D(75, 84);

void TestScene::Init()
{
	const string TEXTURE_DIR = "./Resource/Texture/";

	scene::AddSceneToMap(this, "game");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	nts.Add(gl.GenerateEmptyTexture(30, 30, 0xFFFFFFFF), "fade");
	nts.Add(gl.LoadTexture(TEXTURE_DIR + "shork.bmp", param), "shork");
	nts.Add(gl.LoadTexture(TEXTURE_DIR + "gameover.bmp", param), "gg");

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

	if(KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		player.transformation.position.x -= 13;
		player.transformation.scale.x = 1.0f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
	}
}

void TestScene::OnUpdateLoading()
{
}

void TestScene::OnUpdateClosing()
{
}

void TestScene::OnRenderLoading()
{
}

void TestScene::OnRender()
{
}

void TestScene::OnRenderClosing()
{
}
