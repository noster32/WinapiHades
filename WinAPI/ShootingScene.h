#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

class ShootingScene : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;

	float _x, _y;
	char _text[64];

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void); //호출이되지 않으면 메모리에 넣지 않기위해 가상화시킴

	ShootingScene() {}
	~ShootingScene() {}
};

