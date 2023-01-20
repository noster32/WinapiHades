#include "Stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(void)
{
    _pixelTank = IMAGEMANAGER->addImage("픽셀 탱크", "Resources/Images/Object/Tank.bmp", 70, 60, true, RGB(255, 0, 255));

    _x = WINSIZE_X / 2 + 250;
    _y = WINSIZE_Y / 2 + 100;

    _rc = RectMakeCenter(_x, _y, _pixelTank->getWidth(), _pixelTank->getHeight());

    // Y축 탐지
    _probeY = _y + _pixelTank->getHeight() / 2;

    return S_OK;
}

void PixelCollision::release(void)
{
    SAFE_DELETE(_pixelTank);
}

void PixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 2.0f;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 2.0f;

	_probeY = _y + _pixelTank->getHeight() / 2;

	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		// GetPixel(): 지정된 좌표의 색상을 얻어온다.
		// ㄴ hdc, x, y가 들어온다.
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("울퉁불퉁")->getMemDC(), _x, i);

		// 각각의 RGB 색상을 가져온다.
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _pixelTank->getHeight() / 2;
			break;
		}
	}

	// 사각형 갱신
	_rc = RectMakeCenter(_x, _y, _pixelTank->getWidth(), _pixelTank->getHeight());
}

void PixelCollision::render(void)
{
	_pixelTank->render(getMemDC(), _rc.left, _rc.top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}
}
