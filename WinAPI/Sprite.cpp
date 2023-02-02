#include "Stdafx.h"
#include "Sprite.h"

void DeathAreaSprite::textureInit(void)
{
    da_Texture.insert(make_pair("cerberusPic", Rect2D(Point2D(0, 940), Point2D(229, 1381))));
}

Rect2D DeathAreaSprite::findTexture(string texName)
{
    map<string, Rect2D>::iterator iter(da_Texture.find(texName));
    return (iter != da_Texture.end()) ? iter->second : Rect2D(Point2D(0,0), Point2D(0,0));
}

