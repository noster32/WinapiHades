#include "Stdafx.h"
#include "Animation.h"

void Animation::playAnim(SceneObject& tex, uint start, uint length, uint frame, bool loop)
{
	
	if (start <= 0) start = 0;
	uint temp = start + length;
	if (animTick < start)
		animTick = start;
	if (loop)
	{
		if (animTick > temp)
			animTick = start;
	}
	else
	{
		if (animTick > temp)
			animTick = temp;
	}

	animTickDelay++;

	if(animTickDelay % frame == 0)
		animTick++;
	
	tex.SetTick(animTick);
	
}
