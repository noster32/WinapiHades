#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_ps = new PixelScene();
	_ps->init();

	_tempSound = new TempSoundScene();
	_tempSound->init();
	return S_OK;
}

void SecondScene::release(void)
{
	_ps->release();
	_tempSound->release();
}

void SecondScene::update(void)
{
	_bgSpeed += 3;
	_ps->update();
	_tempSound->update();
}

void SecondScene::render(void)
{
	//IMAGEMANAGER->loopRender("������", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);

	// SetBkMode() : �����ϰ� ���ִ� �Լ�
	// ������ �ڷ� ����� ���̰� �Ѵ�.
	_ps->render();
}
