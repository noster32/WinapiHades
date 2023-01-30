#include "Stdafx.h"
#include "scene.h"

void scene::InternalOnBegin()
{
	OnBegin();
	masterSceneOnject.InternalOnBegin();
}

void scene::InternalOnEnd()
{
	OnEnd();
	masterSceneOnject.InternalOnEnd();
}

void scene::InternalOnUpdateLoading()
{
	OnUpdateLoading();
	masterSceneOnject.InternalOnUpdateLoading();
}

void scene::InternalOnUpdate()
{
	OnUpdate();
	masterSceneOnject.InternalOnUpdate();
}

void scene::InternalOnUpdateClosing()
{
	OnUpdateClosing();
	masterSceneOnject.InternalOnUpdateClosing();
}

void scene::InternalOnRenderLoading()
{
	OnRenderLoading();
	masterSceneOnject.InternalOnRenderLoading();
}

void scene::InternalOnRender()
{
	OnRender();
	masterSceneOnject.InternalOnRender();
}

void scene::InternalOnRenderClosing()
{
	OnRenderClosing();
	masterSceneOnject.InternalOnRenderClosing();
}

bool scene::ConnectionCheck(SceneObject& obj)
{
	SceneObject* parent = &obj;
	while (parent) {
		parent = parent->GetParent();
		if (parent == &masterSceneOnject)
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


