#include "Stdafx.h"
#include "MainMenuScene.h"

void MainMenuScene::Init()
{
	scene::AddSceneToMap(this, "MainMenu");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	//SOUNDMANAGER->addSound("InSound", , false, false);
	//SOUNDMANAGER->addSound("MainMenuBGM", "Resources/Sounds/01 No Escape 44khz 16bit HDK MSTR.wav", true, true);
	SOUNDMANAGER->addSound("MainMenuBGM", "Resources/Sounds/MainMenu.wav", false, true);
	MainMenuIn.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/MainMenuIn.avi");

	MainMenuLoop = new nFFmpeg;
	MainMenuLoop->load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/MainMenuLoop.avi");
	//MainMenuIn.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/MainMenuIn.avi");
	//MainMenuLoop.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/MainMenuLoop.avi");
	MainMenuLoop->transformation.anchor = Anchor::CENTER;
	MainMenuLoop->transformation.scale -= 0.15f;

	nts.Add(gl.LoadTexturePng("Resources/Images/Object/start.png", param), "startButton");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/end.png", param), "endButton");

	RegisterObject(startbutton);
	RegisterObject(endbutton);

	startbutton.texture = nts.Find("startButton");
	startbutton.transformation.position = Vector2D(100, 300);
	startbutton.transformation.scale -= 0.2f;
	startbutton.SetDepth(20);
	endbutton.texture = nts.Find("endButton");
	endbutton.transformation.position = Vector2D(100, 200);
	endbutton.transformation.scale -= 0.2f;
	endbutton.SetDepth(20);

	//startbuttonInter = Rect2D

	start = false;
	startInEnd = false;
	MainMenuLoop->enable = true;
	MainMenuLoop->SetUpdateFrame(30);
}

void MainMenuScene::OnBegin()
{
}

void MainMenuScene::OnEnd()
{
}

void MainMenuScene::OnUpdate()
{
	if (!start) {
		start = true;
		SOUNDMANAGER->play("MainMenuBGM", 0.6f);
		MainMenuIn.SetAnimPlaying();
	}
	if (!startInEnd) {
		MainMenuIn.playOnce(0, 0, 0, 2666667);
		if (!MainMenuIn.GetAnimPlaying())
			startInEnd = true;
	}
	else
		MainMenuLoop->loop();
		
	//printf("test");

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		QueueSceneSwap("game");
		SceneEndOfUpdate();
		SOUNDMANAGER->stop("MainMenuBGM");
	}
}

void MainMenuScene::OnUpdateLoading()
{
	SceneEndOfLoading();
}

void MainMenuScene::OnUpdateClosing()
{
	SceneEndOfClosing();
}

void MainMenuScene::OnRenderLoading()
{
}

void MainMenuScene::OnRender()
{
}

void MainMenuScene::OnRenderClosing()
{
	SceneEndOfClosing();
}
