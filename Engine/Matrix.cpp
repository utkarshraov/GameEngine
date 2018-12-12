#include "Matrix.h"
#include "DebugStatement.h"
#include<math.h>

namespace Engine {
	/*const Matrix Matrix::Zero({ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 });*/

	Matrix Matrix::Transpose()
	{
		Matrix result;

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.vals[i * 4 + j] = vals[j * 4 + i];

		return result;
	}

	Matrix Matrix::Inversion()
	{
		Matrix result;

		result.vals[0] = vals[5] * vals[10] * vals[15] + vals[5] * vals[10] * vals[13] + vals[6] * vals[9] * vals[10] - vals[5] * vals[11] * vals[14] - vals[6] * vals[9] * vals[15] - vals[7] * vals[10] * vals[13];
		result.vals[1] = vals[1] * vals[11] * vals[14] + vals[2] * vals[9] * vals[15] + vals[3] * vals[10] * vals[13] - vals[1] * vals[10] * vals[15] - vals[2] * vals[11] * vals[13] - vals[3] * vals[9] * vals[14];
		result.vals[2] = vals[1] * vals[6] * vals[15] + vals[2] * vals[7] * vals[13] + vals[3] * vals[5] * vals[14] - vals[1] * vals[7] * vals[14] - vals[2] * vals[5] * vals[15] - vals[3] * vals[6] * vals[13];
		result.vals[3] = vals[1] * vals[7] * vals[10] + vals[2] * vals[5] * vals[11] + vals[3] * vals[6] * vals[9] - vals[1] * vals[6] * vals[11] - vals[2] * vals[7] * vals[9] - vals[3] * vals[5] * vals[10];
		result.vals[4] = vals[1] * vals[11] * vals[14] + vals[6] * vals[8] * vals[15] + vals[7] * vals[10] * vals[12] - vals[4] * vals[10] * vals[15] - vals[6] * vals[11] * vals[12] - vals[7] * vals[8] * vals[14];
		result.vals[5] = vals[0] * vals[10] * vals[15] + vals[2] * vals[11] * vals[12] + vals[3] * vals[8] * vals[14] - vals[0] * vals[11] * vals[14] - vals[2] * vals[8] * vals[15] - vals[3] * vals[10] * vals[12];
		result.vals[6] = vals[0] * vals[7] * vals[14] + vals[2] * vals[4] * vals[15] + vals[3] * vals[6] * vals[12] - vals[0] * vals[6] * vals[15] - vals[2] * vals[7] * vals[12] - vals[3] * vals[4] * vals[14];
		result.vals[7] = vals[0] * vals[6] * vals[11] + vals[2] * vals[7] * vals[8] + vals[3] * vals[4] * vals[10] - vals[0] * vals[7] * vals[10] - vals[2] * vals[4] * vals[11] - vals[3] * vals[6] * vals[8];
		result.vals[8] = vals[4] * vals[9] * vals[15] + vals[5] * vals[11] * vals[12] + vals[7] * vals[8] * vals[13] - vals[4] * vals[11] * vals[13] - vals[5] * vals[8] * vals[15] - vals[7] * vals[9] * vals[12];
		result.vals[9] = vals[0] * vals[11] * vals[13] + vals[5] * vals[8] * vals[15] + vals[3] * vals[9] * vals[12] - vals[0] * vals[9] * vals[15] - vals[1] * vals[11] * vals[12] - vals[3] * vals[4] * vals[13];
		result.vals[10] = vals[0] * vals[5] * vals[15] + vals[1] * vals[7] * vals[12] + vals[3] * vals[4] * vals[13] - vals[0] * vals[7] * vals[13] - vals[1] * vals[4] * vals[15] - vals[3] * vals[5] * vals[12];
		result.vals[11] = vals[0] * vals[7] * vals[9] + vals[1] * vals[4] * vals[10] + vals[3] * vals[5] * vals[8] - vals[0] * vals[5] * vals[11] - vals[1] * vals[7] * vals[8] - vals[3] * vals[4] * vals[9];
		result.vals[12] = vals[4] * vals[10] * vals[12] + vals[5] * vals[8] * vals[14] + vals[6] * vals[9] * vals[12] - vals[4] * vals[9] * vals[14] - vals[5] * vals[10] * vals[12] - vals[6] * vals[8] * vals[13];
		result.vals[13] = vals[0] * vals[9] * vals[14] + vals[1] * vals[10] * vals[12] + vals[2] * vals[8] * vals[13] - vals[0] * vals[10] * vals[13] - vals[1] * vals[8] * vals[14] - vals[2] * vals[9] * vals[12];
		result.vals[14] = vals[0] * vals[6] * vals[13] + vals[1] * vals[4] * vals[14] + vals[2] * vals[5] * vals[12] - vals[0] * vals[5] * vals[14] - vals[1] * vals[6] * vals[12] - vals[2] * vals[8] * vals[13];
		result.vals[15] = vals[0] * vals[5] * vals[10] + vals[1] * vals[6] * vals[8] + vals[2] * vals[4] * vals[9] - vals[0] * vals[6] * vals[9] - vals[1] * vals[4] * vals[10] - vals[2] * vals[5] * vals[8];

		return result;
	}

