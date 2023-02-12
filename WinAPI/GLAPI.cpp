#include "Stdafx.h"
#include "GLAPI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int charWidthMid = 17;
const int charWidthBig = 33;
const int charHeight = 33;
const int charStrideMid = 15;
const int charStrideBig = 21;

void GLAPI::EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC, Point2D windowSize)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	*hDC = GetDC(hwnd);
	//*hDC = GetDC(_hWnd);
	this->hdc = hDC;

	//DC의 pixel  format설정
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	iFormat = ChoosePixelFormat(*hDC, &pfd);
	SetPixelFormat(*hDC, iFormat, &pfd);

	//렌더링 컨텍스트 Create & Enable
	*hRC = wglCreateContext(*hDC);
	wglMakeCurrent(*hDC, *hRC);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, windowSize.x, windowSize.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = (GLfloat)windowSize.x / (GLfloat)windowSize.y;
	if (windowSize.x > windowSize.y) {
		glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, 1.0, -1.0);
		this->viewportSize = Vector2D(2.0f * aspect, 2.0f);
	}
	else {
		glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, 1.0, -1.0);
		this->viewportSize = Vector2D(2.0f, 2.0f / aspect);
	}
	this->unitVertex2f = viewportSize / windowSize;
	this->centerVertex2f = viewportSize / 2.0f;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	this->windowSize = windowSize;
	this->enabled = true;
}

void GLAPI::DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc);
	ReleaseDC(hwnd, hdc);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	enabled = false;
}

uint GLAPI::GenerateEmptyTexture(int width, int height, uint RGBA)
{
	uint longer = width > height ? width : height;
	uint power = 0;
	while ((1 << power) < longer)
		power++;
	ulong length = (1 << power);
	return uint();

	unsigned char color[4];
	color[0] = (unsigned char)((RGBA >> 24) & 0xFF);
	color[1] = (unsigned char)((RGBA >> 16) & 0xFF);
	color[2] = (unsigned char)((RGBA >> 8)  & 0xFF);
	color[3] = (unsigned char)( RGBA		& 0xFF);

	ulong totalSize = length * length * 4;
	uchar* data = new uchar[totalSize];
	int repeat = length * length;
	for (int i = 0; i < repeat; i++)
		memcpy(&data[i * 4], color, sizeof(uchar) * 4);

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, length, length, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	delete data;

	TextureSource* dst = new TextureSource(id);
	dst->power = power;
	dst->length = length;
	dst->totalSize = totalSize;
	dst->width = width;
	dst->height = height;
	dst->size = width * height * 4;
	dst->coord = Vector2D((float)width / length, (float)height / length);
	dst->range.rightTop = Point2D(width, height);

	textureStorage.Add(dst);
	return dst->uid;
}

uint GLAPI::LoadTexture(string fileName, TextureGenerateParam param)
{
	FILE* file;
	fopen_s(&file,fileName.c_str(), "rb");
	if (!file)
		return 0;

	char filedef[2];
	fread(&filedef, sizeof(char), 2, file);
	if (filedef[0] != 'B' || filedef[1] != 'M')
		return 0;

	ullong filesize;
	fread(&filesize, sizeof(ullong), 1, file);

	ulong eWidth, eHeight;
	fseek(file, 18, 0);
	fread(&eWidth, sizeof(ulong), 1, file);
	fread(&eHeight, sizeof(ulong), 1, file);
	ulong eSize = eWidth * eHeight * 4;
	
	uint power = 0;
	while ((1 << power) < eWidth)
		power++;
	ulong length = (1 << power);
	ulong totalSize = length * length * 4;
	uchar* data = new uchar[totalSize];
	memset(data, 0x0, sizeof(uchar) * totalSize);

	filesize -= 54;
	ulong bytePerRow = filesize / eHeight;
	bool alphaExists = (bytePerRow == eWidth * 4);
	uchar paddingByte = alphaExists ? 0 : bytePerRow - eWidth * 3; 

fseek(file, 54, 0);
if (alphaExists) {
	for (int y = 0; y < eHeight; y++)
		fread(&data[y * length], sizeof(uchar), eWidth * 4, file);
}
else {
	uchar buffer[4];
	for (int y = 0; y < eHeight; y++)
	{
		for (int x = 0; x < eWidth; x++)
		{
			fread(buffer, sizeof(char), 3, file);
			buffer[3] = ((buffer[0] == 0xFF) && (buffer[1] == 0xFF) && (buffer[2] == 0xFF)) ? 0x00 : 0xFF;
			memcpy(&data[(y * length + x) * 4], buffer, sizeof(uchar) * 4);
		}
		fread(buffer, sizeof(char), paddingByte, file);
	}
}
fclose(file);

GLuint id;
glGenTextures(1, &id);
glBindTexture(GL_TEXTURE_2D, id);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param.GetMinFilter());
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param.GetMagFilter());
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, length, length, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
delete data;

