#include "Stdafx.h"
#include "MasterSceneObject.h"

void MasterSceneObject::Render()
{
	if (!enabled) return;

	gl.PushMatrix();

	gl.TransformMasterSO(transformation);

	vector<SceneObject*>& children = GetChildrenVector();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->Render();
	}

	gl.PopMatrix();
}