	Matrix Matrix::Translate(const Vector3 & newVector)
	{
		Matrix result;
		result.vals[3] = newVector.getX();
		result.vals[7] = newVector.getY();
		result.vals[11] = newVector.getZ();

		return result;
	}

	Matrix Matrix::Rotate(const Vector3 & newVector, const float angle)
	{
		Matrix result;
		float s = sin(angle);
		float c = cos(angle);

		result.vals[0] = c + pow(newVector.getX(), 2) * (1 - c);
		result.vals[1] = newVector.getX() * newVector.getY() * (1 - c) - newVector.getZ() * s;
		result.vals[2] = newVector.getX() * newVector.getZ() * (1 - c) - newVector.getY() * s;

		result.vals[4] = newVector.getY() * newVector.getX() * (1 - c) - newVector.getZ() * s;
		result.vals[5] = c + pow(newVector.getY(), 2) * (1 - c);
		result.vals[6] = newVector.getY() * newVector.getZ() * (1 - c) - newVector.getX() * s;

		result.vals[8] = newVector.getZ() * newVector.getX() * (1 - c) - newVector.getY() * s;
		result.vals[9] = newVector.getZ() * newVector.getY() * (1 - c) - newVector.getX() * s;
		result.vals[10] = c + pow(newVector.getZ(), 2) * (1 - c);

		return result;
	}

	Matrix Matrix::Scale(const Vector3 & newVector)
	{
		Matrix result;
		result.vals[0] = newVector.getX();
		result.vals[5] = newVector.getY();
		result.vals[10] = newVector.getZ();

		return result;
	}

	 Matrix::Matrix()
	{
		for (int i = 0; i < 16; ++i)
			vals[i] = 0;
		vals[0] = vals[5] = vals[10] = vals[15] = 1.0f;
	}

	 Matrix::Matrix(float arr[16])
	{
		 for (int i = 0; i < 16; ++i)
			vals[i] = arr[i];
	}

	 Matrix::Matrix(const Matrix & other)
	{
		for (int i = 0; i < 16; ++i)
			vals[i] = other.vals[i];
	}

	 Matrix& Matrix::operator=(const Matrix & other)
	{
		for (int i = 0; i < 16; ++i)
			vals[i] = other.vals[i];

		return *this;
	}



	 Vector3 Matrix::operator*(const Vector3 & newVector)
	{
		return Vector3(vals[0] * newVector.getX() + vals[1] * newVector.getY() + vals[2] * newVector.getZ() + vals[3],
			vals[4] * newVector.getX() + vals[5] * newVector.getY() + vals[6] * newVector.getZ() + vals[7],
			vals[8] * newVector.getX() + vals[9] * newVector.getY() + vals[10] * newVector.getZ() + vals[11]);
	}

	 Matrix operator+(const Matrix & lhs, const Matrix & rhs)
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
		{
			result.vals[i] = lhs.vals[i] + rhs.vals[i];
		}

		return result;
	}

	 Matrix operator-(const Matrix & lhs, const Matrix & rhs)
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
		{
			result.vals[i] = lhs.vals[i] - rhs.vals[i];
		}

		return result;
	}

	 Matrix operator*(const Matrix & lhs, const float val)
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
		{
			result.vals[i] = lhs.vals[i] * val;
		}

		return result;
	}

	 Matrix operator*(const Matrix & lhs, const Matrix & rhs)
	{
		float elements[16];
		for (int i = 0; i < 16; ++i)
		{
			elements[i] = lhs.vals[(i / 4) * 4 + 0] * rhs.vals[(i % 4) + 0] +
				lhs.vals[(i / 4) * 4 + 1] * rhs.vals[(i % 4) + 4] +
				lhs.vals[(i / 4) * 4 + 2] * rhs.vals[(i % 4) + 8] +
				lhs.vals[(i / 4) * 4 + 3] * rhs.vals[(i % 4) + 12];
		}

		Matrix matrix(elements);
		return matrix;

	}

	 Matrix operator*(const float val, const Matrix & rhs)
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
		{
			result.vals[i] = rhs.vals[i] + val;
		}

		return result;
	}

	 Matrix operator/(const Matrix & lhs, const float val)
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
		{
			result.vals[i] = lhs.vals[i] / val;
		}

		return result;
	}

	// bool operator==(const Matrix & lhs, const Matrix & rhs)
	//{
	//	return IsEqual(lhs, rhs);
	//}

	// bool operator!=(const Matrix & lhs, const Matrix & rhs)
	//{
	//	return !IsEqual(lhs, rhs);
	//}

	//bool IsEqual(const Matrix & lhs, const Matrix & rhs)
	//{
	//	for (int i = 0; i < 4; ++i)
	//	{
	//		if (lhs[i] != rhs[i])
	//			return false;
	//	}
	//	return true;
	//}

}