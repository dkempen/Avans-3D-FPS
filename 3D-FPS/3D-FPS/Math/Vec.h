#pragma once

class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3]{};
	};
	Vec3f();
	Vec3f(const Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);

	Vec3f operator - (const Vec3f &other) const;
	Vec3f operator * (const float &other) const;
	Vec3f &operator += (const Vec3f &other);
	Vec3f &operator *= (const float& other);

	Vec3f normalize() const;
	static Vec3f crossProduct(const Vec3f &v1, const Vec3f &v2);
	Vec3f inverse() const;
	float length() const;
	void maxXZ(float maxLength);
};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2]{};
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(const Vec2f &other);
	float& operator [](int);
};
