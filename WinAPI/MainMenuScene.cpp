#include "Stdafx.h"
#include "MainMenuScene.h"

void MainMenuScene::Init()
{
	scene::AddSceneToMap(this, "MainMenu");

	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	SOUNDMANAGER->addSound("MainMenuBGM", "Resources/Sounds/MainMenu.wav", false, true);
	MainMenuIn.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/MainMenuIn.avi");
	MainMenuLoop.load_frame("G:/SteamLibrary/steamapps/common/Hades/Content/Movies/Test/MainMenuLoop.avi");
	//MainMenuIn.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/MainMenuIn.avi");
	//MainMenuLoop.load_frame("C:/Program Files (x86)/Steam/steamapps/common/Hades/Content/Movies/Test/MainMenuLoop.avi");
	MainMenuLoop.transformation.position.y -= 5.0f;
	MainMenuLoop.transformation.scale -= 0.15f;
	MainMenuLoop.SetDepth(21);

	nts.Add(gl.GenerateEmptyTexture(200, 100, 0xFFFFFFFF), "test1");
	testBox1.texture = nts.Find("test1");
	testBox1.transformation.position = Vector2D(200, 100);
	testBox1.transformation.anchor = Anchor::CENTER;
	testBox1.SetDepth(1);
	nts.Add(gl.GenerateEmptyTexture(200, 100, 0xFFFFFFFF), "test2");
	testBox2.texture = nts.Find("test2");
	testBox2.transformation.position = Vector2D(1000, 100);
	testBox2.transformation.anchor = Anchor::CENTER;
	testBox2.SetDepth(1);

	nts.Add(gl.LoadTexturePng("Resources/Images/Object/start.png", param), "startButton");
	nts.Add(gl.LoadTexturePng("Resources/Images/Object/end.png", param), "endButton");

	RegisterObject(MainMenuLoop);
	RegisterObject(startbutton);
	RegisterObject(endbutton);
	//RegisterObject(testBox1);
	//RegisterObject(testBox2);

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
		//MainMenuIn.SetAnimPlaying();
	}
	if (!startInEnd) {
		//MainMenuIn.playOnce(0, 0, 0, 2666667);
		//if (!MainMenuIn.GetAnimPlaying())
		//	startInEnd = true;
	}
	
	MainMenuLoop.loop();

	//printf("test");

	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		QueueSceneSwap("game");
		SceneEndOfUpdate();
		SOUNDMANAGER->stop("MainMenuBGM");
	}

	
	if (KEYMANAGER->isStayKeyDown('Q')) {
		testBox1.transformation.rotate += 3.0f;
		printf("%f \n", testBox1.transformation.rotate.getDegree());
		printf("lb: %f, %f lt: %f, %f rb: %f, %f rt: %f, %f\n", test.rLeftBottom.x, test.rLeftBottom.y, test.rLeftTop.x, test.rLeftTop.y, test.rRightBottom.x, test.rRightBottom.y, test.rRightTop.x, test.rRightTop.y);
	}
	if (KEYMANAGER->isStayKeyDown('E')) {
		testBox1.transformation.rotate -= 3.0f;
		printf("%f \n", testBox1.transformation.rotate.getDegree());
		printf("lb: %f, %f lt: %f, %f rb: %f, %f rt: %f, %f\n", test.rLeftBottom.x, test.rLeftBottom.y, test.rLeftTop.x, test.rLeftTop.y, test.rRightBottom.x, test.rRightBottom.y, test.rRightTop.x, test.rRightTop.y);
	}

	if (KEYMANAGER->isStayKeyDown('A')) {
		testBox1.transformation.position.x -= 3.0f;
		printf("%f \n", testBox1.transformation.position.x);
	}
	if (KEYMANAGER->isStayKeyDown('D')) {
		testBox1.transformation.position.x += 3.0f;
		printf("%f \n", testBox1.transformation.position.x);
	}
	
	//test = Rect2D(testBox1.transformation.position, 200, 100, testBox1.transformation.rotate.getDegree());
	//test2 = Rect2D(testBox2.transformation.position, 200, 100, testBox2.transformation.rotate.getDegree());
	//
	//if (test.IntersectRotatedRect2D(test2)) {
	//	printf("Collision!\n");
	//}
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
