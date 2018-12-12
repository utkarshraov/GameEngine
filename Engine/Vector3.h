#pragma once
#include "Vector2.h"
namespace Engine {

	class Vector3
	{
	public:
		inline Vector3() { x = 0.0f; y = 0.0f; z = 0.0f; }
		inline Vector3(float a, float b, float c) { x = a; y = b; z = c; }
		inline Vector3(const Vector3 & other) { x = other.getX(); y = other.getY(); z = other.getZ(); }
		inline Vector3(Vector2 other, float zVal) { x = other.getX(), y = other.getY(), z = zVal; }
		void setX(float value)  { x = value; }
		void setY(float value) { y = value; }
		void setZ(float value) { z = value; }

		float getX() const { return x; } 
		float getY() const { return y; } 
		float getZ() const { return z; } 
		static const Vector3 Zero;
		Vector3 normalize();
		float magnitude();

	private:
		float x;
		float y;
		float z;
	};

	Vector3 operator+(const Vector3 & lhs, const Vector3 & rhs);
	Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs);

	Vector3 operator*(const float & val, const Vector3 & rhs);
	Vector3 operator/(const Vector3 & lhs, const float & val);
	Vector3 operator*(const Vector3 & lhs, const float & val);

	bool operator==(const Vector3 & lhs, const Vector3 & rhs);
	bool operator!=(const Vector3 & lhs, const Vector3 & rhs);

	float dot(const Vector3 & lhs, const Vector3 & rhs);
	Vector3 cross(const Vector3 & lhs, const Vector3 & rhs);

	
}