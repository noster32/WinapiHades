#include "Stdafx.h"
#include "Animation.h"

void Animation::playAnim(SceneObject& tex, uint start, uint length, uint frame, bool loop)
{

	uint temp = start + length - 2;

	if (animTick < start || animTick > temp)
	{
		anim
		tex.SetTick(start);

	}
		

	animTickDelay++;
	
	
	if (animTickDelay % frame == 0)
	{
		animTick++;
		animTickDelay = 0;
		tex.SetTick(animTick);
	}
		
	if (start <= 0) start = 0;
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
}
