#pragma once
#include "GameNode.h"

#define FLAME_COUNT	4.0f

class Flame : public GameNode
{
private:
	GImage* _image;
	RECT _rc;

	float* _x;


	float* _y;
	float _flameTick;

	//int _tick;
	//int _flameIdx;

public:
	HRESULT init(const char* imageName, float* x, float* y);
	void release(void);
	void update(void);
	void render(void);

	//void flameRender(int x, int y, int z);

	//int getFlameIdx() { return _flameIdx; }

	Flame() {}
	~Flame() {}
};