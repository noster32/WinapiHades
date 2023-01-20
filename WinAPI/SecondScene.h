#pragma once
#include "GameNode.h"
#include "PixelScene.h"
#include "TempSoundScene.h"

class SecondScene : public GameNode
{
private:
	PixelScene* _ps;
	TempSoundScene* _tempSound;
	int _offsetX;
	int _offsetY;

	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SecondScene() {}
	~SecondScene() {}
};

