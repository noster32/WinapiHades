#pragma once
#include "scene.h"
#include "Animation.h"
#include "Player.h"

class TestScene : public scene
{
private:
	NamedTextureStorage nts;
	
	RenderObject fade;
	RenderObject bg;
	RenderObject test;
	RenderObject testCut;
	RenderObject testSprite;
	RenderObject tempMap;
	RenderObject testOrb;
	RenderObject Orb1;
	RenderObject MobSpawn;
	RenderObject enemyHitbox;
	RenderObject playerAttack;
	RenderObject playerAttack2;
	RenderObject playerHitBox;
	RenderObject UpdateInPlayer;

	Player playerObjTest;


	nFFmpeg Skelly;

	Animation tempAnim;
	Animation tempAnimVfx;
	Animation tempObjAnim;
	Animation OrbAnim;
	Animation MobSpawnAnim;
	SceneObject* animSelected;

	int frame;
	int tick, increment;
	int jump;
	bool gg;

	Rect2D test1;
	Rect2D test2;

	Rect2D playerAttackRect;
	Rect2D SkellyHitBoxRect;
	bool start;

	void MonSpawn();

	void Combat();
public:
	void Init();

	virtual void OnBegin();
	virtual void OnEnd();

	virtual void OnUpdate();
	virtual void OnUpdateLoading();
	virtual void OnUpdateClosing();

	virtual void OnRenderLoading();
	virtual void OnRender();
	virtual void OnRenderClosing();

};

