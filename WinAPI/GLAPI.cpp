#include "Stdafx.h"
#include "GLAPI.h"

const int charWidthMid = 17;
const int charWidthBig = 33;
const int charHeight = 33;
const int charStrideMid = 15;
const int charStrideBig = 21;

void GLAPI::EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hrc, Point2D windowSize)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	*hDC = GetDC(hwnd);
	this->hdc = hDC;

	ZeroMemory(&pfd, sizeof(pfd));

}

void GLAPI::DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc)
{
}

uint GLAPI::GenerateEmptyTexture(int width, int height, uint RGBA)
{
	return uint();
}

uint GLAPI::LoadTexture(string fileName, TextureGenerateParam param)
{
	return uint();
}

uint GLAPI::BuildAnimation(const vector<uint>& uids)
{
	return uint();
}

uint GLAPI::BuildAnimation(const vector<uint>& uids, const Rect2D& range)
{
	return uint();
}

uint GLAPI::CutTexture(const uint uid, const Rect2D& range)
{
	return uint();
}

void GLAPI::ClearTexture(const uint uid, const uint RGBA)
{
}

vector<uint> GLAPI::LoadMultipleTextures(string prefix, string suffix, uint digit, TextureGenerateParam param)
{
	return vector<uint>();
}

void GLAPI::Transform(const Transformation& tf)
{
}

void GLAPI::TransformMasterSO(const Transformation& tf)
{
}

void GLAPI::DrawTextureAuto(const Transformation& tf, const uint uid, const ullong frame, const Point2D size)
{
}

void GLAPI::LoadCharacterSet()
{
}

void GLAPI::DrawString(const Transformation& tf, const string str, const int count)
{
}

void GLAPI::DrawQuadTexture(const float x1, const float y1, const float x2, const float y2, const float tex_x1, const float tex_y1, const float tex_x2, const float tex_y2, const GLuint tid)
{
}

Vector2D GLAPI::PxCoordToVertex2f(const Point2D& pixel)
{
	return Vector2D();
}

Vector2D GLAPI::PxCoordToTexCoord2f(const Point2D& pixel, const uchar power)
{
	return Vector2D();
}

bool GLAPI::ValidateChar(const uint msb, const uint lsb)
{
	return false;
}

void GLAPI::FindCharTexCoord(uint msb, uint lsb, Vector2D& lbTex, Vector2D& rtTex)
{
}
