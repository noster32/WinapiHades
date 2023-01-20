#include "Stdafx.h"
#include "Bullets.h"

HRESULT Bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;


	return S_OK;
}

void Bullet::release(void)
{
	_vBullet.clear();
}

void Bullet::update(void)
{
	move();
}

void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	//�������Ҷ� ��۸� �����Ͱ� �߻��� ������ �ְ�,
	//���͸��� �Ѿ˸���� �ٸ� �� �ֱ� ������ ������ �ϸ�ȵ�
	//bullet.img = new GImage;
	//bullet.img->init("Resources/Images/Object/Missile2.bmp", 0.0f, 0.0f,
	//	416, 64, 13, 1, true, RGB(255, 0, 255));
	
	//�� �߻�ȭ�� �ذ� ����
	bullet.img = IMAGEMANAGER->findImage(_imageName);
	
	bullet.speed = speed;
	bullet.angle = angle;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//DrawRectMake(getMemDC(), _viBullet->rc);
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		// ��Ÿ� ������ ������.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//SAFE_DELETE(_viBullet->img); -> ��۸� ����Ʈ �߻� �ڵ�
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}


HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		// ZeroMemory(): ù ��° ���ڰ� ����Ű�� �ּ��� ���� 0���� �ʱ�ȭ
		//  �� ����: �޸� ���, �޸� ��� ������
		// ZeroMemory�� ���������� memset�� ȣ���ϰ� �ִ�.
		ZeroMemory(&bullet, sizeof(tagBullet));

		bullet.img = new GImage;
		bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
			416, 64, 13, 1, true, RGB(255, 0, 255));

		bullet.fire = false;
		bullet.speed = 5.0f;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Missile::update(void)
{
	move();
}

void Missile::render(void)
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void Missile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}

			_viBullet->count = 0;
		}

		//_viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
	}
}

void Missile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		// ��Ÿ� ������ ������.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}



// #####################################################



HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();
}

void MissileM1::render(void)
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	// �ִ� �߻� ������ ���´�.
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/Object/Missile2.bmp", 0.0f, 0.0f,
		416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 4.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void MissileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{

		//DrawRectMake(getMemDC(), _viBullet->rc);
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		_viBullet->bulletDistance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y + 100);

		// ��Ÿ� ������ ������.
		if (_range < _viBullet->bulletDistance)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void MissileM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void Beam::release(void)
{
	// �ʱ���� �ۿ� ������ ��������Ʈ�� ���ٽ����� ������ �Ұ���. ��ǥ���̱� ����.
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	// ���������� �Ʒ��� ���� �ݺ��� ����.
	// �������� auto�� ������� ����.
	/*iterBullet iterBullet = _vBullet.begin();
	for (; iterBullet != _vBullet.end(); ++iterBullet)
	{
		SAFE_DELETE(iterBullet->img);
	}*/

	// �����̳� ��� for��. �������� ���� ����.
	/*for (auto iter : _vBullet)
	{
		SAFE_DELETE(iter.img);
	}*/

	// �˰��� �Լ��̱⿡ �ſ� ���ſ�.
	/*for each (auto iter in _vBullet)
	{
		SAFE_DELETE(iter.img); �� ����. ���۰� ������ �𸣱⿡ ���� ������ ���� ����.
	}*/

	// C++ 17���� ��� Ȯ��.
	// �ݺ����� ���۰� ��, �Լ��� �Ķ���ͷ� �޴´�.
	// ����Լ�: �Լ����� �ڱ� �ڽ��� ȣ���ϴ� ��.
	/*for_each(_vBullet.begin(), _vBullet.end(), update);
	{

	}

	int Value = 0;
	for_each(_vBullet.begin(), _vBullet.end(), [&Value](auto& number)
		{
			Value += number;
		});*/

	/*
		[] () {} ()

		- [ĸó] (�Ű� ����) {(��ȯ)�Լ� ����} (ȣ�� ����(���� ����))

		[] (int numA, int numB) { cout << numA + bumB << endl; } (10, 20)
		[] (int numA, int numB) { return numA + numB } (10, 20)
	*/

	/*int numberA = 10;
	int numberB = 10;

	auto resultA = [](int numA, int numB) {return numA + numB;} (10, 10);
	auto resultB = [&]()->int {return numberA + numberB;} ();
	auto resultC = [=, &numberA]()->int {return numberA + numberB;} ();*/

	/*
		[]: ���� ������ �ִ� ��� ������ ���� �Ұ�
		[&]: ���� ������ �ִ� ��� ������ ������ ĸó.
		[=]: ���� ������ �ִ� ��� ������ ������ ĸó.
		[=, &����A]: ���� ������ �ִ� ��� ������ ������ ĸó�ϰڴ�. ��, ����A�� ����.
	*/

	/*
		��������Ʈ(�̺�Ʈ) > ������ > �븮��(�ڵ鷯)
		����ϱ� ���� �Լ��� �����ڿ� ���. ��������Ʈ�� ȣ�� �Ǹ� �����ڰ� �Լ��� ��. �� �Լ���
		�븮�ڰ� ���� �� ��������Ʈ���� �Ϸ� ����. �� �� �Լ����� ���� ��ȯ�� ���� ��Ŵ.
		�Լ����� ü������ ���� �� ����. ���� �Լ��� ��� ���� �Լ����� �˾Ƽ� ����. ��ü������ ����.
	*/

	// transform�� �������� ���ǵǾ� �ִ� �Ͱ� transform �ݺ� �Լ��� ����.
	// transform: �ݺ��ڸ� �̿��� �ݺ��� (����� �ٸ� �����̳ʿ� ����)
	//  �� ������ ����
	//vector<int> vBulletReload;

	//// vBulletReload�� _vBullet�� ���ۺ��� ������ �־���.
	//transform(_vBullet.begin(), _vBullet.end(), vBulletReload.begin(),
	//	update);

	//transform(_vBullet.begin(), _vBullet.end(), vBulletReload.begin(),
	//	[](__int64 numA)-> auto {return numA;});

	_vBullet.clear();
}

void Beam::update(void)
{
	move();
}

void Beam::render(void)
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/Object/Beam.bmp", 0.0f, 0.0f,
		412, 801, 4, 1, true, RGB(255, 0, 255));
	bullet.speed = 0.1f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

