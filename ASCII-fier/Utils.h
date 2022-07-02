#pragma once

struct Vec3
{
public:
	int x, y, z;

	Vec3(int xVal = 0, int yVal = 0, int zVal = 0)
		: x(xVal), y(yVal), z(zVal) {}

	friend std::ostream& operator<<(std::ostream& os, const Vec3& vec)
	{
		return (os << vec.x << ' ' << vec.y << ' ' << vec.z);
	}
};

struct Vec3S
{
public:
	void* x, *y, *z;

	Vec3S(void* xVal = nullptr, void* yVal = nullptr, void* zVal = nullptr)
		: x(xVal), y(yVal), z(zVal) {}
};