#include "Stdafx.h"
#include "Animation.h"

void Animation::playAnim(SceneObject& tex, uint start, uint length, uint frame, bool loop, uint state)
{
	uint temp = start + length - 2;

	//if (animTick != start)
	//{
	//	animTick = start;
	//	tex.SetTick(animTick);
	//}
	//	
	animTickDelay++;
	
	if (state == 0)
	{
		animTickMove = 0;
		animTickDash = 0;

		if (start <= 0) start = 0;
		if (animTickIdle < start || animTickIdle > temp)
			animTickIdle = start;

		if (animTickDelay % frame == 0)
		{
			animTickIdle++;
			animTickDelay = 0;
			tex.SetTick(animTickIdle);
		}

		if (loop)
		{
			if (animTickIdle > temp)
				animTickIdle = start;
		}
		else
		{
			if (animTickIdle > temp)
				animTickIdle = temp;
		}
	}
	else if (state == 1)
	{
		animTickIdle = 0;
		animTickDash = 0;

		if (start <= 0) start = 0;
		if (animTickMove < start || animTickMove > temp)
			animTickMove = start;

		if (animTickDelay % frame == 0)
		{
			animTickMove++;
			animTickDelay = 0;
			tex.SetTick(animTickMove);
		}

		if (loop)
		{
			if (animTickMove > temp)
				animTickMove = start;
		}
		else
		{
			if (animTickMove > temp)
				animTickMove = temp;
		}
	}
	else if (state == 2)
	{
		animTickIdle = 0;
		animTickDash = 0;

		if (start <= 0) start = 0;
		if (animTickMove < start || animTickMove > temp)
			animTickMove = start;

		if (animTickDelay % frame == 0)
		{
			animTickMove++;
			animTickDelay = 0;
			tex.SetTick(animTickMove);
		}

		if (loop)
		{
			if (animTickMove > temp)
				animTickMove = start;
		}
		else
		{
			if (animTickMove > temp)
				animTickMove = temp;
		}
	}

		
}

void Animation::playAnim(SceneObject& tex, uint start, uint end, bool loop, uint frame, uint)
{
}

void Animation::playIdle(void)
{
}

void Animation::playMove(void)
{
}

void Animation::playDash(void)
{
}

void Animation::playAttack(void)
{
}