TextureSource* dst = new TextureSource(id);
dst->power = power;
dst->length = length;
dst->totalSize = totalSize;
dst->width = eWidth;
dst->height = eHeight;
dst->size = eSize;
dst->coord = Vector2D((float)eWidth / length, (float)eHeight / length);
dst->range.rightTop = Point2D(eWidth, eHeight);

textureStorage.Add(dst);
return dst->uid;
}

uint GLAPI::LoadTextureFFmpeg(uint8_t* data, int width, int height)
{
	size_t u2 = 1; while (u2 < width) u2 *= 2;
	size_t v2 = 1; while (v2 < height) v2 *= 2;
	

	GLuint id;
	GLuint pboIds[2];
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	return id;
}

uint GLAPI::LoadPixelBufferFFmpeg(const int width, const int height)
{
	GLuint pboIds[2];
	const int DATA_SIZE = width * height * 4;
	if (openGLWindowOpen)
	{
		glGenBuffers(2, pboIds);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[0]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, DATA_SIZE, 0, GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[1]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, DATA_SIZE, 0, GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
		pixelBufferLoad = true;
	}

	return pboIds[0];
}

uint GLAPI::LoadTexturePng(string fileName, TextureGenerateParam param)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* image = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 4);

	if (!image)
		return 0;

	//POT resize
	size_t u2 = 1; while (u2 < width) u2 *= 2;
	size_t v2 = 1; while (v2 < height) v2 *= 2;

	uint powerX = log2(u2);
	uint powerY = log2(v2);
	ulong tempX = pow(2, powerX);
	ulong tempY = pow(2, powerY);
	ulong eSize = width * height * 4;
	ulong totalSize = tempX * tempY * 4;


	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param.GetMinFilter());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param.GetMagFilter());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);

	TextureSource* dst = new TextureSource(id);
	dst->texPowerOfX = powerX;
	dst->texPowerOfY = powerY;
	dst->totalSize = totalSize;
	dst->width = width;
	dst->height = height;
	dst->size = eSize;
	dst->coord = Vector2D((float)width / tempX, (float)height / tempY);
	dst->range.rightTop = Point2D(width, height);

	textureStorage.Add(dst);

	return dst->uid;
}

uint GLAPI::BuildAnimation(const vector<uint>& uids)
{
	if (uids.empty()) return 0; // empty
	const TextureSource& ref = textureStorage.Find(uids.at(0));
	return BuildAnimation(uids, ref.range);
}

uint GLAPI::BuildAnimation(const vector<uint>& uids, const Rect2D& range)
{
	if (uids.empty()) return 0;
	vector<GLuint> tids;
	vector<uint>::const_iterator iter;
	for (iter = uids.begin(); iter != uids.end(); iter++)
	{
		const TextureSource& ref = textureStorage.Find(*iter);
		tids.push_back(ref.Get(0));
	}
	AnimatedTexture* anim = new AnimatedTexture(tids);
	const TextureSource& ref = textureStorage.Find(uids.at(0));
	anim->texPowerOfX = ref.texPowerOfX;
	anim->texPowerOfY = ref.texPowerOfY;
	anim->width = ref.width;
	anim->height = ref.height;
	anim->SetRange(range);
	textureStorage.Add(anim);
	//animationtexture가 textureSource를 상속받기때문에 tids에있는 코드를 돌림
	return anim->uid;
}

