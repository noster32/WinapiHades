#pragma once
//========================================================
// # Utils (간소화 하고 싶거나 or 수학적 기능을 모아둔다.)
//========================================================

#define DEG_TO_RAD		0.017453f
#define PI				3.141592654f
#define PI_2			6.283185308f
#define FLOAT_EPSILON	0.0001f
#define FLOAT_TO_INT(f1)		static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2)	(fabs(f1 - f2) <= FLOAT_EPSILON)
#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )
#define CLAMP(x, upper, lower) (MIN(upper, MAX(x, lower)))


typedef unsigned char		uchar;
typedef unsigned int		uint;
typedef unsigned long		ulong;
typedef unsigned long long ullong;


namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);
	float getAngle(float startX, float startY, float endX, float endY);
}

struct Point2D {
	int x, y;

	Point2D() : x(0.0f), y(0.0f) {}
	Point2D(int x, int y) : x(x), y(y) {}

	inline Point2D operator + (const Point2D& p2) const { return Point2D(x + p2.x, y + p2.y); }
	inline Point2D operator - (const Point2D& p2) const { return Point2D(x - p2.x, y - p2.y); }
	inline Point2D operator * (const Point2D& p2) const { return Point2D(x * p2.x, y * p2.y); }
	inline Point2D operator / (const Point2D& p2) const { return Point2D(x / p2.x, y / p2.y); }
	inline Point2D operator + (const int t) const { return Point2D(x + t, y + t); }
	inline Point2D operator - (const int t) const { return Point2D(x - t, y - t); }
	inline Point2D operator * (const int t) const { return Point2D(x * t, y * t); }
	inline Point2D operator / (const int t) const { return Point2D(x / t, y / t); }

	void operator += (const Point2D& p2) { x += p2.x; y += p2.y; }
	void operator -= (const Point2D& p2) { x -= p2.x; y -= p2.y; }
	void operator *= (const Point2D& p2) { x *= p2.x; y *= p2.y; }
	void operator /= (const Point2D& p2) { x /= p2.x; y /= p2.y; }

	bool operator > (const Point2D& p2) const { return x > p2.x && y > p2.y; }
	bool operator < (const Point2D& p2) const { return x < p2.x && y < p2.y; }
	bool operator >= (const Point2D& p2) const { return x >= p2.x && y >= p2.y; }
	bool operator <= (const Point2D& p2) const { return x <= p2.x && y <= p2.y; }
	bool operator == (const Point2D& p2) const { return x == p2.x && y == p2.y; }
	bool operator != (const Point2D& p2) const { return x != p2.x || y != p2.y; }


	float magnitude() const	{ return sqrtf(x * x + y * y); }
	float distance(const Point2D& p2) const { return sqrtf(powf(p2.x - x, 2.0f) + powf(p2.y - y, 2.0f)); }

	float getAngle(const Point2D& p2) const
	{
		float tempX = p2.x - x;
		float tempY = p2.y - y;
		float d = sqrt(tempX * tempX + tempY * tempY);
		float angle = acos(tempX / d);

		if (tempY > 0) angle = PI_2 - angle;

		return angle;
	}

	static void Clamp(Point2D& src, const Point2D& ref) {
		if (src.x > ref.x) src.x = ref.x;
		if (src.y > ref.y) src.y = ref.y;
	}
};

struct Vector2D {
	float x, y;

	Vector2D() : x(0.0f), y(0.0f) { }
	Vector2D(Point2D p) : x(p.x), y(p.y) { }
	Vector2D(float x, float y) : x(x), y(y) { }
	inline Point2D VecToPoint() const { return Point2D((int)x, (int)y); }

	inline Vector2D operator + (const Vector2D& v2) const { return Vector2D(x + v2.x, y + v2.y); }
	inline Vector2D operator - (const Vector2D& v2) const { return Vector2D(x - v2.x, y - v2.y); }
	inline Vector2D operator * (const Vector2D& v2) const { return Vector2D(x * v2.x, y * v2.y); }
	inline Vector2D operator / (const Vector2D& v2) const { return Vector2D(x / v2.x, y / v2.y); }
	inline Vector2D operator + (const float f) const { return Vector2D(x + f, y + f); }
	inline Vector2D operator - (const float f) const { return Vector2D(x - f, y - f); }
	inline Vector2D operator * (const float f) const { return Vector2D(x * f, y * f); }
	inline Vector2D operator / (const float f) const { return Vector2D(x / f, y / f); }
	inline Vector2D operator + (const Point2D& p2) const { return Vector2D(x + p2.x, y + p2.y); }
	inline Vector2D operator - (const Point2D& p2) const { return Vector2D(x - p2.x, y - p2.y); }
	inline Vector2D operator * (const Point2D& p2) const { return Vector2D(x * p2.x, y * p2.y); }
	inline Vector2D operator / (const Point2D& p2) const { return Vector2D(x / p2.x, y / p2.y); }


