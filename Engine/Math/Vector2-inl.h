#ifndef __Vec2Inl
#define __Vec2Inl

#include "assert.h"
#include "math.h"
#include "Vector2.h"

namespace Engine
{
	namespace Math
	{
		// Dot product
		inline float Dot(const Vector2 & lhs, const Vector2 & rhs)
		{
			return (float)(lhs.x * rhs.x  + lhs.y * rhs.y);
		}

		// Length
		inline float Vector2::Length() const
		{
			return (float)sqrt((x * x) + ( y * y));
		}

		inline void Vector2::Normalize()
		{
			if (Length() == 0.0f)
			{
				return;
			}
			else
			{
				float inv_length = 1.0f / Length();
				*this = *this * inv_length;
			}
		}

		// Add operator
		inline Vector2 operator+(const Vector2 & lhs, const Vector2 & rhs)
		{
			return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
		}

		// Minus operator
		inline Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs)
		{
			return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
		}

		// Multiplication operators
		inline Vector2 operator*(const Vector2 & lhs, const Vector2 & rhs)
		{
			return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
		}
		inline Vector2 operator*(const Vector2 & lhs, int rhs)
		{
			return Vector2(lhs.x * rhs, lhs.y * rhs);
		}
		inline Vector2 operator*(const Vector2 & lhs, float rhs)
		{
			return Vector2((lhs.x * rhs), (lhs.y * rhs));
		}

		// Divide operator
		inline Vector2 operator/(const Vector2 & lhs, const Vector2 & rhs)
		{
			assert(rhs.x);
			assert(rhs.y);
			return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
		}
		inline Vector2 operator/(const Vector2 & lhs, int rhs)
		{
			assert(rhs);
			return Vector2(lhs.x / rhs, lhs.y / rhs);
		}
		inline Vector2 operator/(const Vector2 & lhs, float rhs)
		{
			assert(rhs);
			return Vector2(((float)lhs.x / rhs), ((float)lhs.y / rhs));
		}

		// == operator
		inline bool operator==(const Vector2 & lhs, const Vector2 & rhs)
		{
			return (lhs.x == rhs.x && lhs.y == rhs.y);
		}
		// != operator
		inline bool operator!=(const Vector2 & lhs, const Vector2 & rhs)
		{
			return !(lhs.x == rhs.x && lhs.y == rhs.y);
		}

		// += operator
		inline Vector2 & Vector2::operator+=(const Vector2 & rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		// -= operator
		inline Vector2 & Vector2::operator-=(const Vector2 & rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		// *= operator
		inline Vector2 & Vector2::operator*=(const Vector2 & rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}
		inline Vector2 & Vector2::operator*=(int rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}
		inline Vector2 & Vector2::operator*=(float rhs)
		{
			x *= (int)rhs;
			y *= (int)rhs;
			return *this;
		}

		// /= operator
		inline Vector2 & Vector2::operator/=(const Vector2 & rhs)
		{
			assert(rhs.x);
			assert(rhs.y);
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}
		inline Vector2 & Vector2::operator/=(int rhs)
		{
			assert(rhs);
			x /= rhs;
			y /= rhs;
			return *this;
		}
		inline Vector2 & Vector2::operator/=(float rhs)
		{
			assert(rhs);
			x /= (int)rhs;
			y /= (int)rhs;
			return *this;
		}
	}
}
#endif