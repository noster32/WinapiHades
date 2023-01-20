#include "Stdafx.h"
#include "Flame.h"

/*
HRESULT Flame::init(void)
{
	IMAGEMANAGER->addFrameImage("ºÒ²É", "Resources/Images/Object/Flame.bmp",
		432, 297, 9, 1, true, RGB(255, 0, 255));

	_tick = 0;

	_flameIdx = 0;

	return S_OK;
}
*/

HRESULT Flame::init(const char* imageName, float* x, float* y)
{
	_image = IMAGEMANAGER->addFrameImage("ºÒ²É", "Resources/Images/Object/Flame.bmp",
		0.0f, 0.0f, 432, 297, 9, 1, true, RGB(255, 0, 255));

	_x = x;
	_y = y;

	_rc = RectMakeCenter((int)_x, (int)_y, _image->getFrameWidth(), _image->getFrameHeight());

	_flameTick = 7.0f;

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{
	if (FLAME_COUNT + _flameTick <= GetTickCount64())
	{
		_flameTick = GetTickCount64();
		_image->setFrameX(_image->getFrameX() + 1);

		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}

	_rc = RectMakeCenter(*_x, *_y + 180, _image->getFrameWidth(), _image->getFrameHeight());

	/*_tick++;

	if (_tick % 1 == 0)
	{
		_flameIdx++;
		if (_flameIdx >= 9) _flameIdx = 0;
	}*/
}

void Flame::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}

/*
void Flame::flameRender(int x, int y, int z)
{
	IMAGEMANAGER->frameRender("ºÒ²É", getMemDC(), x, y, z, 0);
}
*/