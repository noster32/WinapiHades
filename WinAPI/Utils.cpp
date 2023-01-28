#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL
{
	float MY_UTIL::getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	float MY_UTIL::getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);

		float angle = acos(x / d);

		if (y > 0) angle = PI_2 - angle;

		return angle;
	}
}

GLfloat TextureGenerateParam::GetValue(TextureMod mod)
{
	switch (mod) {
		case TextureGenerateParam::LINEAR:
			return GL_LINEAR;
		case TextureGenerateParam::NEAREST:
			return GL_NEAREST;
	}
}

uint TextureSource::counter = 1;

void TextureSource::SetRange(Rect2D range) {
	Point2D ref(width, height);
	Point2D::Clamp(range.leftBottom, ref);
	Point2D::Clamp(range.rightTop, ref);
	this->range = range;
}

////////////////////////////////
//    struct TextureStorage   //
////////////////////////////////
void TextureStorage::Remove(uint uid) {
	map<uint, const TextureSource*>::iterator iter(textureMap.find(uid));
	if (iter != textureMap.end()) {
		delete iter->second;
		textureMap.erase(iter);
	}
}

const TextureSource& TextureStorage::Find(uint uid) {
	static TextureSource NULL_TEXTURESOURCE = TextureSource();
	map<uint, const TextureSource*>::iterator iter(textureMap.find(uid));
	if (iter != textureMap.end())
		return *(iter->second);
	else
		return NULL_TEXTURESOURCE;
}


////////////////////////////////
// struct NamedTextureStorage //
////////////////////////////////
void NamedTextureStorage::Remove(string alias) {
	map<string, uint>::iterator iter(namedMap.find(alias));
	if (iter != namedMap.end())
		namedMap.erase(iter);
}

uint NamedTextureStorage::Find(string alias) {
	map<string, uint>::iterator iter(namedMap.find(alias));
	return (iter != namedMap.end()) ? iter->second : 0;
}


