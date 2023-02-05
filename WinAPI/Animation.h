#pragma once
#include "RenderObject.h"
class Animation : public RenderObject
{
private:
	int animTickDelay;
	int animTickIdle;
	int animTickMove;
	int animTickDash;
	bool bLoopAnimaiton;

	bool animIdlePlayeing;
	bool animMove

	void playIdle(void);
	void playMove(void);
	void playDash(void);
	void playAttack(void);
public:
	
	void playAnim(SceneObject& tex,  uint start, uint length, uint frame, bool loop, uint state);

	Animation() { }

};

