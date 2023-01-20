#pragma once
#include "SingletonBase.h"

class MapManager : public SingletonBase <MapManager>
{
public: 
	HRESULT init(void);
	void update(void);
	void render(void);
};

