#pragma once
#include "GameNode.h"

// Enemy (부모 클래스): 이 클래스를 기반으로 보스, 일반 몬스터 등을 만들 수 있다.
class Enemy : public GameNode
{
protected:
	GImage* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

	float _rndFireCount;
	float _bulletFireCount;


public:
	HRESULT init(void);
	HRESULT init(const char* imgName, POINT position);

	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

	bool bulletCountFire(void);

	RECT getRect(void) { return _rc; }

	Enemy(void);
	~Enemy(void) {}
};

