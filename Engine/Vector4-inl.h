#ifndef __Vec4Inl
#define __Vec4Inl

#include "assert.h"
#include "math.h"
#include "Vector4.h"

namespace Engine
{
	namespace Math
	{
		// Dot product
		inline float Dot(const Vector4 & lhs, const Vector4 & rhs)
		{
			__m128 vec0 = { lhs.x, lhs.y, lhs.z, lhs.w };
			__m128 vec1 = { rhs.x, rhs.y, rhs.z, rhs.w };

			__m128 vec2 = _mm_dp_ps(vec0, vec1, 0xf1);

			float dot = _mm_cvtss_f32(vec2);

			return dot;
		}

		// Length
		inline float Vector4::Length() const
		{
			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(m_vec, m_vec, 0xf1)));
		}

		inline void Vector4::Normalize()
		{
			if (Length() == 0.0f)
			{
				return;
			}
			else
			{
				m_vec = _mm_mul_ps(m_vec, _mm_set1_ps(Length()));
			}
		}

		// Add operator
		inline Vector4 operator+(const Vector4 & lhs, const Vector4 & rhs)
		{
			return _mm_add_ps(lhs.m_vec, rhs.m_vec);
		}

		// Minus operator
		inline Vector4 operator-(const Vector4 & lhs, const Vector4 & rhs)
		{
			return _mm_sub_ps(lhs.m_vec, rhs.m_vec);
		}

		// Multiplication operators
		inline Vector4 operator*(const Vector4 & lhs, const Vector4 & rhs)
		{
			return _mm_mul_ps(lhs.m_vec, rhs.m_vec);
		}
		inline Vector4 operator*(const Vector4 & lhs, int rhs)
		{
			return _mm_mul_ps(lhs.m_vec, _mm_set1_ps(rhs));
		}
		inline Vector4 operator*(const Vector4 & lhs, float rhs)
		{
			return _mm_mul_ps(lhs.m_vec, _mm_set1_ps(rhs));
		}

		// Divide operator
		inline Vector4 operator/(const Vector4 & lhs, const Vector4 & rhs)
		{
			return _mm_div_ps(lhs.m_vec, rhs.m_vec);
		}
		inline Vector4 operator/(const Vector4 & lhs, int rhs)
		{
			return _mm_div_ps(lhs.m_vec, _mm_set1_ps(rhs));
		}
		inline Vector4 operator/(const Vector4 & lhs, float rhs)
		{
			return _mm_div_ps(lhs.m_vec, _mm_set1_ps(rhs));
		}

		// == operator
		inline bool operator==(const Vector4 & lhs, const Vector4 & rhs)
		{
			return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
		}
		// != operator
		inline bool operator!=(const Vector4 & lhs, const Vector4 & rhs)
		{
			return !(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
		}

		// += operator
		inline Vector4 & Vector4::operator+=(const Vector4 & rhs)
		{
			m_vec = _mm_add_ps(m_vec, rhs.m_vec);
			return *this;
		}
		// -= operator
		inline Vector4 & Vector4::operator-=(const Vector4 & rhs)
		{
			m_vec = _mm_sub_ps(m_vec, rhs.m_vec);
			return *this;
		}

		// *= operator
		inline Vector4 & Vector4::operator*=(const Vector4 & rhs)
		{
			m_vec = _mm_mul_ps(m_vec, rhs.m_vec);
			return *this;
		}
		inline Vector4 & Vector4::operator*=(int rhs)
		{
			m_vec = _mm_mul_ps(m_vec, _mm_set1_ps(rhs));
			return *this;
		}
		inline Vector4 & Vector4::operator*=(float rhs)
		{
			m_vec = _mm_mul_ps(m_vec, _mm_set1_ps(rhs));
			return *this;
		}

		// /= operator
		inline Vector4 & Vector4::operator/=(const Vector4 & rhs)
		{
			m_vec = _mm_div_ps(m_vec, rhs.m_vec);
			return *this;
		}
		inline Vector4 & Vector4::operator/=(int rhs)
		{
			m_vec = _mm_div_ps(m_vec, _mm_set1_ps(rhs));
			return *this;
		}
		inline Vector4 & Vector4::operator/=(float rhs)
		{
			m_vec = _mm_div_ps(m_vec, _mm_set1_ps(rhs));
			return *this;
		}
	}
}
#endif