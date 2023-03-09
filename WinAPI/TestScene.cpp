#include "Stdafx.h"
#include "TestScene.h"

const int FADE_IN_FRAME = 30;
const int FADE_OUT_FRAME = 30;

const Point2D PLAYER_SIZE = Point2D(416, 64);
const Point2D PLAYER2_SIZE = Point2D(128, 224);

void TestScene::MonSpawn()
{		
}

void TestScene::Init()
{
	srand(time(NULL));

	scene::AddSceneToMap(this, "game");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	nts.Add(gl.GenerateEmptyTexture(30, 30, 0xFFFFFFFF), "fade");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/DeathArea_Tilesets53.png", param), "Sprite");
	nts.Add(gl.LoadTexturePng("Resources/Images/Map/TempMap.png", param), "TempMap");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/idle.png", param), "temp");

	SOUNDMANAGER->addSound("DeathRoom", "Resources/Sounds/DeathRoom.wav", false, true);
	SOUNDMANAGER->addSound("DeathRoom1", "Resources/Sounds/DeathRoom1.wav", false, true);
	SOUNDMANAGER->addSound("DeathRoom2", "Resources/Sounds/DeathRoom2.wav", false, true);

	vector<uint> OrbUids = gl.LoadMultipleTexturesPng("Resources/Images/Object/Anim/Orb/Orb", ".png", 3, param);
	nts.Add(gl.BuildAnimation(OrbUids), "Orb");

	uint cutTexId = gl.CutTexture(nts.Find("Sprite"), Rect2D(Point2D(0, 940), Point2D(229, 1381)));
	nts.Add(cutTexId, "cut");
	vector<uint> uidsOrb = gl.LoadMultipleTexturesPng("Resources/Images/Object/Anim/Orb/Orb", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsOrb), "Orb");

	vector<uint> uidsMobSpawn = gl.LoadMultipleTexturesPng("Resources/Images/Object/Anim/MobSpawn/MobSpawn", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsMobSpawn), "MobSpawn");

	//Skelly.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/SkellyAssistTrait_Bink.avi");
	Skelly.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/SkellyAssistTrait_Bink.avi");
	
	nts.Add(gl.GenerateEmptyTexture(150, 150, 0xFFFFFFFF), "EnemyHitbox");
	nts.Add(gl.GenerateEmptyTexture(182, 200, 0xFFFFFFFF), "PlayerAttack");
	nts.Add(gl.GenerateEmptyTexture(250, 100, 0xFFFFFFFF), "PlayerAttackUpDown");
	
	playerObjTest.SetTexture();
	playerObjTest.SetFFmpeg(); 
	playerObjTest.SetDepth(20);
	RegisterObject(playerObjTest);

	//RegisterObject(Skelly);

	RegisterObject(Orb1);
	RegisterObject(MobSpawn);

	RegisterObject(fade);
	RegisterObject(testCut);
	RegisterObject(testSprite);
	RegisterObject(tempMap);
	
	RegisterObject(enemyHitbox);
	RegisterObject(playerAttack);
	RegisterObject(playerAttack2);

	RegisterObject(UpdateInPlayer);
	//fade.alpha

	UpdateInPlayer.texture = nts.Find("temp");
	UpdateInPlayer.SetDepth(20);
	UpdateInPlayer.transformation.anchor = Anchor::CENTER;
	UpdateInPlayer.transformation.position = Vector2D(2500, 800);
	//애니메이션 여러개 만들어서 활 당기는중일때는 "bow뭐시기" 하고 쏘면 -> "bow발사" 이런식으로 재생
	fade.texture = nts.Find("fade");
	fade.SetDepth(100);
	fade.renderOp = RenderObject::FIT_TO_SCREEN;
	fade.transformation.anchor = Anchor::CENTER;
	fade.transformation.position = Vector2D(2500, 800);
	tempMap.texture = nts.Find("TempMap");
	tempMap.SetDepth(100000);
	tempMap.transformation.scale -= 0.2f;

	
	Skelly.transformation.position = Vector2D(5000, 5000);
	Skelly.transformation.anchor = Anchor::CENTER;
	Skelly.transformation.scale -= 0.3f;
	//Skelly.SetDepth(20);
	//Skelly.transformation.alpha = 0.5f;


	//enemyHitbox.texture = nts.Find("EnemyHitbox");
	//enemyHitbox.SetDepth(18);
	//enemyHitbox.transformation.position = Skelly.transformation.position;
	//enemyHitbox.transformation.anchor = Anchor::CENTER;
	
	Orb1.texture = nts.Find("Orb");
	Orb1.transformation.position = Vector2D(2100, 900);
	Orb1.transformation.anchor = Anchor::BOTTOM;
	Orb1.SetDepth(3000);
	Orb1.transformation.color.SetColor(1.0f, 0, 0);

	MobSpawn.texture = nts.Find("MobSpawn");
	MobSpawn.transformation.position = Vector2D(2730, 1000);
	MobSpawn.transformation.scale -= 0.3f;
	MobSpawn.SetDepth(21);
	MobSpawn.transformation.anchor = Anchor::CENTER;

	masterSceneObject.transformation.anchor = Anchor::CENTER;
	start = false;
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
	playerObjTest.SetDepth(playerObjTest.GetPlayerDepth());
	if (!start) {
		start = true;
		SOUNDMANAGER->play("DeathRoom", 0.6f);
		SOUNDMANAGER->play("DeathRoom1", 0.6f);
		SOUNDMANAGER->play("DeathRoom2", 0.6f);
	}
	Orb1.enabled = true;
	playerObjTest.enabled = true;

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		Skelly.transformation.color.SetColor(10.0f, 10.0f, 10.0f);
	playerObjTest.playerUpdate();
	masterSceneObject.transformation.position = playerObjTest.getPlayerPosition() * -1.0f;
	
	MobSpawn.enabled = true;
	MobSpawnAnim.playObjAnimOnce(MobSpawn, 62, 1);
	if(MobSpawnAnim.GetAnimDone())
		Skelly.transformation.position = Vector2D(2730, 1000);
	Skelly.loop();
	OrbAnim.playObjAnim(Orb1, 39, 2);

	tempObjAnim.playObjAnim(testOrb, 39, 2);
}

void TestScene::OnUpdateLoading()
{
	if (frame >= FADE_IN_FRAME) {
		SceneEndOfLoading();
		frame = 0;
		fade.enabled = false;
		UpdateInPlayer.enabled = false;
	}
	else {
		frame++;
	}
	Orb1.enabled = false;
	MobSpawn.enabled = false;
	playerObjTest.enabled = false;
	Skelly.enable = false;
}

void TestScene::OnUpdateClosing()
{
	if (frame >= FADE_OUT_FRAME) {
		frame = 0;
		fade.enabled = false;
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
	//tempMap.Render();

	masterSceneObject.transformation.position = Vector2D(-2500, -800);
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