uint GLAPI::BuildAnimationBySprite(uint uid, int width, int height)
{
	vector<GLuint> tids;
	const TextureSource& ref = textureStorage.Find(uid);
	int tempWidthNum = ref.width / width;
	int tempHeightNum = ref.height / height;
	for (int y = 0; y < tempHeightNum; y++)
	{
		for (int x = 0; x < tempWidthNum; x++)
		{
			tids.push_back(ref.Get(0) + ((y * tempWidthNum) + x));
		}
	}
	AnimatedTexture* anim = new AnimatedTexture(tids);
	anim->power = ref.power;
	anim->width = ref.width;
	anim->height = ref.height;
	//anim->SetRange(Rect2D(Point2D(x * width, ), Point2D()));
	return uint();
}

uint GLAPI::CutTexture(const uint uid, const Rect2D& range)
{
	const TextureSource& ref = textureStorage.Find(uid);
	if (!ref.tid) return 0;
	TextureSource* tex = new TextureSource(ref.tid);
	tex->texPowerOfX = ref.texPowerOfX;
	tex->texPowerOfY = ref.texPowerOfY;
	tex->width = ref.width;
	tex->height = ref.height;
	tex->SetRange(range);
	textureStorage.Add(tex);

	return tex->uid;
}
//프레임 데이터 -> 픽셀 버퍼 오브젝트 -> 렌더링
void GLAPI::ClearTexture(const uint uid, const uint RGBA)
{
	const TextureSource& ref = textureStorage.Find(uid);
	if (!ref.tid) return;
	
	uchar color[4];
	color[0] = (uchar)((RGBA >> 24) & 0xFF);
	color[1] = (uchar)((RGBA >> 16) & 0xFF);
	color[2] = (uchar)((RGBA >> 8)  & 0xFF);
	color[3] = (uchar)(RGBA			& 0xFF);

	int rep = ref.width * ref.height;
	uchar* data = new uchar[ref.size];
	memset(data, 0x0, ref.size);
	for (int i = 0; i < rep; i++)
		memcpy(&data[i * 4], color, sizeof(uchar) * 4);

	glBindTexture(GL_TEXTURE_2D, ref.tid); 
	//texture update;
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ref.width, ref.height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	delete data;
	
}

vector<uint> GLAPI::LoadMultipleTextures(string prefix, string suffix, uint digit, TextureGenerateParam param)
{
	int index = 1;
	stringstream ss;
	stringstream len;
	vector<uint> uids;

	while (1) {
		ss.str(string());
		len.str(string());

		ss << prefix;
		len << index;
		int zeros = digit - len.str().length();
		for (int i = 0; i < zeros; i++)
			ss << "0";
		ss << index << suffix;
		uint uid = LoadTexture(ss.str(), param);
		if (!uid)
			break;
		uids.push_back(uid);
		index++;
	}

	return uids;
}

vector<uint> GLAPI::LoadMultipleTexturesPng(string prefix, string suffix, uint digit, TextureGenerateParam param)
{
	int index = 0;
	stringstream ss;
	stringstream len;
	vector<uint> uids;

	while (1) {
		ss.str(string());
		len.str(string());

		ss << prefix;
		len << index;
		int zeros = digit - len.str().length();
		for (int i = 0; i < zeros; i++)
			ss << "0";
		ss << index << suffix;
		uint uid = LoadTexturePng(ss.str(), param);
		if (!uid)
			break;
		uids.push_back(uid);
		index++;
	}

	return uids;
}

void GLAPI::Transform(const Transformation& tf)
{
	Vector2D pos = PxCoordToVertex2f(tf.position.VecToPoint());
	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(tf.rotate.getDegree(), 0.0f, 0.0f, 1.0f);
	glScalef(tf.scale.x, tf.scale.y, 1.0f);
}

void GLAPI::TransformMasterSO(const Transformation& tf)
{
	Vector2D ac = centerVertex2f;
	switch(tf.anchor.Get()) {
		case Anchor::LEFT_BOTTOM:
			ac *= -1.0f;
			break;
		case Anchor::RIGHT_BOTTOM:
			ac.x *= -1;
			break;
		case Anchor::LEFT_TOP:
			ac.y *= -1;
			break;
		case Anchor::RIGHT_TOP:
			break;
		case Anchor::CENTER:
			ac = Vector2D();
			break;
	}

	Transform(tf);
	glTranslatef(ac.x, ac.y, 0.0f);
}