	void operator += (const Vector2D& v2) { x += v2.x; y += v2.y; }
	void operator -= (const Vector2D& v2) { x -= v2.x; y -= v2.y; }
	void operator *= (const Vector2D& v2) { x *= v2.x; y *= v2.y; }
	void operator /= (const Vector2D& v2) { x /= v2.x; y /= v2.y; }
	void operator += (const float f) { x += f; y += f; }
	void operator -= (const float f) { x -= f; y -= f; }
	void operator *= (const float f) { x *= f; y *= f; }
	void operator /= (const float f) { x /= f; y /= f; }
	void operator += (const Point2D& p2) { x += p2.x; y += p2.y; }
	void operator -= (const Point2D& p2) { x -= p2.x; y -= p2.y; }
	void operator *= (const Point2D& p2) { x *= p2.x; y *= p2.y; }
	void operator /= (const Point2D& p2) { x /= p2.x; y /= p2.y; }

	bool operator > (const Vector2D& v2) { return x > v2.x && y > v2.y; }
	bool operator < (const Vector2D& v2) { return x < v2.x && y < v2.y; }
	bool operator >= (const Vector2D& v2) { return x >= v2.x && y >= v2.y; }
	bool operator <= (const Vector2D& v2) { return x <= v2.x && y <= v2.y; }
	bool operator == (const Vector2D& v2) { return x == v2.x && y == v2.y; }
	bool operator != (const Vector2D& v2) { return x != v2.x || y != v2.y; }
};

struct Rect2D {
	Point2D leftBottom, rightTop;
	Vector2D center, rLeftBottom, rLeftTop, rRightBottom, rRightTop;

	Rect2D() : leftBottom(), rightTop(), rLeftBottom(), rLeftTop(), rRightBottom(), rRightTop() {}
	Rect2D(int left, int bottom, int right, int top) : leftBottom(Point2D(left, bottom)), rightTop(Point2D(right, top)) { }
	Rect2D(Point2D lb, Point2D rt) : leftBottom(lb), rightTop(rt) { }
	Rect2D(Vector2D center, int width, int height) : leftBottom(Point2D(center.x - width / 2, center.y - height / 2)), rightTop(Point2D(center.x + width / 2, center.y + height / 2)), center(center) { }
	Rect2D(int centerX, int centerY, int width, int height, uchar center) : leftBottom(Point2D(centerX - width / 2, centerY - height / 2)), rightTop(Point2D(centerX + width / 2, centerY + height / 2)), center(Point2D(centerX, centerY)) { }
	Rect2D(Point2D lb, Point2D rt, float rotate) : rLeftBottom(lb.x*cos(rotate * DEG_TO_RAD) - lb.y*sin(rotate * DEG_TO_RAD), lb.x*sin(rotate * DEG_TO_RAD) + lb.y*cos(rotate * DEG_TO_RAD)),
												rLeftTop(lb.x*cos(rotate* DEG_TO_RAD) - rt.y*sin(rotate * DEG_TO_RAD), lb.x*sin(rotate* DEG_TO_RAD) + rt.y*cos(rotate * DEG_TO_RAD)),
												rRightBottom(rt.x*cos(rotate* DEG_TO_RAD) - lb.y*sin(rotate * DEG_TO_RAD), rt.x*sin(rotate* DEG_TO_RAD) + lb.y*cos(rotate * DEG_TO_RAD)),
												rRightTop(rt.x * cos(rotate* DEG_TO_RAD) - rt.y*sin(rotate * DEG_TO_RAD), rt.x*sin(rotate* DEG_TO_RAD) + rt.y*cos(rotate * DEG_TO_RAD)) { }
	Rect2D(Vector2D center, int width, int height, float rotate) : rLeftBottom( center.x + ((center.x - width / 2) - center.x)* cos(rotate* DEG_TO_RAD) - ((center.y - height / 2) - center.y) * sin(rotate * DEG_TO_RAD), center.y + ((center.x - width / 2) - center.x) * sin(rotate* DEG_TO_RAD) + ((center.y - height / 2) - center.y) * cos(rotate * DEG_TO_RAD)),
																rLeftTop(center.x + ((center.x - width / 2) - center.x) * cos(rotate * DEG_TO_RAD) - ((center.y + height / 2) - center.y) * sin(rotate * DEG_TO_RAD), center.y + ((center.x - width / 2) - center.x) * sin(rotate* DEG_TO_RAD) + ((center.y + height / 2) - center.y) * cos(rotate * DEG_TO_RAD)),
																rRightBottom(center.x + ((center.x + width / 2) - center.x) * cos(rotate * DEG_TO_RAD) - ((center.y - height / 2) - center.y) * sin(rotate * DEG_TO_RAD), center.y + ((center.x + width / 2) - center.x) * sin(rotate * DEG_TO_RAD) + ((center.y - height / 2) - center.y) * cos(rotate * DEG_TO_RAD)),
																rRightTop(center.x + ((center.x + width / 2) - center.x) * cos(rotate * DEG_TO_RAD) - ((center.y + height / 2) - center.y) * sin(rotate * DEG_TO_RAD), center.y + ((center.x + width / 2) - center.x) * sin(rotate * DEG_TO_RAD) + ((center.y + height / 2) - center.y) * cos(rotate * DEG_TO_RAD)),
																center(center) { }

