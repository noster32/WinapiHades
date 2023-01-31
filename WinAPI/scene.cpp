#include "Stdafx.h"
#include "scene.h"

map<string, scene*> scene::sceneMap;
bool scene::swapFlag = false;
scene* scene::nextScene = NULL;

GLAPI& scene::gl = GLAPI::GetInstance();
EngineAPI& scene::engine = EngineAPI::GetInstance();

void scene::InternalOnBegin()
{
	OnBegin();
	masterSceneObject.InternalOnBegin();
}

void scene::InternalOnEnd()
{
	OnEnd();
	masterSceneObject.InternalOnEnd();
}

void scene::InternalOnUpdateLoading()
{
	OnUpdateLoading();
	masterSceneObject.InternalOnUpdateLoading();
}

void scene::InternalOnUpdate()
{
	OnUpdate();
	masterSceneObject.InternalOnUpdate();
}

void scene::InternalOnUpdateClosing()
{
	OnUpdateClosing();
	masterSceneObject.InternalOnUpdateClosing();
}

void scene::InternalOnRenderLoading()
{
	OnRenderLoading();
	masterSceneObject.InternalOnRenderLoading();
}

void scene::InternalOnRender()
{
	OnRender();
	masterSceneObject.InternalOnRender();
}

void scene::InternalOnRenderClosing()
{
	OnRenderClosing();
	masterSceneObject.InternalOnRenderClosing();
}

bool scene::ConnectionCheck(SceneObject& obj)
{
	SceneObject* parent = &obj;
	while (parent) {
		parent = parent->GetParent();
		if (parent == &masterSceneObject)
			return true;
	}
	return false;
}

string scene::RegisterReference(SceneObject& obj, string alias)
{
	map<string, SceneObject*>::iterator iter;
	for (iter = somap.begin(); iter != somap.end(); iter++)
		if (iter->second == &obj)
			return iter->first;

	string result = alias;
	iter = somap.find(result);
	while (iter != somap.end()) {
		stringstream ss;
		int inc = 2;
		ss << alias << inc;
		result = ss.str();
		inc++;
		iter = somap.find(result);
	}
	somap.insert(make_pair(result, &obj));

	return result;
}

SceneObject* scene::FindReference(string alias)
{
	map<string, SceneObject*>::const_iterator iter(somap.find(alias)); 
	return (iter != somap.end()) ? iter->second : NULL;
}

void scene::RemoveReference(string alias)
{
	map<string, SceneObject*>::iterator iter(somap.find(alias));
	if (iter != somap.end())
		somap.erase(iter);
}


