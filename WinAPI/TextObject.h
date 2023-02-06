#pragma once
#include "SceneObject.h"

class TextObject : public SceneObject
{
private:
	string text;
	bool begin;
	uint length;
	uint cursor;
	uint tickPerChar;
public:
	TextObject();
	void SetText(string text);
	inline void SetTickPerChar(uint tpc) { this->tickPerChar = tpc; }
	void Reset();
	inline void BeginDisplay() { begin = true; }
	inline void ForceEnd() { cursor = length - 1; }
	virtual void OnUpdate();
	virtual void Render();
};

