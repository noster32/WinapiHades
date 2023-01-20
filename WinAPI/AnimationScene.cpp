#include "Stdafx.h"
#include "AnimationScene.h"

HRESULT AnimationScene::init(void)
{
	_image = IMAGEMANAGER->addImage("ÄÚ³¢¸®", "Resources/Images/Object/Elephant.bmp",
		660, 268, true, RGB(255, 0, 255));

	_animationA = new Animation;
	// ->
	_animationA->init(_image->getWidth(), _image->getHeight(), 110, 67);
	_animationA->setDefPlayFrame(false, true);
	//_animationA->setPlayFrame(11,17,true, true);
	// >-
	//_animationA->setFPS(12);
	_animationA->setFPS(60);
	return S_OK;
}

void AnimationScene::release(void)
{
	_animationA->release();
	SAFE_DELETE(_animationA);
}

void AnimationScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_animationA->aniStart();
	}

	_animationA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AnimationScene::render(void)
{
	_image->aniRender(getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 2, _animationA);
}
