#pragma once

class DeathAreaSprite
{
private:
public:
	static DeathAreaSprite& GetInstance() {
		static DeathAreaSprite instance;
		return instance;
	}
	void textureInit(void);
	Rect2D findTexture(string texName);


	map<string, Rect2D> da_Texture;
};

