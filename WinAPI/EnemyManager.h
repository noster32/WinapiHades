#pragma once
#include "GameNode.h"
// �ּҸ� ���� ���� ����
#include "Enemy.h"
#include "Bullets.h"

class Rocket;

class EnemyManager : public GameNode
{
private:
	// ������ ����� �����ϴ� ����
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	// �θ� �����ϰ� �ڽĿ��� ������ �ؼ� ����ϰڴ�. �� 1�� ���� ����
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