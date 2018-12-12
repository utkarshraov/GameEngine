#pragma once

namespace Engine {
	class Vector4 {
	private:

	public:
		float val[4];
		Vector4()
		{
			for (int i = 0; i < 4; i++)
			{
				val[i] = 0;
			}
		}
		
		Vector4(float newVal[4])
		{
			for (int i = 0; i < 4; i++)
			{
				val[i] = newVal[i];
			}
		}
		
		friend void copyArray(float* a, float* b, float size);
		friend Vector4 operator+(Vector4 lhs, Vector4 rhs);
		friend Vector4 operator-(Vector4 lhs, Vector4 rhs);
		friend Vector4 operator+(Vector4 lhs, Vector4 rhs);
	};
	
}