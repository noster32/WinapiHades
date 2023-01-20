#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase <SceneManager>
{
private:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT changeScene(string sceneName);

	//로딩 스레드 함수
	// LPVOID: vpid
	//friend 단방향 참조
	
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	//callback = deligate
	SceneManager() {}
	~SceneManager() {}
};