void GLAPI::DrawTextureAuto(const Transformation& tf, const uint uid, const ullong frame, const Point2D size)
{
	const TextureSource& ref = textureStorage.Find(uid);

	Point2D rtPx = size;
	Point2D texSize = Point2D(ref.range.rightTop) - ref.range.leftBottom;
	if (size.x == 0)
		rtPx.x = texSize.x;
	if (size.y == 0)
		rtPx.y = texSize.y;

	Vector2D lbVer, rtVer;
	rtVer = PxCoordToVertex2f(rtPx);
	lbVer = rtVer / -2.0f;
	rtVer = rtVer / 2.0f;

	float leftTex = PxCoordToTexCoord2fTest(ref.range.leftBottom.x, ref.width);
	float rightTex = PxCoordToTexCoord2fTest(ref.range.rightTop.x, ref.width);
	float bottomTex = PxCoordToTexCoord2fTest(ref.range.leftBottom.y, ref.height);
	float topTex = PxCoordToTexCoord2fTest(ref.range.rightTop.y, ref.height);
	
	Vector2D ac = rtVer;
	switch (tf.anchor.Get()) {
	case Anchor::LEFT_BOTTOM:
		break;
	case Anchor::RIGHT_BOTTOM:
		ac.x *= -1;
		break;
	case Anchor::LEFT_TOP:
		ac.y += -1;
		break;
	case Anchor::RIGHT_TOP:
		ac.x *= -1;
		ac.y *= -1;
		break;
	case Anchor::CENTER:
		ac = Vector2D();
		break;
	}
	
	GLuint tid = ref.Get(frame);

	Transform(tf);

	glPushMatrix();
	glTranslatef(ac.x, ac.y, 0.0f);
	DrawQuadTexture(lbVer.x, lbVer.y, rtVer.x, rtVer.y, leftTex, bottomTex, rightTex, topTex, tid);
	glPopMatrix();

}

void GLAPI::LoadCharacterSet()
{
	const char* FILENAME = "./data/characterset/characterset.bmp";

	// Open file
	FILE* file;
	fopen_s(&file,FILENAME, "rb");
	if (!file)
		return;

	// Read BMP File Descriptor
	char filedef[2];
	fread(&filedef, sizeof(char), 2, file);
	if (filedef[0] != 'B' || filedef[1] != 'M')
		return;

	// Get Filesize
	ullong filesize;
	fread(&filesize, sizeof(ullong), 1, file);

	// Get Effective Width, Height, Size
	ulong eWidth, eHeight;
	fseek(file, 18, 0);
	fread(&eWidth, sizeof(ulong), 1, file);
	fread(&eHeight, sizeof(ulong), 1, file);
	ulong eSize = eWidth * eHeight * 4;

	// Calculate Total Size and Allocate Memory
	uint power = 0;
	while ((1 << power) < eWidth)
		power++;
	ulong length = (1 << power);
	ulong totalSize = length * length * 4;
	uchar* data = new uchar[totalSize];
	memset(data, 0x0, sizeof(uchar) * totalSize);

	// Check File Cotains Alpha Channel
	filesize -= 54;
	ulong bytePerRow = filesize / eHeight;
	bool alphaExists = (bytePerRow == eWidth * 4);
	uchar paddingByte = alphaExists ? 0 : bytePerRow - eWidth * 3;

	// Copy Data to memory
	fseek(file, 54, 0);
	if (alphaExists) {
		// Alpha Channel Exists
		for (int y = 0; y < eHeight; y++)
			fread(&data[y * length], sizeof(uchar), eWidth * 4, file);
	}
	else {
		// Alpha Channel Not Exists
		uchar buffer[4];
		uchar med;
		for (int y = 0; y < eHeight; y++) {
			for (int x = 0; x < eWidth; x++) {
				fread(buffer, sizeof(char), 3, file);
				med = (buffer[0] + buffer[1] + buffer[2]) / 3;
				buffer[0] = med;
				buffer[1] = med;
				buffer[2] = med;
				buffer[3] = 0xFF - med;
				//buffer[3] = ((buffer[0] == 0xFF) && (buffer[1] == 0xFF) && (buffer[2] == 0xFF)) ? 0x00 : 0xFF;
				memcpy(&data[(y * length + x) * 4], buffer, sizeof(uchar) * 4);
			}
			fread(buffer, sizeof(char), paddingByte, file);
		}
	}
	fclose(file);

	// Create Texture
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, length, length, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
	delete data;

	// Build TextureSource
	TextureSource* dst = new TextureSource(id);
	dst->power = power;
	dst->length = length;
	dst->totalSize = totalSize;
	dst->width = eWidth;
	dst->height = eHeight;
	dst->size = eSize;
	dst->coord = Vector2D((float)eWidth / length, (float)eHeight / length);
	dst->range.rightTop = Point2D(eWidth, eHeight);

	// Add Texture to reference map
	textureStorage.Add(dst);
	charset = dst->uid;
}

