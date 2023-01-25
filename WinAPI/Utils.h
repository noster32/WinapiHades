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

	Rect2D() : leftBottom(), rightTop() {}
	Rect2D(int left, int bottom, int right, int top) : leftBottom(Point2D(left, bottom)), rightTop(Point2D(right, top)) { }
	Rect2D(Point2D lb, Point2D rt) : leftBottom(lb), rightTop(rt) { }

	bool IntersectRect(const Rect2D& r) const {
		return (leftBottom.x >= r.leftBottom.x && leftBottom.x <= r.rightTop.x && leftBottom.y >= r.leftBottom.y && leftBottom.y <= r.rightTop.y) ||
			(rightTop.x >= r.leftBottom.x && rightTop.x <= r.rightTop.x && leftBottom.y >= r.leftBottom.y && leftBottom.y <= r.rightTop.y) ||
			(leftBottom.x >= r.leftBottom.x && leftBottom.x <= r.rightTop.x && rightTop.y >= r.leftBottom.y && rightTop.y <= r.rightTop.y) ||
			(rightTop.x >= r.leftBottom.x && rightTop.x <= r.rightTop.x && rightTop.y >= r.leftBottom.y && rightTop.y <= r.rightTop.y);
	}
	bool IntersectMouse(const POINT& mousePt) const {
		return mousePt.x >= leftBottom.x && mousePt.x <= rightTop.x && mousePt.y <= rightTop.y && mousePt.y >= leftBottom.y;
	}
};

class Angle {
private:
	float degree;
public:
	Angle() : degree(0.0f) { }
	Angle(float f) { setDegree(f) }
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
	void operator += (const Angle& a) { setDegree(degree + a.degree); }
	void operator += (const float a) { setDegree(degree + a); }
	void operator += (const float a) { setDegree(degree + a); }
};
