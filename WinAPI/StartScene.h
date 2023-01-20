#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	float _alpha;
	float _bgAlpha;
	char _text[64];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StartScene() {}
	~StartScene() {}
};
