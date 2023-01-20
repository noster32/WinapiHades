#pragma once
#include "GImage.h"

#pragma region ��ü���� 4�� Ư¡ �� 5�� ���� ��Ģ
/*
�� ��ü���� ���α׷���(OOP)
- �ڵ��� ���뼺�� ���� �ڵ� ������ �����ϴ�.
- �ŷڼ��� ���� ���α׷��� �ۼ��� �����ϰ� �Ѵ�.
�� �Ϲ�ȭ ���α׷���


����ü���� 4�� Ư¡
1. ĸ��ȭ
	�� ��ü�� �Ӽ��� ��ȣ�Ѵ�.(��ü�� �Ӽ��� ����ϱ� ���ؼ� ��ȣ�� ������ �Ѵ�.)

2. ���
	�� ��ü���⿡���� ����̶� ������ ���� ������ �� �� ��üȭ �Ǵ� ���� �ǹ��Ѵ�.
	�� ���뼺 ��� / Ȯ�强 ���� / �������� ȿ�� UP

3. ������
	�� �ϳ��� ��ü�� ���� ���·� ���ϴ� ���� �ǹ�(�������̵�)

4. �߻�ȭ
	�� �������� �κа� Ư�� Ư���� �и� �� ������ ������ �ϰų� �籸�� �ϴ� ����
		�� ������ + ����� ��� �߻�ȭ�� ���Ѵ�.


����ü���� 5�� �����Ģ SOLID
1. SRP (���� å���� ��Ģ)
	�� ���յ��� ���߰� �������� ������.

	- ���յ�
	�����(Ŭ����)���� ��ȣ ���� ������ ��Ÿ���� ��ǥ
	�� ���յ��� �������� ��ȣ �������� �پ ���� �� �������� ����
	
	- ������
	�� �ϳ��� ��� ���ο� �����ϴ� ���� ��ҵ��� ��ɼ� ���ü�
	�� �������� ���� ����� �ϳ��� å�ӿ� ������ �� �ְ� �������� ������ ����� ���������� �����ϴ�.

	cf) ��Ӱ� �������̵� ���

2. OCP (���� ����� ��Ģ)
	�� �ڽ��� Ȯ�忡�� ���� �ְ�, �ֺ��� ��ȭ���� ���� �־�� �Ѵٴ� ��Ģ
	�� ���� Ŭ���� �Ǵ� �������̽��� �߰��� �ξ� �ڽ��� ��ȭ�� ���ؼ��� ����ϰ� �������̽��� �ܺ��� ��ȭ�� ���� Ȯ�强�� �����Ѵ�.
	cf) �������̽� ��� - C++���� ���� ���ϱ� ������ ���α׷��� �Ǽ� ���ɼ� ����.

3. LSP (�����ں� ġȯ�� ��Ģ)
	�� ���� Ÿ���� ������ �ڽ��� ����� �Ǵ� ���� Ÿ������ ��ü�� �� �־�� �Ѵ�.
	ex) ����: ��ۼ���, �ڵ��� / ����: �ƹ���, �׷���, ���׽ý�...

4. ISP (�������̽� �и��� ��Ģ)
	�� Ŭ���̾�Ʈ�� �ڽ��� ������� �ʴ� �Լ�(�޼���)�� ���� ���踦 ������ �� �ȴ�.
	�� �������̽��� �� ����� �и��Ͽ� ����ϴ� �Լ�(�޼���)���� ���� ���踦 �����Ѵ�.
	�� ���� ����� ���� �ִ� ������Ʈ�� ���� ��Ŀ� ���� SRP or ISP �� �����Ѵ�.

5. DIP (�������� ������ ��Ģ)
	�� �ڽź��� ���ϱ� ���� �Ϳ� ���� �������� ���ƾ� �Ѵ�.
*/
#pragma endregion

static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;

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

	LRESULT MainProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
};
