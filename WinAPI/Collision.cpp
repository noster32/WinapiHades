#include "Stdafx.h"
#include "ShootingScene.h"

void ShootingScene::collision(void)
{
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(),40,30)))
				//&_em->getMinion()[j]->getRect()))
			{
				_rocket->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getBeam()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getBeam()->getBullet()[i].rc,
				&CollisionAreaResizing(_em->getMinion()[j]->getRect(), 40, 30)))
				//&_em->getMinion()[j]->getRect()))
			{
				_em->removeMinion(j);
				break;
			}
		}
	}
}


