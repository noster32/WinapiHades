#include "Stdafx.h"
#include "PixelScene.h"

HRESULT PixelScene::init(void)
{
	IMAGEMANAGER->addImage("¿ïÅüºÒÅü", "Resources/Images/Background/BG.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	_pixel = new PixelCollision;
	_pixel->init();

	return S_OK;
}

void PixelScene::release(void)
{
	SAFE_DELETE(_pixel);
}

void PixelScene::update(void)
{
	_pixel->update();
}

void PixelScene::render(void)
{
	IMAGEMANAGER->findImage("¿ïÅüºÒÅü")->render(getMemDC());
	_pixel->render();
}
