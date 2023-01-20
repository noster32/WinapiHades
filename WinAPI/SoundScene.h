#pragma once
#include "GameNode.h"
class SoundScene : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

