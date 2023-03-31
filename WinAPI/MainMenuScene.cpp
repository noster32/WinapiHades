#include "Stdafx.h"
#include "MainMenuScene.h"

void MainMenuScene::Init()
{
	scene::AddSceneToMap(this, "MainMenu");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	SOUNDMANAGER->addSound("MainMenuBGM", "Resources/Sounds/MainMenu.wav", false, true);
	MainMenuLoop.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/MainMenuLoop.avi");
	MainMenuLoop.transformation.position.y -= 5.0f;
	MainMenuLoop.transformation.scale -= 0.15f;
	MainMenuLoop.SetDepth(21);

	nts.Add(gl.LoadTexturePng("Resources/Images/Object/start.png", param), "startButton");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/end.png", param), "endButton");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/idle.png", param), "temp");

	RegisterObject(MainMenuLoop);
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

	start = false;
	startInEnd = false;
	MainMenuLoop.enable = true;
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
		SOUNDMANAGER->play("MainMenuBGM", 0.5f);
	}
	
	MainMenuLoop.loop();

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
	gl.RenderText("Test", 0, 0, 1.0f);
}

void MainMenuScene::OnRenderClosing()
{
	SceneEndOfClosing();
}
