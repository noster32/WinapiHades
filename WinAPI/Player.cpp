#include "Stdafx.h"
#include "Player.h"

void Player::Init()
{
	TextureGenerateParam param(TextureGenerateParam::LINEAR, TextureGenerateParam::LINEAR);
	vector<uint> uids = gl.LoadMultipleTexturesPng("Resources/Images/Anim/Idle/ZagreusIdle_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uids), "IDLE");
	vector<uint> uidsMove = gl.LoadMultipleTexturesPng("Resources/Images/Anim/IdleMove/ZagreusRun_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsMove), "MOVE");
	vector<uint> uidsDash = gl.LoadMultipleTexturesPng("Resources/Images/Anim/Dash/ZagreusDash_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsDash), "DASH");
	vector<uint> uidsDashVfx = gl.LoadMultipleTexturesPng("Resources/Images/Anim/DashVfx/ZagreusDashVFX_Bink", ".png", 3, param);
	nts.Add(gl.BuildAnimation(uidsDashVfx), "DashVfx");

	RegisterObject(testSprite);
	RegisterObject(testAnim);
	RegisterObject(testAnimVfx);

	testAnim.SetDepth(15);
	testAnimVfx.SetDepth(16);
	testAnim.transformation.position = Vector2D(WINSIZE_X / 2, WINSIZE_Y / 2);
	//masterSceneObject.transformation.position = Vector2D(2590, 4250);
	testAnim.transformation.anchor = Anchor::CENTER;
	testAnim.transformation.scale += 0.1f;
	testAnimVfx.transformation.anchor = Anchor::CENTER;

	mPlayerStatus.insert(make_pair(IDLE, "IDLE"));
	mPlayerStatus.insert(make_pair(MOVE, "MOVE"));
	mPlayerStatus.insert(make_pair(DASH, "DASH"));
	mPlayerStatus.insert(make_pair(STOP, "STOP"));
	mPlayerStatus.insert(make_pair(ATTACK, "ATTACK"));
	mPlayerStatus.insert(make_pair(SPECIAL_ATTACK, "SPECIALATTACK"));
	mPlayerStatus.insert(make_pair(MAGIC, "MAGIC"));
	mPlayerStatus.insert(make_pair(CALL, "CALL"));
	mPlayerStatus.insert(make_pair(HIT, "HIT"));
	mPlayerStatus.insert(make_pair(DIE, "DIE"));
	mPlayerStatus.insert(make_pair(FISHING, "FISHING"));
}

void Player::OnBegin()
{
}

void Player::OnEnd()
{
}

void Player::OnUpdate()
{
	testAnim.texture = nts.Find(FindStatus(ps));

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//float tempAngle = getAngle(testAnim.transformation.position.x, testAnim.transformation.position.y, _ptMouse.x - masterSceneObject.transformation.position.x, _ptMouse.y - masterSceneObject.transformation.position.y);
		//angle = (360 - (tempAngle * 180 / PI)) / 10;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		masterSceneObject.transformation.position.x += 10;
		testAnim.transformation.position.x -= 10;
		if (KEYMANAGER->isStayKeyDown(VK_UP))
			angle = 14;
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			angle = 22;
		else
			angle = 18;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		masterSceneObject.transformation.position.x -= 10;
		testAnim.transformation.position.x += 10;
		if (KEYMANAGER->isStayKeyDown(VK_UP))
			angle = 4;
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			angle = 32;
		else
			angle = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		masterSceneObject.transformation.position.y -= 10;
		testAnim.transformation.position.y += 10;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			angle = 13;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			angle = 5;
		}
		else {
			angle = 9;
			dashAngle = 4;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {

		masterSceneObject.transformation.position.y += 10;
		testAnim.transformation.position.y -= 10;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			angle = 23;
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			angle = 31;
		else
			angle = 27;
	}
	tempPlayerStatueUpdate();
	if (ps == DASH)
	{
		testAnimVfx.texture = nts.Find("DashVfx");
		testAnimVfx.transformation.position = testAnim.transformation.position;
		//Dash 90' = 48  = 12장씩 /  4
		//Idle 90' = 240 = 24장씩 / 10
		//Move 90' = 104 = 6장씩 / 16
		tempAnimVfx.playAnimVFX(testAnimVfx, angle * animLength, animLength, animDelay, ps);
		tempAnim.playAnim(testAnim, angle * animLength, animLength, animDelay, false, ps);
	}
	else
		tempAnim.playAnim(testAnim, angle * animLength, animLength, animDelay, true, ps);
}

void Player::OnUpdateLoading()
{
}

void Player::OnUpdateClosing()
{
}

void Player::OnRenderLoading()
{
}

void Player::OnRender()
{
}

void Player::OnRenderClosing()
{
}

string Player::FindStatus(playerStatus ps)
{

	map<playerStatus, string>::iterator iter(mPlayerStatus.find(ps));
		return (iter != mPlayerStatus.end()) ? iter->second : 0;

}

void Player::tempPlayerStatueUpdate()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		ps = MOVE;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_SPACE) || tempAnim.GetAnimDashPlaying())
	{
		ps = DASH;
	}
	else
		ps = IDLE;

	switch (ps)
	{
	case IDLE:
		animLength = 24;
		animDelay = 3;
		break;
	case MOVE:
		animLength = 6;
		animDelay = 3;
		break;
	case DASH:
		animLength = 12;
		animDelay = 3;
		break;
	case STOP:
		break;
	case ATTACK:
		break;
	case SPECIAL_ATTACK:
		break;
	case MAGIC:
		break;
	case CALL:
		break;
	case HIT:
		break;
	case DIE:
		break;
	case FISHING:
		break;
	default:
		animLength = 24;
		break;
	}
}

