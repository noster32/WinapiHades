#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"

#define ROCKET_SPEED	5.0f

class EnemyManager;

enum EWeapon
{
	MISSILE, BEAM
};

class Rocket : public GameNode
{
private:
	GImage* _image;
	Flame* _flame;

	//Missile* _missile;
	MissileM1* _missileM1;
	Beam* _beam;
	EWeapon _setWeapon;

	ProgressBar* _hpBar;

	EnemyManager* _em;

	RECT _rc;
	float _x, _y;
	bool _beamIrradiation;

	float _currentHP;
	float _maxHP;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision(void);
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }

	void removeMissile(int arrNum);

	MissileM1* getMissile(void) { return _missileM1; }
	Beam* getBeam(void) { return _beam; }

	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
	RECT getRect(void) { return _rc; }

	inline void hitDamage(float damage)
	{
		if (_currentHP <= 0)
		{
			_currentHP = 0;
			return;
		}

		_currentHP -= damage;
	}

	Rocket() {}
	~Rocket() {}
};