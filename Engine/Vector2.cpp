#include "Vector2.h"
#include<math.h>


namespace Engine
{
	static const Vector2 Up = Vector2(0, 1);
	static const Vector2 Down = Vector2(0, -1);
	static const Vector2 Right = Vector2(1, 0);
	static const Vector2 Left = Vector2(-1, 0);


		float Vector2::getX() const{
			return xPosition;
		}

		float Vector2::getY() const{
			return yPosition;
		}

		void Vector2::setX(float value)
		{
			xPosition = value;
		}

		void Vector2::setY(float value)
		{
			yPosition = value;
		}

		float Vector2::magnitude()
		{
			return sqrtf(pow(xPosition, 2)+ pow(yPosition, 2));
		}

		Vector2::Vector2(float xValue, float yValue) 
		{
			xPosition = xValue;
			yPosition = yValue;
		}

		Vector2::Vector2() {
			xPosition = 0;
			yPosition = 0;
		};

		bool Vector2::checkEqual(Vector2 value)
		{
			if (xPosition == value.xPosition && yPosition == value.yPosition)
				return true;
			return false;
		}
		Vector2 Vector2::normalise()
		{
			if (magnitude() != 0)
			{
				float nX = xPosition / magnitude();
				float nY = yPosition / magnitude();
				return Vector2(nX, nY);
			}
			else
				return Vector2(0, 0);
		}
		float Vector2::dot(const Vector2 & lhs, const Vector2 & rhs)
		{
			return lhs.getX() * rhs.getX() + lhs.getY() * rhs.getY();
		}
		
	
	
		std::ostream & operator<<(std::ostream & stream, const Vector2 & vector)
		{
			
			stream << "("<<vector.getX() <<","<< vector.getY()<<")";
			return stream;
		}
		
	
}