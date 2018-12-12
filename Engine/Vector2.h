#pragma once
#include<iostream>


namespace Engine
{

	class Vector2{
	private:
		float xPosition;
		float yPosition;
	public:
		
		float getX() const;
		float getY() const;
		void setX(float);
		void setY(float);
		Vector2(float, float);
		Vector2();
		float magnitude();
		bool checkEqual(Vector2);
		Vector2 normalise();
		float dot(const Vector2 & lhs, const Vector2 & rhs);
		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
		inline Vector2 operator- (Vector2  i_rhs)
		{
			return Vector2(this->getX() - i_rhs.getX(), this->getY() - i_rhs.getY());
		}

		inline Vector2 operator+ (Vector2  i_rhs)
		{
			return Vector2(this->getX() + i_rhs.getX(), this->getY() + i_rhs.getY());
		}

		inline Vector2 operator* (float multi)
		{
			return Vector2(this->getX() * multi, this->getY() * multi);
		}

		inline Vector2 operator/ (float multi)
		{
			return Vector2(this->getX() / multi, this->getY() / multi);
		}


		inline Vector2 & operator+= (Vector2 value)
		{
			return Vector2(this->getX() + value.getX(), this->getY() + value.getY());
		}


		inline Vector2 & operator-= (Vector2 value)
		{
			return Vector2(this->getX() - value.getX(), this->getY() - value.getY());
		}

	};
	
	
}