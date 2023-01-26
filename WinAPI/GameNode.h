#pragma once
#include "GImage.h"

struct GameEngineInitializer {
	HINSTANCE hInstance;
	int nCmdShow;
	HWND mainWnd;
	Point2D windowSize;
	string title;
	uint updateDelay;
	uint drawDelay;
	bool keepUpdateOnBackground;
	bool keepDrawOnBackground;
};

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	HGLRC _hrc;
	HANDLE mutex;
	bool _managerInit;
	int visibleHeight;
	GLAPI gl;

public:
	// HRESULT: �Լ��� ���������� ����Ǿ����� üũ
	// �� 32��Ʈ signed ����(������ �ƴ� ������ ������ �ǹ��ϸ� ���������� ���и� �ǹ��Ѵ�.)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(GameEngineInitializer& param);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	GImage* getBackBuffer(void) { return _backBuffer; }

	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���(ȭ�� DC)
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
};

