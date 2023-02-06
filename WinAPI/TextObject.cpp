#include "Stdafx.h"
#include "TextObject.h"

TextObject::TextObject() : SceneObject() 
{
	this->tickPerChar = 1;
	SetText(" ");
}

void TextObject::SetText(string text)
{
	this->text = text;
	this->length = strlen(text.c_str());
	Reset();
}

void TextObject::Reset()
{
	begin = false;
	cursor = 0;
	tick = 0;
}

void TextObject::OnUpdate()
{
	if (begin) {
		
	}
}

void TextObject::Render()
{
}
