#ifndef __VECTOR2_H
#define __VECTOR2_H

namespace Engine
{
	namespace Math
	{
		class Vector2
		{
		public:
			float x, y;
			Vector2() {}

			inline Vector2(float nx, float ny)
			{
				x = nx;
				y = ny;
			}

			inline Vector2(const Vector2 & other)
			{
				x = other.x;
				y = other.y;
			}

			inline Vector2 & operator+=(const Vector2 & rhs);
			inline Vector2 & operator-=(const Vector2 & rhs);

			inline Vector2 & operator*=(const Vector2 & rhs);
			inline Vector2 & operator*=(int rhs);
			inline Vector2 & operator*=(float rhs);

			inline Vector2 & operator/=(const Vector2 & rhs);
			inline Vector2 & operator/=(int rhs);
			inline Vector2 & operator/=(float rhs);

			inline float Length() const;

			inline void Normalize();

		private:
		};
		
		inline bool operator==(const Vector2 & lhs, const Vector2 & rhs);
		inline bool operator!=(const Vector2 & lhs, const Vector2 & rhs);

		inline Vector2 operator+(const Vector2 & lhs, const Vector2 & rhs);
		inline Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs);

		inline Vector2 operator*(const Vector2 & lhs, const Vector2 & rhs);
		inline Vector2 operator*(const Vector2 & lhs, int rhs);
		inline Vector2 operator*(const Vector2 & lhs, float rhs);

		inline Vector2 operator/(const Vector2 & lhs, const Vector2 & rhs);
		inline Vector2 operator/(const Vector2 & lhs, int rhs);
		inline Vector2 operator/(const Vector2 & lhs, float rhs);

		inline float Dot(const Vector2 & lhs, const Vector2 & rhs);
	}
}

#include "Vector2-inl.h"
#endif