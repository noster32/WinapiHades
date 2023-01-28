#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "SoundScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	//SCENEMANAGER->addScene("시작", new StartScene);
	SCENEMANAGER->addScene("사운드", new SoundScene);

	SCENEMANAGER->changeScene("사운드");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();

	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC());
}


