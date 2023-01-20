#include "Stdafx.h"
#include "Rocket.h"
#include "EnemyManager.h"

HRESULT Rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("╥ндо", "Resources/Images/Object/Rocket.bmp",
		52, 64, true, RGB(255, 0, 255));

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y - 100;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	_flame = new Flame;
	_flame->init("Flame.bmp", &_x, &_y);

	//_missile = new Missile;
	//_missile->init(100, 100);

	_missileM1 = new MissileM1;
	_missileM1->init(5, 700);

	_beam = new Beam;
	_beam->init(1, 0.5);
	_beamIrradiation = false;

	_hpBar = new ProgressBar;
	_hpBar->init(_x, _y, 52, 4);

	_currentHP = 10;
	_maxHP = 10;

	_setWeapon = MISSILE;

	//missileCnt = 0;
	

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);
	//_missile->release();
	//SAFE_DELETE(_missile);
	_missileM1->release();
	SAFE_DELETE(_missileM1);
	_beam->release();
	SAFE_DELETE(_beam);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void Rocket::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('1')) hitDamage(1.0f);
	if (KEYMANAGER->isOnceKeyDown('2')) hitDamage(-1.0f);


	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X && _beamIrradiation == false)
	{
		_x += ROCKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _beamIrradiation == false)
	{
		_x -= ROCKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_setWeapon = MISSILE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_setWeapon = BEAM;
	}


	switch (_setWeapon)
	{
	case MISSILE:
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_missileM1->fire(_x, _y - 60);
		}
		break;

	case BEAM:
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			_beamIrradiation = true;
			_beam->fire(_x, _y - 430);
		}
		else
		{
			_beamIrradiation = false;
		}
		break;
	}


	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	
	_flame->update();
	//_missile->update();
	_missileM1->update();
	_beam->update();

	//collision();

	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGauge(_currentHP, _maxHP);
}

void Rocket::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();

	//_missile->render();
	_missileM1->render();
	_beam->render();

	_hpBar->render();


}

void Rocket::collision(void)
{
	for (int i = 0; i < _missileM1->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
				//&_em->getMinion()[j]->getRect()))
			{
				_missileM1->removeBullet(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _beam->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_beam->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
				//&_em->getMinion()[j]->getRect()))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void Rocket::removeMissile(int arrNum)
{
	_missileM1->removeBullet(arrNum);
}

