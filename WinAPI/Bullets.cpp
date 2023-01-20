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
	//삭제를할때 댕글릭 포인터가 발생할 여지가 있고,
	//몬스터마다 총알모양이 다를 수 있기 때문에 세팅을 하면안됨
	//bullet.img = new GImage;
	//bullet.img->init("Resources/Images/Object/Missile2.bmp", 0.0f, 0.0f,
	//	416, 64, 13, 1, true, RGB(255, 0, 255));
	
	//ㄴ 추상화로 해결 가능
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

		// 사거리 밖으로 나갔다.
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//SAFE_DELETE(_viBullet->img); -> 댕글릭 포인트 발생 코드
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
		// ZeroMemory(): 첫 번째 인자가 가리키는 주소의 값을 0으로 초기화
		//  ㄴ 인자: 메모리 블록, 메모리 블록 사이즈
		// ZeroMemory는 내부적으로 memset을 호출하고 있다.
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

		// 사거리 밖으로 나갔다.
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
	// 최대 발사 갯수를 막는다.
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

		// 사거리 밖으로 나갔다.
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
	// 초기식이 밖에 있으면 델리게이트나 람다식으로 실행이 불가함. 비표준이기 때문.
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	// 현업에서는 아래와 같이 반복을 돌림.
	// 현업에서 auto는 사용하지 않음.
	/*iterBullet iterBullet = _vBullet.begin();
	for (; iterBullet != _vBullet.end(); ++iterBullet)
	{
		SAFE_DELETE(iterBullet->img);
	}*/

	// 컨테이너 기반 for문. 현업에서 많이 쓰임.
	/*for (auto iter : _vBullet)
	{
		SAFE_DELETE(iter.img);
	}*/

	// 알고리즘 함수이기에 매우 무거움.
	/*for each (auto iter in _vBullet)
	{
		SAFE_DELETE(iter.img); ▶ 정적. 시작과 끝점을 모르기에 스택 영역에 놓고 돌림.
	}*/

	// C++ 17에서 기능 확장.
	// 반복자의 시작과 끝, 함수를 파라미터로 받는다.
	// 재귀함수: 함수에서 자기 자신을 호출하는 것.
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

		- [캡처] (매개 변수) {(반환)함수 동작} (호출 인자(생략 가능))

		[] (int numA, int numB) { cout << numA + bumB << endl; } (10, 20)
		[] (int numA, int numB) { return numA + numB } (10, 20)
	*/

	/*int numberA = 10;
	int numberB = 10;

	auto resultA = [](int numA, int numB) {return numA + numB;} (10, 10);
	auto resultB = [&]()->int {return numberA + numberB;} ();
	auto resultC = [=, &numberA]()->int {return numberA + numberB;} ();*/

	/*
		[]: 같은 영역에 있는 모든 변수에 접근 불가
		[&]: 같은 영역에 있는 모든 변수를 참조로 캡처.
		[=]: 같은 영역에 있는 모든 변수를 값으로 캡처.
		[=, &변수A]: 같은 영역에 있는 모든 변수를 값으로 캡처하겠다. 단, 변수A만 참조.
	*/

	/*
		델리게이트(이벤트) > 실행자 > 대리자(핸들러)
		사용하기 위함 함수를 실행자에 등록. 델리게이트가 호출 되면 실행자가 함수를 고름. 그 함수를
		대리자가 실행 후 델리게이트에게 완료 보고. 그 후 함수들의 내용 교환을 적용 시킴.
		함수들을 체인으로 묶을 수 있음. 상위 함수만 끊어도 하위 함수들이 알아서 끊김. 객체지향의 장점.
	*/

	// transform은 엔진에서 정의되어 있는 것과 transform 반복 함수가 있음.
	// transform: 반복자를 이용한 반복문 (결과를 다른 컨테이너에 저장)
	//  ㄴ 원본도 가능
	//vector<int> vBulletReload;

	//// vBulletReload에 _vBullet의 시작부터 끝까지 넣어줌.
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

