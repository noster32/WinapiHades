#pragma once
#include "RenderObject.h"
#include "nFFmpeg.h"
#include "Player.h"
#include "Engineapi.h"
#include "MasterSceneObject.h"

class scene : public IUpdatable
{
protected:
	static map<string, scene*> sceneMap;
	static bool swapFlag;
	static scene* nextScene;

	static void AddSceneToMap(scene* scene, string alias) { sceneMap.insert(make_pair(alias, scene)); }
	static scene* GetScene(string alias) {
		map<string, scene*>::iterator iter(sceneMap.find(alias));
		return (iter != sceneMap.end()) ? iter->second : NULL;
	}
	static void QueueSceneSwap(string alias) {
		scene* next = GetScene(alias);
		if (next == NULL) return;
		swapFlag = true;
		nextScene = next;
	}

	static GLAPI& gl;
	static EngineAPI& engine;
public:
	static bool GetSwapFlag() { return swapFlag; }
	static scene* GetNextScene() { return nextScene; }
	static void ResetSwapFlag() { swapFlag = false; }


public:
	enum SceneState {
		BEGIN,
		LOADING,
		UPDATE,
		CLOSING,
		END
	};
protected:
	SceneState state;
	Transformation& transformation;
	MasterSceneObject masterSceneObject;
	map<string, SceneObject*> somap;

public:
	scene() : state(BEGIN), transformation(masterSceneObject.transformation) { }

	SceneState GetSceneState() { return state; }
	void SetSceneState(SceneState _state) { state = _state;  }
	void SceneEndOfLoading() { state = UPDATE; }
	void SceneEndOfUpdate() { state = CLOSING; }
	void SceneEndOfClosing() { state = END; }

	void InternalOnBegin();
	void InternalOnEnd();
	void InternalOnUpdateLoading();
	void InternalOnUpdate();
	void InternalOnUpdateClosing(); 
	void InternalOnRenderLoading();
	void InternalOnRender();
	void InternalOnRenderClosing();

protected:
	void RegisterObject(SceneObject& obj) { obj.SetParent(&masterSceneObject); }
	void RegisterObject(SceneObject& obj, SceneObject& parent) { obj.SetParent(&parent); }

	string RegisterReference(SceneObject& obj, string alias);
	SceneObject* FindReference(string alias);
	void RemoveReference(string alias);

	bool ConnectionCheck(SceneObject& obj);

};

