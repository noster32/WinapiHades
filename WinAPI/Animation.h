#pragma once
#include "RenderObject.h"
class Animation : public RenderObject
{
private:
	int animTickDelay;
	int animTick;
	int animTickMove;
	bool bLoopAnimaiton;
public:
	
	void playAnim(SceneObject& tex,  uint start, uint length, uint frame, bool loop);

	Animation() : animTick(0) { }

};