	bool IntersectRect2D(const Rect2D& r) const {
		return (leftBottom.x >= r.leftBottom.x && leftBottom.x <= r.rightTop.x && leftBottom.y >= r.leftBottom.y && leftBottom.y <= r.rightTop.y) ||
			(rightTop.x >= r.leftBottom.x && rightTop.x <= r.rightTop.x && leftBottom.y >= r.leftBottom.y && leftBottom.y <= r.rightTop.y) ||
			(leftBottom.x >= r.leftBottom.x && leftBottom.x <= r.rightTop.x && rightTop.y >= r.leftBottom.y && rightTop.y <= r.rightTop.y) ||
			(rightTop.x >= r.leftBottom.x && rightTop.x <= r.rightTop.x && rightTop.y >= r.leftBottom.y && rightTop.y <= r.rightTop.y);
	}
	bool IntersectRotatedRect2D(const Rect2D& r) const {
		bool isGap = false, isCollision = false;
		Vector2D Axis1, Axis2, Axis3, Axis4;
		Vector2D Represent1, Represent2, Represent3, Represent4;
		Vector2D  rRepresent1, rRepresent2, rRepresent3, rRepresent4;
		float RepresentCompare1, RepresentCompare2,	RepresentCompare3, RepresentCompare4;
		float rRepresentCompare1, rRepresentCompare2, rRepresentCompare3, rRepresentCompare4;

		Axis1.x = rRightTop.x - rLeftTop.x;
		Axis1.y = rRightTop.y - rLeftTop.y;
		Axis2.x = rRightTop.x - rRightBottom.x;
		Axis2.y = rRightTop.y - rRightBottom.y;
		Axis3.x = r.rRightTop.x - r.rLeftTop.x;
		Axis3.y = r.rRightTop.y - r.rLeftTop.y;
		Axis4.x = r.rRightTop.x - r.rRightBottom.x;
		Axis4.y = r.rRightTop.y - r.rRightBottom.y;

		vector<Vector2D> Axiss;
		Axiss.push_back(Axis1); 
		Axiss.push_back(Axis2);
		Axiss.push_back(Axis3);
		Axiss.push_back(Axis4);

		for (Vector2D axis : Axiss) {
			Represent1.x = ((rRightTop.x * axis.x + rRightTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			Represent1.y = ((rRightTop.x * axis.x + rRightTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;
			Represent2.x = ((rLeftTop.x * axis.x + rLeftTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			Represent2.y = ((rLeftTop.x * axis.x + rLeftTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;
			Represent3.x = ((rRightBottom.x * axis.x + rRightBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			Represent3.y = ((rRightBottom.x * axis.x + rRightBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;
			Represent4.x = ((rLeftBottom.x * axis.x + rLeftBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			Represent4.y = ((rLeftBottom.x * axis.x + rLeftBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;

			rRepresent1.x = ((r.rRightTop.x * axis.x + r.rRightTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			rRepresent1.y = ((r.rRightTop.x * axis.x + r.rRightTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;
			rRepresent2.x = ((r.rLeftTop.x * axis.x + r.rLeftTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			rRepresent2.y = ((r.rLeftTop.x * axis.x + r.rLeftTop.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;
			rRepresent3.x = ((r.rRightBottom.x * axis.x + r.rRightBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			rRepresent3.y = ((r.rRightBottom.x * axis.x + r.rRightBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;
			rRepresent4.x = ((r.rLeftBottom.x * axis.x + r.rLeftBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.x;
			rRepresent4.y = ((r.rLeftBottom.x * axis.x + r.rLeftBottom.y * axis.y) / (pow(axis.x, 2) + pow(axis.y, 2))) * axis.y;


			RepresentCompare1 = Represent1.x * axis.x + Represent1.y * axis.y;
			RepresentCompare2 = Represent2.x * axis.x + Represent2.y * axis.y;
			RepresentCompare3 = Represent3.x * axis.x + Represent3.y * axis.y;
			RepresentCompare4 = Represent4.x * axis.x + Represent4.y * axis.y;

			rRepresentCompare1 = rRepresent1.x * axis.x + rRepresent1.y * axis.y;
			rRepresentCompare2 = rRepresent2.x * axis.x + rRepresent2.y * axis.y;
			rRepresentCompare3 = rRepresent3.x * axis.x + rRepresent3.y * axis.y;
			rRepresentCompare4 = rRepresent4.x * axis.x + rRepresent4.y * axis.y;

			
			if(max({ rRepresentCompare1, rRepresentCompare2, rRepresentCompare3, rRepresentCompare4 }) >= max({ RepresentCompare1, RepresentCompare2, RepresentCompare3, RepresentCompare4 })) {
				if (min({ rRepresentCompare1, rRepresentCompare2, rRepresentCompare3, rRepresentCompare4 }) >= max({ RepresentCompare1, RepresentCompare2, RepresentCompare3, RepresentCompare4 }))
					return false;
			}
			else {
				if (max({ rRepresentCompare1, rRepresentCompare2, rRepresentCompare3, rRepresentCompare4 }) <= min({ RepresentCompare1, RepresentCompare2, RepresentCompare3, RepresentCompare4 }))
					return false;
			}
		}


			return true;
	}

	bool IntersectMouse(const POINT& mousePt) const {
		return mousePt.x >= leftBottom.x && mousePt.x <= rightTop.x && mousePt.y <= rightTop.y && mousePt.y >= leftBottom.y;
	}
};

struct Color2D {
	float r, g, b;

	Color2D() : r(1.0f), g(1.0f), b(1.0f) {}
	Color2D(float _r, float _g, float _b) : r(_r), g(_g), b(_b) { }
	void SetColor(float _r, float _g, float _b) { r = _r, g = _g, b = _b; }
};

class Angle {
private:
	float degree;
public:
	Angle() : degree(0.0f) { }
	Angle(float f) { setDegree(f); }
	inline float getDegree() const { return degree; }
	void setDegree(float angle) { 
		while (angle < 0) angle += 360.0f;
		degree = (angle - (int)angle) + ((int)angle % 360);
	}

	Angle operator + (const Angle& a) { return Angle(degree + a.degree); }
	Angle operator - (const Angle& a) { return Angle(degree - a.degree); }
	Angle operator + (const float f) { return Angle(degree + f); }
	Angle operator - (const float f) { return Angle(degree - f); }
	void operator += (const Angle& a) { setDegree(degree + a.degree); }
	void operator -= (const Angle& a) { setDegree(degree - a.degree); }
	void operator += (const float a) { setDegree(degree + a); }
	void operator -= (const float a) { setDegree(degree - a); }
};

struct AnglePoint {
	float x, y, z;

	void SetAnglePointX() { x = 1.0f; y = 0.0f; z = 0.0f; }
	void SetAnglePointY() { x = 0.0f; y = 1.0f; z = 0.0f; }
	void SetAnglePointZ() { x = 0.0f; y = 0.0f; z = 1.0f; }

	AnglePoint() : x(0.0f), y(0.0f), z(1.0f) {}
};

struct Anchor {
	enum AnchorPos {
		LEFT_BOTTOM,
		RIGHT_BOTTOM,
		LEFT_TOP,
		RIGHT_TOP,
		CENTER,
		BOTTOM
	};
	AnchorPos ap;
	Anchor() : ap(Anchor::LEFT_BOTTOM) { }
	Anchor(AnchorPos _ap) : ap(_ap) { }
	AnchorPos Get() const { return ap; }
	void operator=(const AnchorPos ap) { this->ap = ap; }
};

struct Transformation {
	Vector2D position;
	Vector2D scale;
	Angle rotate;
	AnglePoint anglePoont;
	Anchor anchor;
	Color2D color;
	float alpha;
	Transformation() : position(), scale(1.0f, 1.0f), rotate(), anchor(), alpha(1.0f), color(1.0f, 1.0f, 1.0f), anglePoont()  { }
	Transformation(Vector2D _pos, Vector2D _sca, Angle _rot) : position(_pos), scale(_sca), rotate(_rot), anchor(), alpha(1.0f), color(1.0f, 1.0f, 1.0f), anglePoont() { }
};

struct TextureGenerateParam {
	enum TextureMod {
		LINEAR,
		NEAREST
	};

	TextureMod minFilter;
	TextureMod magFilter;

	TextureGenerateParam() : minFilter(LINEAR), magFilter(LINEAR) { }
	TextureGenerateParam(TextureMod min, TextureMod mag) : minFilter(min), magFilter(mag) { }
	GLfloat GetValue(TextureMod mod);
	GLfloat GetMinFilter() { return GetValue(minFilter); }
	GLfloat GetMagFilter() { return GetValue(magFilter); }
};

struct TextureSource {
private:
	static uint counter;
public:
	// ID
	const uint      uid;
	const GLuint    tid;

	// Memory Size(Not use)
	uchar power;
	ulong length;  
	ulong totalSize;

	double texPowerOfX;
	double texPowerOfY;

	// Effective Range (Actual Data Available Range)
	ulong width, height;
	ulong size;
	Vector2D coord;

	// Used Range
	Rect2D range;

	uint spriteWidth;
	uint spriteHeight;

	//alpha
	float alpha;

	TextureSource() : uid(counter++), tid(0), power(0), length(0), totalSize(0),
		width(0), height(0), size(0), coord(), range(), spriteWidth(1), spriteHeight(1), alpha(1.0f) { }
	TextureSource(GLuint _tid) : uid(counter++), tid(_tid), power(0), length(0), totalSize(0),
		width(0), height(0), size(0), coord(), range(), spriteWidth(1), spriteHeight(1), alpha(1.0f) { }
	virtual inline GLuint Get(ullong frame) const { return tid; }
	virtual inline Rect2D GetRange(ullong frame) const { return range; }
	void SetRange(Rect2D range);
};

struct AnimatedTexture : TextureSource {
	const vector<GLuint> tids;
	uint count;

	AnimatedTexture() : tids(), count(0) { }
	AnimatedTexture(const vector<GLuint>& _tids) : tids(_tids), count(_tids.size()) { }
	virtual GLuint Get(ullong frame) const { return count ? tids.at(frame % count) : 0; }
	vector<GLuint>::const_iterator Begin() { return tids.begin(); }
	vector<GLuint>::const_iterator End() { return tids.end(); }
};

struct AnimatedSpriteTexture : TextureSource {
	const GLuint    tid;
	const vector<Rect2D> ranges;
	uint count;

	AnimatedSpriteTexture() : tid(), ranges(), count(0) { }
	AnimatedSpriteTexture(GLuint _tid, const vector<Rect2D> _ranges) : tid(_tid), ranges(_ranges), count(_ranges.size()) { }
	virtual GLuint Get(ullong frame) const { return tid; }
	virtual Rect2D GetRange(ullong frame) const { return count ? ranges.at(frame % count) : ranges[0]; }
};

struct Character {
	uint uid;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	uint Advance;
};

struct CharacterStorage {
	map<GLchar, Character> Characters;
	void Add(char c, Character chars) { Characters.insert(pair(c, chars)); }
};

struct TextureStorage {
	map<uint, const TextureSource*> textureMap;
	void Add(const TextureSource* texture) { textureMap.insert(make_pair(texture->uid, texture)); }
	void Remove(uint uid);
	const TextureSource& Find(uint uid);
};

struct NamedTextureStorage {
	map<string, uint> namedMap;
	void Add(uint uid, string alias) { namedMap.insert(make_pair(alias, uid)); }
	void Remove(string alias);
	uint Find(string alias);
};


struct IDisposable {
	bool disposed;
	virtual void Dispose() { };
};

struct IUpdatable {
	// Single Called Initializer For Each State
	virtual void OnBegin() { }
	virtual void OnEnd() { }

	// Keep Called Until State Change (For Logic)
	virtual void OnUpdateLoading() { }
	virtual void OnUpdate() { }
	virtual void OnUpdateClosing() { }

	// Keep Called Ultil State Change (For Drawing)
	virtual void OnRenderLoading() { }
	virtual void OnRender() { }
	virtual void OnRenderClosing() { }
};