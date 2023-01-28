#pragma once
#include "GImage.h"
#include "GameEngine.h"

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	EngineInit param;
	GameEngine* _ge;

public:
	// HRESULT: �Լ��� ���������� ����Ǿ����� üũ
	// �� 32��Ʈ signed ����(������ �ƴ� ������ ������ �ǹ��ϸ� ���������� ���и� �ǹ��Ѵ�.)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	GImage* getBackBuffer(void) { return _backBuffer; }

	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���(ȭ�� DC)
	HDC getHDC() { return _hdc; }

	GameNode() {}
	virtual ~GameNode() {}
};

