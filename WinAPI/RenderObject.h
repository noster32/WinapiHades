#pragma once
#include "SceneObject.h"

class RenderObject : public SceneObject
{
public:
	enum RenderingOption {
		TEXTURE_SIZE = (1 << 0),
		GIVEN_SIZE = (1 << 1),
		STRETCH_HOR = (1 << 2),
		STRETCH_VER = (1 << 3),
		FIT_TO_SCREEN = (STRETCH_HOR | STRETCH_VER),
		FIT_TO_SCREEN_KEEP_RATIO = (1 << 4)
	};

public:
	uint texture;
	uint renderOp;
	Point2D renderSize;

public:
	RenderObject() : renderOp(RenderObject::TEXTURE_SIZE) { }
	void SetTexture(uint texture);
	virtual void Render();
};

