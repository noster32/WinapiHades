#pragma once
#include "GameNode.h"
// 주소를 통한 오류 방지
#include "Enemy.h"
#include "Bullets.h"

class Rocket;

class EnemyManager : public GameNode
{
private:
	// 범용적 기능을 지원하는 원본
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	// 부모를 참조하고 자식에서 재정의 해서 사용하겠다. 적 1에 대한 정보
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet* _bullet;
	Rocket* _rocket;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinion() { return _vMinion; }
	Bullet* getBullet(void) { return _bullet; }
	void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }


	EnemyManager() {}
	~EnemyManager() {}
};