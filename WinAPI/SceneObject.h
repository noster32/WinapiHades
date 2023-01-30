#pragma once
#include "GLAPI.h"

class SceneObject : public IDisposable, public IUpdatable
{
protected:
	static bool SOComparator(const SceneObject* s1, const SceneObject* s2) {
		return s1->depth < s2->depth; 
	}
private:
	static uint counter;

protected:
	static GLAPI& gl;

public:
	const uint id;
	bool enabled;
	bool tickUpdate;
	Transformation transformation;
	ullong tick;
	string alias;

protected:
	SceneObject* parent;
	vector<SceneObject*> children;
	int depth;

public:
	SceneObject() : id(counter++), enabled(true), tickUpdate(true), transformation(), depth(0), parent(NULL) { }
	virtual ~SceneObject() { Dispose(); }
	
	SceneObject* GetParent() { return parent; }
	vector<SceneObject*>& GetChildrenVector() { return children; }
	void SetParent(SceneObject* parent);
	void RemoveChild(SceneObject* target);
	void SetDepth(int depth);
	int GetDepth() const { return depth; }

	virtual void Render();

	void InternalOnBegin();
	void InternalOnEnd();
	void InternalOnUpdateLoading();
	void InternalOnUpdate();
	void InternalOnUpdateClosing();
	void InternalOnRenderLoading();
	void InternalOnRender();
	void InternalOnRenderClosing();

	virtual void Dispose();
};