void GLAPI::DrawString(const Transformation& tf, const string str, const int count)
{
	const TextureSource& ref = textureStorage.Find(charset);

	// Draw Character
	uchar msb, lsb;
	int stride = 0;
	int linebreak = 0;
	for (int i = 0; i <= count; i++) {
		// Get character
		msb = str.at(i);

		if (msb == '\n') {
			// Linebreak
			linebreak++;
			stride = 0;
			continue;
		}
		else if (msb == ' ') {
			// Spacing Char
			stride += charStrideMid;
			continue;
		}

		if ((msb & 0x80) == 0x80) {
			// Read one more byte for unicode
			lsb = str.at(i + 1);
			i++;
		}
		else {
			lsb = 0x0;
		}

		// Validate
		if (!ValidateChar(msb, lsb))
			continue;

		// Get Char Tex Coord
		Vector2D lbTex, rtTex;
		FindCharTexCoord(msb, lsb, lbTex, rtTex);

		// Get Vertex Coord
		Vector2D lbVer, rtVer;
		bool thin = (msb < 0x80) || (msb == 0xA3);
		Point2D shift(stride, -linebreak * charHeight);
		lbVer = PxCoordToVertex2f(Point2D(0, -charHeight) + shift);
		rtVer = PxCoordToVertex2f(Point2D(charWidthBig, 0) + shift);

		// Draw Texture
		DrawQuadTexture(lbVer.x, lbVer.y, rtVer.x, rtVer.y, lbTex.x, lbTex.y, rtTex.x, rtTex.y, ref.tid);

		// Update Shift
		stride += thin ? charStrideMid : charStrideBig;
	}
}

void GLAPI::DrawQuadTexture(const float x1, const float y1, const float x2, const float y2,
	const float tex_x1, const float tex_y1, const float tex_x2, const float tex_y2, const GLuint tid)
{
	if (tid == 0)   return; // ignore null texture
	glBindTexture(GL_TEXTURE_2D, tid);
	glBegin(GL_POLYGON);
	glTexCoord2d(tex_x1, tex_y1); glVertex2f(x1, y1);
	glTexCoord2d(tex_x2, tex_y1); glVertex2f(x2, y1);
	glTexCoord2d(tex_x2, tex_y2); glVertex2f(x2, y2);
	glTexCoord2d(tex_x1, tex_y2); glVertex2f(x1, y2);
	glEnd();
}

void GLAPI::DrawVideoTexture(const Transformation& tf, uint width, uint height, const uint id)
{

	Point2D rtPx;
	Point2D texSize = Point2D(width, height);
	rtPx = texSize;

	Vector2D lbVer, rtVer;
	rtVer = PxCoordToVertex2f(rtPx);
	lbVer = rtVer / -2.0f;
	rtVer = rtVer / 2.0f;

	float leftTex = PxCoordToTexCoord2fTest(0, width);
	float rightTex = PxCoordToTexCoord2fTest(width, width);
	float bottomTex = PxCoordToTexCoord2fTest(0, height);
	float topTex = PxCoordToTexCoord2fTest(height, height);

	Vector2D ac = rtVer;
	switch (tf.anchor.Get()) {
	case Anchor::LEFT_BOTTOM:
		break;
	case Anchor::RIGHT_BOTTOM:
		ac.x *= -1;
		break;
	case Anchor::LEFT_TOP:
		ac.y += -1;
		break;
	case Anchor::RIGHT_TOP:
		ac.x *= -1;
		ac.y *= -1;
		break;
	case Anchor::CENTER:
		ac = Vector2D();
		break;
	}

	Transform(tf);

	glPushMatrix();
	glTranslatef(ac.x, ac.y, 0.0f);
	DrawQuadVideoTexture(lbVer.x, lbVer.y, rtVer.x, rtVer.y, leftTex, bottomTex, rightTex, topTex, id);
	glPopMatrix();
}

