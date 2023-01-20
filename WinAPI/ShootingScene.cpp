#include "Stdafx.h"
#include "ShootingScene.h"

HRESULT ShootingScene::init(void)
{
	IMAGEMANAGER->addImage("전장", "Resources/Images/Background/BattleField.bmp",
		WINSIZE_X, WINSIZE_Y);

	_rocket = new Rocket;
	_rocket->init();

	_em = new EnemyManager;
	_em->init();
	
	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);


	wsprintf(_text, "Shooting Scene");

	_x = _y = 0.0f;

	return S_OK;
}

void ShootingScene::release(void)
{

	_rocket->release();
	SAFE_DELETE(_rocket);

	_em->release();
	SAFE_DELETE(_em);
}

void ShootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->changeScene("시작");
	}

	_rocket->update();
	_em->update();

	collision();

	_y -= 2.0f;
}

void ShootingScene::render(void)
{
	RECT rc = { 0,0,WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("전장")->loopRender(getMemDC(), &rc, _x, _y);

	_rocket->render();
	_em->render();

	TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));
}
