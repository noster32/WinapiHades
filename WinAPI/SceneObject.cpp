#include "Stdafx.h"
#include "SceneObject.h"

uint SceneObject::counter = 0;
GLAPI& SceneObject::gl = GLAPI::GetInstance();

void SceneObject::SetParent(SceneObject* parent) {
	if (this->parent)
		this->parent->RemoveChild(this);
	parent->children.push_back(this);
	this->parent = parent;
}

void SceneObject::RemoveChild(SceneObject* target) {
	vector<SceneObject*>::iterator iter;
	for(iter = children.begin(); iter != children.end(); iter++)
		if (*iter == target) {
			children.erase(iter);
			return;
		}
}

void SceneObject::SetDepth(int depth) {
	this->depth = depth;
	if (parent)
		stable_sort(parent->children.begin(), parent->children.end(), SceneObject::SOComparator);
}

void SceneObject::Render()
{
	gl.PushMatrix();

	gl.Transform(transformation);

	vector<SceneObject*>& children = GetChildrenVector();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->Render();
	}

	gl.PopMatrix();
	
}

void SceneObject::InternalOnBegin()
{
	OnBegin();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnBegin();
}

void SceneObject::InternalOnEnd()
{
	OnEnd();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnEnd();
}

void SceneObject::InternalOnUpdateLoading()
{
	if (!enabled)	return;
	OnUpdateLoading();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnUpdateLoading();
}

void SceneObject::InternalOnUpdate()
{
	if (!enabled) return;
	OnUpdate();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnUpdate();
}

void SceneObject::InternalOnUpdateClosing()
{
	if (!enabled) return;
	OnUpdateClosing();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnUpdateClosing();
}

void SceneObject::InternalOnRenderLoading()
{
	if (!enabled) return;
	OnRenderLoading();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnRenderLoading();
}

void SceneObject::InternalOnRender()
{
	if (!enabled) return;
	OnRender();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnRender();
}

void SceneObject::InternalOnRenderClosing()
{
	if (!enabled) return;
	OnRenderClosing();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InternalOnRenderClosing();
}

void SceneObject::Dispose()
{
	if (parent)
		parent->RemoveChild(this);

	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->Dispose();
	}

	disposed = true;
	enabled = false;
}
