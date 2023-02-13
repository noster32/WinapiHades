#pragma once
#include "RenderObject.h"
class Animation : public RenderObject
{
private:
	int animTickDelay;
	int animTickIdle;
	int animTickMove;
	int animTickDash;
	int animTickDashVFX;
	bool bLoopAnimaiton;

	bool animIdlePlaying;
	bool animMovePlaying;
	bool animDashPlaying;
	bool animDashVFXPlaying;
	bool animAttackPlaying;
	
	int animTickObj;

	void playIdle(uint start, uint end, bool loop);
	void playMove(uint start, uint end, bool loop);
	void playDash(uint start, uint end, bool loop);
	void playAttack(uint start, uint end, bool loop);

	void animValueReset(uint state);
	void animValueResetVFX(uint state);
public:
	
	void playAnim(SceneObject& tex,  uint start, uint length, uint frame, bool loop, uint state);
	void playAnimVFX(SceneObject& tex, uint start, uint length, uint frame, uint state);
	void playObjAnim(SceneObject& tex, uint length, uint frame);

	bool GetAnimDashPlaying(void) { return animDashPlaying; }
	Animation();

};