void GLAPI::DrawQuadVideoTexture(const float x1, const float y1, const float x2, const float y2, const float tex_x1, const float tex_y1, const float tex_x2, const float tex_y2, const GLuint tid)
{
	if (tid == 0)   return; // ignore null texture
	glBindTexture(GL_TEXTURE_2D, tid);
	glBegin(GL_POLYGON);
	glTexCoord2d(tex_x1, tex_y1); glVertex2f(x1, y2);
	glTexCoord2d(tex_x2, tex_y1); glVertex2f(x2, y2);
	glTexCoord2d(tex_x2, tex_y2); glVertex2f(x2, y1);
	glTexCoord2d(tex_x1, tex_y2); glVertex2f(x1, y1);
	glEnd();
}

void GLAPI::DrawVideoBuffer(uint width, uint height, const uint id, const uint pboIds)
{
	static int index = 0;
	int nextIndex = 0;
	double dataSize = width * height * 4;
	index = nextIndex = 0;

	t1.start();

	glBindTexture(GL_TEXTURE_2D, id);
	glBindTexture(GL_PIXEL_UNPACK_BUFFER, pboIds);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	t1.stop();
	//copyTime = t1.getElapsedTimeInMilliSec();

	t1.start();
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, dataSize, 0, GL_STREAM_DRAW);
	GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
	if (ptr)
	{
		//updatePixel;
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	}

	t1.stop();

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER | GL_STENCIL_BUFFER_BIT);
}



Vector2D GLAPI::PxCoordToVertex2f(const Point2D& pixel)
{
	Vector2D ver(pixel);
	ver *= unitVertex2f;

	return ver;
}

Vector2D GLAPI::PxCoordToTexCoord2f(const Point2D& pixel, const uchar power)
{
	Vector2D tex(pixel);
	tex /= (1 << power);
	return tex;
}

float GLAPI::PxCoordToTexCoord2fTest(const uint coord, const uint power)
{
	float tex = coord;
	//tex /= (1 << power);
	tex /= power;
	return tex;
}

bool GLAPI::ValidateChar(const uint msb, const uint lsb)
{
	if ((msb & 0x00) == 0x0) {
		return (0x21 <= msb) && (msb <= 0x7E);
	}

	if (msb < 0xA1 || msb > 0xC8 || ((msb > 0xA4) && (msb < 0xB0)))
		return false;

	if (lsb < 0xA1 || lsb == 0xFF)
		return false;
	else if (msb == 0xA4 && lsb > 0xD4)
		return false;

	return true;
}

void GLAPI::FindCharTexCoord(uint msb, uint lsb, Vector2D& lbTex, Vector2D& rtTex)
{
	bool isAscii = false;
	int row;
	if (msb < 0x80) {
		// ASCII
		row = 0;
		lsb = msb + 0x80;
		isAscii = true;
	}
	else if (msb == 0xA1) {
		// Special Char #1
		row = 27;
	}
	else if (msb == 0xA2) {
		// Special Char #2
		row = 28;
	}
	else if (msb == 0xA3) {
		// Also Unicode ASCII
		row = 0;
		isAscii = true;
	}
	else if (msb == 0xA4) {
		// Single KR Char
		row = 1;
	}
	else if (0xB0 <= msb && msb <= 0xC8) {
		// Combined KR Char
		row = msb - 0xB0 + 2;
	}
	else {
		// Not Found
		row = -1;
	}

	// Charset Info
	const TextureSource& ref = textureStorage.Find(charset);

	// Texture Position Calculation
	Point2D charSetPos(lsb - 0xA1, row);
	Point2D lbpx, rtpx;
	if (isAscii) {
		lbpx = Point2D(charSetPos.x * charWidthBig, ref.height - (charSetPos.y + 1) * charHeight);
		rtpx = Point2D((charSetPos.x + 1) * charWidthBig, ref.height - charSetPos.y * charHeight);
	}
	else {
		lbpx = Point2D(charSetPos.x * charWidthBig, ref.height - (charSetPos.y + 1) * charHeight);
		rtpx = Point2D((charSetPos.x + 1) * charWidthBig, ref.height - charSetPos.y * charHeight);
	}
	lbTex = PxCoordToTexCoord2f(lbpx, ref.power);
	rtTex = PxCoordToTexCoord2f(rtpx, ref.power);
}
