#include<math.h>
#include "Vector3.h"

namespace Engine
{
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

	Vector3 operator+(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY(), lhs.getZ() + rhs.getZ());
	}
	 Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY(), lhs.getZ() - rhs.getZ());
	}
	 Vector3 operator*(const float & val, const Vector3 & rhs)
	{
		return Vector3(rhs.getX() * val, rhs.getY() * val, rhs.getZ() * val);
	}
	 Vector3 operator/(const Vector3 & lhs, const float & val)
	{
		return Vector3(lhs.getX() / val, lhs.getY() / val, lhs.getZ() / val);
	}
	 Vector3 operator*(const Vector3 & lhs, const float & val)
	{
		return Vector3(lhs.getX() * val, lhs.getY() * val, lhs.getZ() * val);
	}
	 bool operator==(const Vector3 & lhs, const Vector3 & rhs)
	{
		if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	 bool operator!=(const Vector3 & lhs, const Vector3 & rhs)
	{
		if (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	 float dot(const Vector3 & lhs, const Vector3 & rhs)
	{
		return lhs.getX() * rhs.getX() + lhs.getY() * rhs.getY() + lhs.getZ() * rhs.getZ();
	}
	 Vector3 cross(const Vector3 & lhs, const Vector3 & rhs)
	{
		return Vector3(lhs.getY() * rhs.getZ() - lhs.getZ() * rhs.getY(),
			lhs.getZ() * rhs.getX() - lhs.getX() * rhs.getZ(),
			lhs.getX() * rhs.getY() - lhs.getY() * rhs.getX());

	}

	Vector3 Vector3::normalize()
	{
		if (magnitude() != 0)
		{
			float newX = x / magnitude();
			float newY = y / magnitude();
			float newZ = z / magnitude();
			return Vector3(newX, newY, newZ);
		}
		else 
			return Vector3(0,0,0);
	}

	float Vector3::magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	
}