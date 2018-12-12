#include <xmmintrin.h>
#include <smmintrin.h>

#pragma once

namespace Engine
{
		static const __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
		class Vector3SIMD
		{

		public:

			inline Vector3SIMD();
			inline Vector3SIMD(float a, float b, float c);
			inline Vector3SIMD(__m128 vector);

			inline Vector3SIMD operator+(const Vector3SIMD& vector) const;
			inline Vector3SIMD operator-(const Vector3SIMD& vector) const;
			inline Vector3SIMD operator*(const Vector3SIMD& vector) const;
			inline Vector3SIMD operator/(const Vector3SIMD& vector) const;

			inline Vector3SIMD& operator+=(const Vector3SIMD& vector);
			inline Vector3SIMD& operator-=(const Vector3SIMD& vector);
			inline Vector3SIMD& operator*=(const Vector3SIMD& vector);
			inline Vector3SIMD& operator/=(const Vector3SIMD& vector);

			inline Vector3SIMD & operator=(const Vector3SIMD & i_vector);
			inline Vector3SIMD operator-(void);
			inline bool operator==(const Vector3SIMD& vector) const;
			inline Vector3SIMD Cross(const Vector3SIMD & vector);
			inline float Dot(const Vector3SIMD& vector);

			inline float Length();
			inline Vector3SIMD Normalize();

		private:
			union
			{
				struct
				{
					float x, y, z;
				};
				__m128 vec3;
			};
		};

		inline Vector3SIMD::Vector3SIMD() : vec3(_mm_setzero_ps())
		{}

		inline Vector3SIMD::Vector3SIMD(float a, float b, float c) :
			vec3(_mm_set_ps(0, c, b, a))
		{}

		inline Vector3SIMD::Vector3SIMD(__m128 vector) : vec3(vector)
		{}

		inline Vector3SIMD Vector3SIMD::operator+(const Vector3SIMD& vector) const
		{
			return _mm_add_ps(vec3, vector.vec3);
		}

		inline Vector3SIMD Vector3SIMD::operator-(const Vector3SIMD& vector) const
		{
			return _mm_sub_ps(vec3, vector.vec3);
		}

		inline Vector3SIMD Vector3SIMD::operator*(const Vector3SIMD& vector) const
		{
			return _mm_mul_ps(vec3, vector.vec3);
		}

		inline Vector3SIMD Vector3SIMD::operator/(const Vector3SIMD& vector) const
		{
			return _mm_div_ps(vec3, vector.vec3);
		}

		inline Vector3SIMD& Vector3SIMD::operator+=(const Vector3SIMD& vector)
		{
			this->vec3 = _mm_add_ps(vec3, vector.vec3);
			return *this;
		}

		inline Vector3SIMD& Vector3SIMD::operator-=(const Vector3SIMD& vector)
		{
			this->vec3 = _mm_sub_ps(vec3, vector.vec3);
			return *this;
		}

		inline Vector3SIMD& Vector3SIMD::operator*=(const Vector3SIMD& vector)
		{
			this->vec3 = _mm_mul_ps(vec3, vector.vec3);
			return *this;
		}

		inline Vector3SIMD& Vector3SIMD::operator/=(const Vector3SIMD& vector)
		{
			this->vec3 = _mm_div_ps(vec3, vector.vec3);
			return *this;
		}

		inline Vector3SIMD& Vector3SIMD::operator=(const Vector3SIMD & vector)
		{
			this->vec3 = vector.vec3;
			return *this;
		}

		inline Vector3SIMD Vector3SIMD::operator-(void)
		{
			return _mm_xor_ps(vec3, SIGNMASK);
		}

		inline bool Vector3SIMD::operator==(const Vector3SIMD & vector) const
		{
			return(((_mm_movemask_ps(_mm_cmpeq_ps(vec3, vector.vec3))) & 0x7) == 0x7);
		}

		inline Vector3SIMD Vector3SIMD::Cross(const Vector3SIMD & vector)
		{
			return Vector3SIMD(_mm_sub_ps(
				_mm_mul_ps(_mm_shuffle_ps(vec3, vec3, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(vector.vec3, vector.vec3, _MM_SHUFFLE(3, 1, 0, 2))),
				_mm_mul_ps(_mm_shuffle_ps(vec3, vec3, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(vector.vec3, vector.vec3, _MM_SHUFFLE(3, 0, 2, 1)))
			));
		}

		inline float Vector3SIMD::Dot(const Vector3SIMD& vector)
		{
			return _mm_cvtss_f32(_mm_dp_ps(vec3, vector.vec3, 0x71));
		}

		inline float Vector3SIMD::Length()
		{
			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(vec3, vec3, 0x71)));
		}

}
