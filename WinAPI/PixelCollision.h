#pragma once
#include "GameNode.h"

class PixelCollision : public GameNode
{
private:
	GImage* _pixelTank;
	RECT _rc;
	int _probeY;
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PixelCollision(){}
	~PixelCollision(){}
};

