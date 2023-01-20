#pragma once
#include "GameNode.h"
#include "PixelCollision.h"

class PixelScene : public GameNode
{
private:
	PixelCollision* _pixel;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PixelScene() {}
	~PixelScene() {}
};

