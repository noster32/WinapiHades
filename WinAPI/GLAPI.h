#pragma once


class GLAPI
{
private:
	
	HDC* hdc;
	bool enabled;

	TextureStorage textureStorage;
	Point2D windowSize;
	Vector2D viewportSize;
	Vector2D unitVertex2f;
	Vector2D centerVertex2f;

	uint charset;


public:
	static GLAPI& GetInstance() {
		static GLAPI instance;
		return instance;
	}

	bool GetSuccess() { return enabled; }

	void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC, Point2D windowSize);
	void DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc);

	void EnableFreeType();

	Point2D GetWindowSize() { return windowSize; }

	uint GenerateEmptyTexture(int width, int height, uint RGBA);
	uint LoadTexturePng(string fileName, TextureGenerateParam param);
	uint LoadTexturePngAnim(string fileName, TextureGenerateParam param, uint animWidth, uint animheight);
	uint LoadTextureFFmpeg(uint8_t* data, int width, int height);
	uint LoadPixelBufferFFmpeg(const int width, const int height);
	uint BuildAnimation(const vector<uint>& uids);
	uint BuildAnimation(const vector<uint>& uids, const Rect2D& range);
	uint BuildAnimationBySprite(uint uid);
	uint BuildText(string text);
	uint CutTexture(const uint uid, const Rect2D& range);
	void ClearTexture(const uint uid, const uint RGBA);
	
	vector<uint> LoadMultipleTexturesPng(string prefix, string suffix, uint digit, TextureGenerateParam param);
	const TextureSource& GetTextureInformation(const uint uid) { return textureStorage.Find(uid); }

	void ClearBuffer() { glClear(GL_COLOR_BUFFER_BIT); }
	void SwapBuffer() { SwapBuffers(*hdc); }
	void PushMatrix() { glPushMatrix(); }
	void PopMatrix() { glPopMatrix(); }
	void LoadIdentity() { glLoadIdentity(); }

	void Transform(const Transformation& tf);
	void TransformMasterSO(const Transformation& tf);
	void DrawTextureAuto(const Transformation& tf, const uint uid, const ullong frame, const Point2D size);

	void LoadFreeType();
	void LoadCharacterSet();
	void DrawString(const Transformation& tf, const string str, const int count);

	void DrawQuadTexture(const float x1, const float y1, const float x2, const float y2,
						const float tex_x1, const float tex_y1, const float tex_x2, const float tex_y2, const GLuint tid);
	void DrawVideoTexture(const Transformation& tf, uint width, uint height, const uint id);
	void DrawQuadVideoTexture(const float x1, const float y1, const float x2, const float y2,
		const float tex_x1, const float tex_y1, const float tex_x2, const float tex_y2, const GLuint tid);
	void DrawVideoBuffer(uint width, uint height, const uint id, const uint pboIds);
protected:
	Vector2D PxCoordToVertex2f(const Point2D& pixel);
	Vector2D PxCoordToTexCoord2f(const Point2D& pixel, const uchar power);
	float PxCoordToTexCoord2fTest(const uint coord, const uint power);

	bool ValidateChar(const uint msb, const uint lsb);
	void FindCharTexCoord(uint msb, uint lsb, Vector2D& lbTex, Vector2D& rtTex);
	
private:
	GLAPI() : enabled(false) { };
};

