#ifndef __VECTOR4_H
#define __VECTOR4_H

#include <xmmintrin.h>
#include <smmintrin.h>

namespace Engine
{
	namespace Math
	{
		class Vector4
		{
		public:
			float x, y, z, w;
			Vector4() {}

			inline Vector4(float nx, float ny, float nz, float nw)
			{
				x = nx;
				y = ny;
				z = nz;
				w = nw;
			}

			inline Vector4(__m128 m)
			{
				m_vec = m;
			}

			inline Vector4(const Vector4 & other)
			{
				x = other.x;
				y = other.y;
				z = other.z;
				w = other.w;
			}

			inline Vector4 & operator+=(const Vector4 & rhs);
			inline Vector4 & operator-=(const Vector4 & rhs);

			inline Vector4 & operator*=(const Vector4 & rhs);
			inline Vector4 & operator*=(int rhs);
			inline Vector4 & operator*=(float rhs);

			inline Vector4 & operator/=(const Vector4 & rhs);
			inline Vector4 & operator/=(int rhs);
			inline Vector4 & operator/=(float rhs);

			inline float Length() const;

			inline void Normalize();

			union
			{
				struct { float x, y, z, w; };
				__m128 m_vec;
			};
		private:
		};

		inline bool operator==(const Vector4 & lhs, const Vector4 & rhs);
		inline bool operator!=(const Vector4 & lhs, const Vector4 & rhs);

		inline Vector4 operator+(const Vector4 & lhs, const Vector4 & rhs);
		inline Vector4 operator-(const Vector4 & lhs, const Vector4 & rhs);

		inline Vector4 operator*(const Vector4 & lhs, const Vector4 & rhs);
		inline Vector4 operator*(const Vector4 & lhs, int rhs);
		inline Vector4 operator*(const Vector4 & lhs, float rhs);

		inline Vector4 operator/(const Vector4 & lhs, const Vector4 & rhs);
		inline Vector4 operator/(const Vector4 & lhs, int rhs);
		inline Vector4 operator/(const Vector4 & lhs, float rhs);

		inline float Dot(const Vector4 & lhs, const Vector4 & rhs);
	}
}

#include "Vector4-inl.h"
#endif