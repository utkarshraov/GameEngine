#include <xmmintrin.h>
#include <smmintrin.h>
#pragma once

namespace Engine
{

		class Matrix4SIMD
		{
		public:
			inline Matrix4SIMD();
			inline Matrix4SIMD(const float val0, const float val1, const float val2, const float val3, const float val4,
				const float val5, const float val6, const float val7, const float val8, const float val9, const float val10,
				const float val11, const float val12, const float val13, const float val14, const float val15);
			inline Matrix4SIMD(__m128 row0, __m128 row1, __m128 row2, __m128 row3);

			inline __m128 GetRow(int rowNumber);
			inline __m128 GetColumn(int colNumber);

			inline bool IfIdentity();
			inline Matrix4SIMD GetInverse();

			inline Matrix4SIMD & operator*=(Matrix4SIMD& other);
			inline Matrix4SIMD & operator=(Matrix4SIMD& other);
			inline bool operator==(const Matrix4SIMD& other);
			inline void Transpose();

		private:
			union
			{
				struct {
					float vals[16];
				};
				__m128 row[4];
			};
		};






		inline Matrix4SIMD::Matrix4SIMD()
		{
			row[0] = _mm_setzero_ps();
			row[1] = _mm_setzero_ps();
			row[2] = _mm_setzero_ps();
			row[3] = _mm_setzero_ps();
		}

		inline Matrix4SIMD::Matrix4SIMD(const float val0, const float val1, const float val2, const float val3, const float val4,
			const float val5, const float val6, const float val7, const float val8, const float val9, const float val10,
			const float val11, const float val12, const float val13, const float val14, const float val15)
		{
			row[0] = _mm_set_ps(val3, val2, val1, val0);
			row[1] = _mm_set_ps(val7, val6, val5, val4);
			row[2] = _mm_set_ps(val11, val10, val9, val8);
			row[3] = _mm_set_ps(val15, val14, val13, val12);
		}

		inline Matrix4SIMD::Matrix4SIMD(__m128 row0, __m128 row1, __m128 row2, __m128 row3)
		{
			row[0] = row0;
			row[1] = row1;
			row[2] = row2;
			row[3] = row3;
		}

		inline __m128 Matrix4SIMD::GetRow(int rowNumber)
		{
			__m128 temp;
			switch (rowNumber)
			{
			case 1:
				temp = __m128(_mm_set_ps(vals[3], vals[2], vals[1], vals[0]));
				break;
			case 2:
				temp = __m128(_mm_set_ps(vals[7], vals[6], vals[5], vals[4]));
				break;
			case 3:
				temp = __m128(_mm_set_ps(vals[11], vals[10], vals[9], vals[8]));
				break;
			case 4:
				temp = __m128(_mm_set_ps(vals[15], vals[14], vals[13], vals[12]));
				break;
			}

			return temp;
		}

		inline __m128 Matrix4SIMD::GetColumn(int colNumber)
		{
			__m128 temp;
			switch (colNumber)
			{
			case 1:
				temp = __m128(_mm_set_ps(vals[12], vals[8], vals[4], vals[0]));
				break;
			case 2:
				temp = __m128(_mm_set_ps(vals[13], vals[9], vals[5], vals[1]));
				break;
			case 3:
				temp = __m128(_mm_set_ps(vals[14], vals[10], vals[6], vals[2]));
				break;
			case 4:
				temp = __m128(_mm_set_ps(vals[15], vals[11], vals[7], vals[3]));
				break;
			}

			return temp;
		}

		inline bool Matrix4SIMD::IfIdentity()
		{
			return true;
		}

		inline Matrix4SIMD Matrix4SIMD::GetInverse()
		{
			return *this;
		}

		inline Matrix4SIMD & Matrix4SIMD::operator*=(Matrix4SIMD& other)
		{
			Matrix4SIMD temp;

			temp.vals[0] = _mm_cvtss_f32(_mm_dp_ps(this->row[0], other.GetColumn(1), 0xFF));
			temp.vals[1] = _mm_cvtss_f32(_mm_dp_ps(this->row[0], other.GetColumn(2), 0xFF));
			temp.vals[2] = _mm_cvtss_f32(_mm_dp_ps(this->row[0], other.GetColumn(3), 0xFF));
			temp.vals[3] = _mm_cvtss_f32(_mm_dp_ps(this->row[0], other.GetColumn(4), 0xFF));

			temp.vals[4] = _mm_cvtss_f32(_mm_dp_ps(this->row[1], other.GetColumn(1), 0xFF));
			temp.vals[5] = _mm_cvtss_f32(_mm_dp_ps(this->row[1], other.GetColumn(2), 0xFF));
			temp.vals[6] = _mm_cvtss_f32(_mm_dp_ps(this->row[1], other.GetColumn(3), 0xFF));
			temp.vals[7] = _mm_cvtss_f32(_mm_dp_ps(this->row[1], other.GetColumn(4), 0xFF));

			temp.vals[8] = _mm_cvtss_f32(_mm_dp_ps(this->row[2], other.GetColumn(1), 0xFF));
			temp.vals[9] = _mm_cvtss_f32(_mm_dp_ps(this->row[2], other.GetColumn(2), 0xFF));
			temp.vals[10] = _mm_cvtss_f32(_mm_dp_ps(this->row[2], other.GetColumn(3), 0xFF));
			temp.vals[11] = _mm_cvtss_f32(_mm_dp_ps(this->row[2], other.GetColumn(4), 0xFF));

			temp.vals[12] = _mm_cvtss_f32(_mm_dp_ps(this->row[3], other.GetColumn(1), 0xFF));
			temp.vals[13] = _mm_cvtss_f32(_mm_dp_ps(this->row[3], other.GetColumn(2), 0xFF));
			temp.vals[14] = _mm_cvtss_f32(_mm_dp_ps(this->row[3], other.GetColumn(3), 0xFF));
			temp.vals[15] = _mm_cvtss_f32(_mm_dp_ps(this->row[3], other.GetColumn(4), 0xFF));

			*this = temp;
			return *this;
		}

		inline Matrix4SIMD & Matrix4SIMD::operator=(Matrix4SIMD& other)
		{
			this->row[0] = other.row[0];
			this->row[1] = other.row[1];
			this->row[2] = other.row[2];
			this->row[3] = other.row[3];

			return *this;
		}

		inline bool Matrix4SIMD::operator==(const Matrix4SIMD& other)
		{
			return ((((_mm_movemask_ps(_mm_cmpeq_ps(this->row[0], other.row[0]))) & 0x7) == 0x7) &&
				(((_mm_movemask_ps(_mm_cmpeq_ps(this->row[1], other.row[1]))) & 0x7) == 0x7) &&
				(((_mm_movemask_ps(_mm_cmpeq_ps(this->row[2], other.row[2]))) & 0x7) == 0x7) &&
				(((_mm_movemask_ps(_mm_cmpeq_ps(this->row[3], other.row[3]))) & 0x7) == 0x7));
		}

		inline void Matrix4SIMD::Transpose()
		{
			Matrix4SIMD temp;
			temp.row[0] = this->GetColumn(1);
			temp.row[1] = this->GetColumn(2);
			temp.row[2] = this->GetColumn(3);
			temp.row[3] = this->GetColumn(4);

			*this = temp;
		}

	
}

