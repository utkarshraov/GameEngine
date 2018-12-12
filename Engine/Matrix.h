#pragma once
#include "Vector4.h"
#include "Vector3.h"

namespace Engine {

	
		class Matrix
		{
		public:
			Matrix();
			Matrix(float newVals[16]);
			Matrix(const Matrix & other);
			Matrix& operator=(const Matrix & other);


			Vector3 operator*(const Vector3 & newVector);

			Matrix Transpose();
			Matrix Inversion();
			Matrix Translate(const Vector3 & Vector);
			Matrix Rotate(const Vector3 & axis, const float angle);
			Matrix Scale(const Vector3 & vector);

			friend Matrix operator+(const Matrix & lhs, const Matrix & rhs);
			friend Matrix operator-(const Matrix & lhs, const Matrix & rhs);
			friend Matrix operator*(const Matrix & lhs, const float val);
			friend Matrix operator*(const float val, const Matrix & rhs);
			friend Matrix operator*(const Matrix & lhs, const Matrix & rhs);
			friend Matrix operator/(const Matrix & lhs, const float val);

			/*friend bool operator==(const Matrix & lhs, const Matrix & rhs);
			friend bool operator!=(const Matrix & lhs, const Matrix & rhs);
			friend bool IsEqual(const Matrix & lhs, const Matrix & rhs);*/

			static const Matrix Zero;

		private:
			float vals[16];
		};

}

