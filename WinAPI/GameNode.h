#pragma once
#include "GImage.h"

struct EngineInit {
	uint updateDelay;
	uint renderDelay;
	bool updateOnBackground;
	bool renderOnBackground;
};

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
public:
	enum EngineState {
		OK					= 0,
		OPENGL_NOT_READY	= (1<<0),
		NO_CURRENT_SCENE	= (1<<1),
		ENGINE_STOPPED		= (1<<2)
	};
private:
	
	HDC _hdc;
	HGLRC _hrc;
	bool _managerInit;
	bool isWindowsActive;
	int visibleHeight;

	//OpenGL API
	GLAPI gl;

	//��Ƽ �������
	mutex _mutex;
	bool threadExit;

	//���� State
	int egState;
	string stateString;
	
	bool updateOnBackground;
	bool renderOnBackground;

public:
	// HRESULT: �Լ��� ���������� ����Ǿ����� üũ
	// �� 32��Ʈ signed ����(������ �ƴ� ������ ������ �ǹ��ϸ� ���������� ���и� �ǹ��Ѵ�.)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(bool managerInit, EngineInit& param);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void engineStateUpdate(void);

	GImage* getBackBuffer(void) { return _backBuffer; }

	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���(ȭ�� DC)
	HDC getHDC() { return _hdc; }

	int GetEngineState() { return egState; }
	string GetEngineStateString() { return stateString; }

	void SetExitThread() { threadExit = true; }
	bool GetExitThread() { return threadExit; }

	LRESULT MainProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode() {}
};

