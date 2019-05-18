#include "Vec.h"
#include <cmath>

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(const Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

Vec3f Vec3f::operator-(const Vec3f &other) const
{
	return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f &Vec3f::operator+=(const Vec3f &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3f& Vec3f::operator*=(const float& other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Vec3f Vec3f::operator*(const float& other) const
{
	return Vec3f(x * other, y * other, z * other);
}

Vec3f Vec3f::normalized() const
{
	const auto len = length();
	return Vec3f(x / len, y / len, z / len);
}

float Vec3f::length() const
{
	return sqrt(x*x+y*y+z*z);
}

void Vec3f::maxXZ(float maxLength)
{
	const auto len = sqrt(x*x + z*z);
	if (len <= maxLength)
		return;

	x /= len;
	z /= len;

	x *= maxLength;
	z *= maxLength;
}

Vec2f::Vec2f(const float x, const float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](const int index)
{
	return v[index];
}
