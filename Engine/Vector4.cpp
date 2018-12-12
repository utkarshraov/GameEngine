#include "Vector4.h"

namespace Engine {
	Vector4 operator+(Vector4 &lhs, Vector4 &rhs)
	{
		Vector4 temp;
		for (int i = 0; i < 4; i++)
		{
			temp.val[i] = lhs.val[i] + rhs.val[i];
		}
		return temp;
	}

	Vector4 operator-(Vector4 &lhs, Vector4 &rhs)
	{
		Vector4 temp;
		for (int i = 0; i < 4; i++)
		{
			temp.val[i] = lhs.val[i] - rhs.val[i];
		}
		return temp;
	}

	void copyArray(float *a, float *b, float size)
	{
		if (size == 0) return;
		*a = *b;
		copyArray(++a, ++b, size - 1);
	}
}