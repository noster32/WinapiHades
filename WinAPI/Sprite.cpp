#include "Stdafx.h"
#include "Sprite.h"

void DeathAreaSprite::textureInit(void)
{
    
    da_Texture_TileTexture53.insert(make_pair("light", Rect2D(Point2D(0, 1766), Point2D(375, 0))));
    da_Texture_TileTexture53.insert(make_pair("TreeLeaves", Rect2D(Point2D(375, 1791), Point2D(773, 0))));
    da_Texture_TileTexture53.insert(make_pair("Pillor1", Rect2D(Point2D(773, 1473), Point2D(958, 0))));
    da_Texture_TileTexture53.insert(make_pair("drawer1", Rect2D(Point2D(958, 1637), Point2D(1152, 0))));
    da_Texture_TileTexture53.insert(make_pair("cerberusFoodDish", Rect2D(Point2D(958, 1483), Point2D(1112, 1636))));
    da_Texture_TileTexture53.insert(make_pair("drawerSha", Rect2D(Point2D(1152, 1751), Point2D(1416, 0))));
    da_Texture_TileTexture53.insert(make_pair("Box", Rect2D(Point2D(1417, 1765), Point2D(1688, 0))));
    da_Texture_TileTexture53.insert(make_pair("PaperDrawer", Rect2D(Point2D(1689, 1770), Point2D(1876, 0))));
    da_Texture_TileTexture53.insert(make_pair("SkullStatue", Rect2D(Point2D(1877, 1786), Point2D(2008, 0))));
    da_Texture_TileTexture53.insert(make_pair("statueBlue", Rect2D(Point2D(1113, 1323), Point2D(1372, 1635))));
    da_Texture_TileTexture53.insert(make_pair("pic", Rect2D(Point2D(1373, 1372), Point2D(1626, 1750))));
    da_Texture_TileTexture53.insert(make_pair("candle", Rect2D(Point2D(1627, 1396), Point2D(1810, 1764))));
    da_Texture_TileTexture53.insert(make_pair("drawer2", Rect2D(Point2D(1813, 1447), Point2D(2044, 1769))));
    da_Texture_TileTexture53.insert(make_pair("cerberusPic", Rect2D(Point2D(0, 940), Point2D(229, 1381))));
    da_Texture_TileTexture53.insert(make_pair("SkullStatue", Rect2D(Point2D(1877, 1786), Point2D(2008, 0))));
}

Rect2D DeathAreaSprite::findTexture(string texName)
{
    map<string, Rect2D>::iterator iter(da_Texture_TileTexture53.find(texName));
    return (iter != da_Texture_TileTexture53.end()) ? iter->second : Rect2D(Point2D(0,0), Point2D(0,0));
}

