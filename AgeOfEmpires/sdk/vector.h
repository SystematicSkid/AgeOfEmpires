#pragma once

class Vector
{
public:
	Vector() : x(0), y(0), z(0) {}
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}

	float x, y, z;

	bool operator == (const Vector& v) const { return v.x == x && v.y == y && v.z == z; }
	bool operator != (const Vector& v) const { return v.x != x || v.y != y || v.z != z; }
};