#include "Stdafx.h"
#include "Animation.h"
Animation::Animation() : animTickDelay(0),
						animIdlePlaying(false),
						animMovePlaying(false),
						animDashPlaying(false),
						animDashVFXPlaying(false)
{
}

void Animation::playAnim(SceneObject& tex, uint start, uint length, uint frame, bool loop, uint state)
{
	uint temp = start + length - 2;

	animTickDelay++;
	animValueReset(state);

	if (state == 0)
	{
		if (animTickDelay % frame == 0)
		{
			playIdle(start, temp, loop);
			animTickDelay = 0;
			tex.SetTick(animTickIdle);
		}
	}
	else if (state == 1)
	{
		if (animTickDelay % frame == 0)
		{
			playMove(start, temp, loop);
			animTickDelay = 0;
			tex.SetTick(animTickMove);
		}
	}
	else if (state == 2)
	{
		if (animTickDelay % frame == 0)
		{
			playDash(start, temp, loop);
			animTickDelay = 0;
			tex.SetTick(animTickDash);
		}
	}

		
}

void Animation::playAnimVFX(SceneObject& tex, uint start, uint length, uint frame)
{
	uint temp = start + length - 2;
	
	if (start <= 0) start = 0;

	if (!animDashVFXPlaying)
	{
		animTickDashVFX = start;
		animDashVFXPlaying = true;
	}
		
	if (animTickDelay % frame == 0)
	{
		animTickDashVFX++;
		animTickDelay = 0;
		tex.SetTick(animTickDashVFX);
	}

	if (animTickDashVFX >= temp)
	{
		animTickDashVFX = temp;
		animDashVFXPlaying = false;
	}

}



void Animation::playIdle(uint start, uint end, bool loop)
{
	animTickIdle++;
	if (start <= 0) start = 0;
	if (!animIdlePlaying)
	{
		animTickIdle = start;
		animIdlePlaying = true;
	}

	if (loop)
	{
		if (animTickIdle >= end)
		{
			animTickIdle = start;
			animIdlePlaying = false;
		}
	}
	else
	{
		if (animTickIdle >= end)
		{
			animTickIdle = end;
			animIdlePlaying = false;
		}	
	}
}

void Animation::playMove(uint start, uint end, bool loop)
{
	animTickMove++;
	if (start <= 0) start = 0;
	if (animTickMove < start || animTickMove > end)
		animTickMove = start;
	if (!animMovePlaying)
	{
		animTickMove = start;
		animMovePlaying = true;
	}


	if (loop)
	{
		if (animTickMove >= end)
		{
			animTickMove = start;
			animMovePlaying = false;
		}
			
	}
	else
	{
		if (animTickMove >= end)
		{
			animTickMove = end;
			animMovePlaying = false;
		}
				}
}

void Animation::playDash(uint start, uint end, bool loop)
{
	animTickDash++;
	if (start <= 0) start = 0;
	if (!animDashPlaying)
	{
		animTickDash = start;
		animDashPlaying = true;
	}
		

	if (loop)
	{
		if (animTickDash >= end)
		{
			animTickDash = start;
			animDashPlaying = false;
		}
			
	}
	else
	{
		if (animTickDash >= end)
		{
			animTickDash = end;
			animDashPlaying = false;
		}
	}
}

void Animation::playAttack(uint start, uint end, bool loop)
{
}

void Animation::animValueReset(uint state)
{
	switch (state)
	{
	case 0:
		animTickMove = 0;
		animMovePlaying = false;
		animTickDash = 0;
		animDashPlaying = false;
		break;
	case 1:
		animTickIdle = 0;
		animIdlePlaying = false;
		animTickDash = 0;
		animDashPlaying = false;
		break;
	case 2:
		animTickIdle = 0;
		animIdlePlaying = false;
		animTickMove = 0;
		animMovePlaying = false;
		break;
	case 3:
		break;
	case 4:
		break;
	}
}


