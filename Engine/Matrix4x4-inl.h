#ifndef __Matrix4x4Inl
#define __Matrix4x4Inl

#include "assert.h"
#include "math.h"
#include "Matrix4x4.h"

namespace Engine
{
	namespace Matrix
	{
		inline Matrix CreateIdentity()
		{
			return Matrix(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateZRot(float rad)
		{
			return Matrix(
				static_cast<float>(cos(rad)), static_cast<float>(-sin(rad)), 0, 0,
				static_cast<float>(sin(rad)), static_cast<float>(cos(rad)), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateXRot(float rad)
		{
			return Matrix(
				1, 0, 0, 0,
				0, static_cast<float>(cos(rad)), static_cast<float>(-sin(rad)), 0,
				0, static_cast<float>(sin(rad)), static_cast<float>(cos(rad)), 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateYRot(float rad)
		{
			return Matrix(
				static_cast<float>(cos(rad)), 0, static_cast<float>(sin(rad)), 0,
				0, 1, 0, 0,
				static_cast<float>(-sin(rad)), 0, static_cast<float>(cos(rad)), 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateScale(float scale)
		{
			return Matrix(
				scale, 0, 0, 0,
				0, scale, 0, 0,
				0, 0, scale, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateScale(float scaleX, float scaleY, float scaleZ)
		{
			return Matrix(
				scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, scaleZ, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateScaleX(float scale)
		{
			return Matrix(
				scale, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateScaleY(float scale)
		{
			return Matrix(
				1, 0, 0, 0,
				0, scale, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateScaleZ(float scale)
		{
			return Matrix(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, scale, 0,
				0, 0, 0, 1);
		}

		inline Matrix CreateTranslate(float x, float y, float z)
		{
			return Matrix(
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1);
		}

		inline Matrix CreateTranslate(Engine::Math::Vector2 vec)
		{
			return Matrix(
				1, 0, 0, vec.x,
				0, 1, 0, vec.y,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		inline Matrix Matrix::Transpose()
		{
			return Matrix(
				m11, m21, m31, m41,
				m12, m22, m32, m42,
				m13, m23, m33, m43,
				m14, m24, m34, m44);
		}

		inline Matrix Matrix::Inverse()
		{
			/*
			__m128 temp = { 0.0f };
			__m128 row0, row1, row2, row3;
			__m128 minor0, minor1, minor2, minor3;

			temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m11)), reinterpret_cast<const __m64 *>(&m21));
			row1 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m31)), reinterpret_cast<const __m64 *>(&m41));
			row0 = _mm_shuffle_ps(temp, row1, 0x88);
			row1 = _mm_shuffle_ps(row1, temp, 0xDD);
			temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m13)), reinterpret_cast<const __m64 *>(&m23));
			row3 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m33)), reinterpret_cast<const __m64 *>(&m43));
			row2 = _mm_shuffle_ps(temp, row3, 0x88);
			row3 = _mm_shuffle_ps(row3, temp, 0xDD);

			// -----------------------------------------------
			temp = _mm_mul_ps(row2, row3);
			temp = _mm_shuffle_ps(temp, temp, 0xB1);
			minor0 = _mm_mul_ps(row1, temp);
			minor1 = _mm_mul_ps(row0, temp);
			temp = _mm_shuffle_ps(temp, temp, 0x4E);
			minor0 = _mm_sub_ps(_mm_mul_ps(row1, temp), minor0);
			minor1 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor1);
			minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

			// -----------------------------------------------
			temp = _mm_mul_ps(row1, row2);
			temp = _mm_shuffle_ps(temp, temp, 0xB1);
			minor0 = _mm_add_ps(_mm_mul_ps(row3, temp), minor0);
			minor3 = _mm_mul_ps(row0, temp);
			temp = _mm_shuffle_ps(temp, temp, 0x4E);
			minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, temp));
			minor3 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor3);
			minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

			// -----------------------------------------------
			temp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
			temp = _mm_shuffle_ps(temp, temp, 0xB1);
			row2 = _mm_shuffle_ps(row2, row2, 0x4E);
			minor0 = _mm_add_ps(_mm_mul_ps(row2, temp), minor0);
			minor2 = _mm_mul_ps(row0, temp);
			temp = _mm_shuffle_ps(temp, temp, 0x4E);
			minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, temp));
			minor2 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor2);
			minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

			// -----------------------------------------------
			temp = _mm_mul_ps(row0, row1);
			temp = _mm_shuffle_ps(temp, temp, 0xB1);
			minor2 = _mm_add_ps(_mm_mul_ps(row3, temp), minor2);
			minor3 = _mm_sub_ps(_mm_mul_ps(row2, temp), minor3);
			temp = _mm_shuffle_ps(temp, temp, 0x4E);
			minor2 = _mm_sub_ps(_mm_mul_ps(row3, temp), minor2);
			minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, temp));

			// -----------------------------------------------
			temp = _mm_mul_ps(row0, row3);
			temp = _mm_shuffle_ps(temp, temp, 0xB1);
			minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, temp));
			minor2 = _mm_add_ps(_mm_mul_ps(row1, temp), minor2);
			temp = _mm_shuffle_ps(temp, temp, 0x4E);
			minor1 = _mm_add_ps(_mm_mul_ps(row2, temp), minor1);
			minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, temp));

			// -----------------------------------------------
			temp = _mm_mul_ps(row0, row2);
			temp = _mm_shuffle_ps(temp, temp, 0xB1);
			minor1 = _mm_add_ps(_mm_mul_ps(row3, temp), minor1);
			minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, temp));
			temp = _mm_shuffle_ps(temp, temp, 0x4E);
			minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, temp));
			minor3 = _mm_add_ps(_mm_mul_ps(row1, temp), minor3);

			// -----------------------------------------------
			__m128 det;

			det = _mm_mul_ps(row0, minor0);
			det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
			det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
			temp = _mm_rcp_ss(det);
			det = _mm_sub_ss(_mm_add_ss(temp, temp), _mm_mul_ss(det, _mm_mul_ss(temp, temp)));
			det = _mm_shuffle_ps(det, det, 0x00);

			Matrix o_out;
			minor0 = _mm_mul_ps(det, minor0);
			_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m11), minor0);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m13), minor0);

			minor1 = _mm_mul_ps(det, minor1);
			_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m21), minor1);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m23), minor1);

			minor2 = _mm_mul_ps(det, minor2);
			_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m31), minor2);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m33), minor2);

			minor3 = _mm_mul_ps(det, minor3);
			_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m41), minor3);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m43), minor3);
			return o_out;
			*/
			float det = 
				  m11 * m22 * m33 * m44 + m11 * m23 * m34 * m42 + m11 * m24 * m32 * m43
				- m11 * m24 * m33 * m42 - m11 * m23 * m32 * m44 - m11 * m22 * m34 * m43
				- m12 * m21 * m33 * m44 - m13 * m21 * m34 * m42 - m14 * m21 * m32 * m43
				+ m14 * m21 * m33 * m42 + m13 * m21 * m32 * m44 + m12 * m21 * m34 * m43
				+ m12 * m23 * m31 * m44 + m13 * m24 * m31 * m42 + m14 * m22 * m31 * m43
				- m14 * m23 * m31 * m42 - m13 * m22 * m31 * m44 - m12 * m24 * m31 * m43
				- m12 * m23 * m34 * m41 - m13 * m24 * m32 * m41 - m14 * m22 * m33 * m41
				+ m14 * m23 * m32 * m41 + m13 * m22 * m34 * m41 + m12 * m24 * m33 * m41;

			float A11 = 
				m22 * m33 * m44 + m23 * m34 * m42 + m24 * m32 * m43 -
				m24 * m33 * m42 - m23 * m32 * m44 - m22 * m34 * m43;
			float A12 =
				m14 * m33 * m42 + m13 * m32 * m44 + m12 * m34 * m43 -
				m12 * m33 * m44 - m13 * m34 * m42 - m14 * m32 * m43;
			float A13 =
				m12 * m23 * m44 + m13 * m24 * m42 + m14 * m22 * m43 -
				m14 * m23 * m42 - m13 * m22 * m44 - m12 * m24 * m43;
			float A14 =
				m14 * m23 * m32 + m13 * m22 * m34 + m12 * m24 * m33 -
				m12 * m23 * m34 - m13 * m24 * m32 - m14 * m22 * m33;

			float A21 =
				m24 * m33 * m41 + m23 * m31 * m44 + m21 * m34 * m43 -
				m21 * m33 * m44 - m23 * m34 * m41 - m24 * m31 * m43;
			float A22 =
				m11 * m33 * m44 + m13 * m34 * m41 + m14 * m31 * m43 -
				m14 * m33 * m41 - m13 * m31 * m44 - m11 * m34 * m43;
			float A23 =
				m14 * m23 * m41 + m13 * m21 * m44 + m11 * m24 * m43 -
				m11 * m23 * m44 - m13 * m24 * m41 - m14 * m21 * m43;
			float A24 =
				m11 * m23 * m34 + m13 * m24 * m31 + m14 * m21 * m33 -
				m14 * m23 * m31 - m13 * m21 * m34 - m11 * m24 * m33;

			float A31 =
				m21 * m32 * m44 + m22 * m34 * m41 + m24 * m31 * m42 -
				m24 * m32 * m41 - m22 * m31 * m44 - m21 * m34 * m42;
			float A32 =
				m14 * m32 * m41 + m12 * m31 * m44 + m11 * m34 * m42 -
				m11 * m32 * m44 - m12 * m34 * m41 - m14 * m31 * m42;
			float A33 =
				m11 * m22 * m44 + m12 * m24 * m41 + m14 * m21 * m42 -
				m14 * m22 * m41 - m12 * m21 * m44 - m11 * m24 * m42;
			float A34 =
				m14 * m22 * m31 + m12 * m21 * m34 + m11 * m24 * m32 -
				m11 * m22 * m34 - m12 * m24 * m31 - m14 * m21 * m32;

			float A41 =
				m23 * m32 * m41 + m22 * m31 * m43 + m21 * m33 * m42 -
				m21 * m32 * m43 - m22 * m33 * m41 - m23 * m31 * m42;
			float A42 =
				m11 * m32 * m43 + m12 * m33 * m41 + m13 * m31 * m42 -
				m13 * m32 * m41 - m12 * m31 * m43 - m11 * m33 * m42;
			float A43 =
				m13 * m22 * m41 + m12 * m21 * m43 + m11 * m23 * m42 -
				m11 * m22 * m43 - m12 * m23 * m41 - m13 * m21 * m42;
			float A44 =
				m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 -
				m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;
			
			Matrix adjg(
				A11, A12, A13, A14,
				A21, A22, A23, A24,
				A31, A32, A33, A34,
				A41, A42, A43, A44			
			);

			return Matrix(
				A11 / det, A12 / det, A13 / det, A14 / det,
				A21 / det, A22 / det, A23 / det, A24 / det,
				A31 / det, A32 / det, A33 / det, A34 / det,
				A41 / det, A42 / det, A43 / det, A44 / det
			);
		}

		inline Matrix operator*(const Matrix & lhs, const Matrix & rhs)
		{
			/*/ load i_other
			__m128 row1 = _mm_load_ps(&rhs.m11);
			__m128 row2 = _mm_load_ps(&rhs.m21);
			__m128 row3 = _mm_load_ps(&rhs.m31);
			__m128 row4 = _mm_load_ps(&rhs.m41);

			__m128 acc;
			acc = _mm_mul_ps(_mm_load1_ps(&lhs.m11), row1);
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m12), row2));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m13), row3));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m14), row4));

			Matrix res;
			// write result
			_mm_storel_pi(reinterpret_cast<__m64 *>(&res.m11), acc);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&res.m13), acc);

			acc = _mm_mul_ps(_mm_load1_ps(&lhs.m21), row1);
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m22), row2));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m23), row3));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m24), row4));

			// write result
			_mm_storel_pi(reinterpret_cast<__m64 *>(&res.m21), acc);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&res.m23), acc);

			acc = _mm_mul_ps(_mm_load1_ps(&lhs.m31), row1);
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m32), row2));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m33), row3));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m34), row4));

			// write result
			_mm_storel_pi(reinterpret_cast<__m64 *>(&res.m31), acc);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&res.m33), acc);

			acc = _mm_mul_ps(_mm_load1_ps(&lhs.m41), row1);
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m42), row2));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m43), row3));
			acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&lhs.m44), row4));

			// write result
			_mm_storel_pi(reinterpret_cast<__m64 *>(&res.m41), acc);
			_mm_storeh_pi(reinterpret_cast<__m64 *>(&res.m43), acc);

			return res;
						
			/*///Old matrix mult
			return Matrix(
				lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31 + lhs.m14 * rhs.m41,
				lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32 + lhs.m14 * rhs.m42,
				lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33 + lhs.m14 * rhs.m43,
				lhs.m11 * rhs.m14 + lhs.m12 * rhs.m24 + lhs.m13 * rhs.m34 + lhs.m14 * rhs.m44,

				lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31 + lhs.m24 * rhs.m41,
				lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32 + lhs.m24 * rhs.m42,
				lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33 + lhs.m24 * rhs.m43,
				lhs.m21 * rhs.m14 + lhs.m22 * rhs.m24 + lhs.m23 * rhs.m34 + lhs.m24 * rhs.m44,

				lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31 + lhs.m34 * rhs.m41,
				lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32 + lhs.m34 * rhs.m42,
				lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33 + lhs.m34 * rhs.m43,
				lhs.m31 * rhs.m14 + lhs.m32 * rhs.m24 + lhs.m33 * rhs.m34 + lhs.m34 * rhs.m44,

				lhs.m41 * rhs.m11 + lhs.m42 * rhs.m21 + lhs.m43 * rhs.m31 + lhs.m44 * rhs.m41,
				lhs.m41 * rhs.m12 + lhs.m42 * rhs.m22 + lhs.m43 * rhs.m32 + lhs.m44 * rhs.m42,
				lhs.m41 * rhs.m13 + lhs.m42 * rhs.m23 + lhs.m43 * rhs.m33 + lhs.m44 * rhs.m43,
				lhs.m41 * rhs.m14 + lhs.m42 * rhs.m24 + lhs.m43 * rhs.m34 + lhs.m44 * rhs.m44);
			//*/
			/*/ failed attempt #1, was slower

			__m128 row0 = { rhs.m11, rhs.m12, rhs.m13, rhs.m14 };
			__m128 row1 = { rhs.m21, rhs.m22, rhs.m23, rhs.m24 };
			__m128 row2 = { rhs.m31, rhs.m32, rhs.m33, rhs.m34 };
			__m128 row3 = { rhs.m41, rhs.m42, rhs.m43, rhs.m44 };

			__m128 col0 = { rhs.m11, rhs.m21, rhs.m31, rhs.m41 };
			__m128 col1 = { rhs.m12, rhs.m22, rhs.m32, rhs.m42 };
			__m128 col2 = { rhs.m13, rhs.m23, rhs.m33, rhs.m43 };
			__m128 col3 = { rhs.m14, rhs.m24, rhs.m34, rhs.m44 };



			__m128 vec11 = _mm_mul_ps(row0, col0);
			vec11 = _mm_hadd_ps(vec11, vec11);
			vec11 = _mm_hadd_ps(vec11, vec11);

			__m128 vec12 = _mm_mul_ps(row0, col1);
			vec12 = _mm_hadd_ps(vec12, vec12);
			vec12 = _mm_hadd_ps(vec12, vec12);

			__m128 vec13 = _mm_mul_ps(row0, col2);
			vec13 = _mm_hadd_ps(vec13, vec13);
			vec13 = _mm_hadd_ps(vec13, vec13);

			__m128 vec14 = _mm_mul_ps(row0, col3);
			vec14 = _mm_hadd_ps(vec14, vec14);
			vec14 = _mm_hadd_ps(vec14, vec14);


			__m128 vec21 = _mm_mul_ps(row1, col0);
			vec21 = _mm_hadd_ps(vec21, vec21);
			vec21 = _mm_hadd_ps(vec21, vec21);

			__m128 vec22 = _mm_mul_ps(row1, col1);
			vec22 = _mm_hadd_ps(vec22, vec22);
			vec22 = _mm_hadd_ps(vec22, vec22);

			__m128 vec23 = _mm_mul_ps(row1, col2);
			vec23 = _mm_hadd_ps(vec23, vec23);
			vec23 = _mm_hadd_ps(vec23, vec23);

			__m128 vec24 = _mm_mul_ps(row1, col3);
			vec24 = _mm_hadd_ps(vec24, vec24);
			vec24 = _mm_hadd_ps(vec24, vec24);


			__m128 vec31 = _mm_mul_ps(row2, col0);
			vec31 = _mm_hadd_ps(vec31, vec31);
			vec31 = _mm_hadd_ps(vec31, vec31);

			__m128 vec32 = _mm_mul_ps(row2, col1);
			vec32 = _mm_hadd_ps(vec32, vec32);
			vec32 = _mm_hadd_ps(vec32, vec32);

			__m128 vec33 = _mm_mul_ps(row2, col2);
			vec33 = _mm_hadd_ps(vec33, vec33);
			vec33 = _mm_hadd_ps(vec33, vec33);

			__m128 vec34 = _mm_mul_ps(row2, col3);
			vec34 = _mm_hadd_ps(vec34, vec34);
			vec34 = _mm_hadd_ps(vec34, vec34);


			__m128 vec41 = _mm_mul_ps(row3, col0);
			vec41 = _mm_hadd_ps(vec41, vec41);
			vec41 = _mm_hadd_ps(vec41, vec41);

			__m128 vec42 = _mm_mul_ps(row3, col1);
			vec42 = _mm_hadd_ps(vec42, vec42);
			vec42 = _mm_hadd_ps(vec42, vec42);

			__m128 vec43 = _mm_mul_ps(row3, col2);
			vec43 = _mm_hadd_ps(vec43, vec43);
			vec43 = _mm_hadd_ps(vec43, vec43);

			__m128 vec44 = _mm_mul_ps(row3, col3);
			vec44 = _mm_hadd_ps(vec44, vec44);
			vec44 = _mm_hadd_ps(vec44, vec44);

			return  Matrix(
				_mm_cvtss_f32(vec11), _mm_cvtss_f32(vec12), _mm_cvtss_f32(vec13), _mm_cvtss_f32(vec14),
				_mm_cvtss_f32(vec21), _mm_cvtss_f32(vec22), _mm_cvtss_f32(vec23), _mm_cvtss_f32(vec24),
				_mm_cvtss_f32(vec31), _mm_cvtss_f32(vec32), _mm_cvtss_f32(vec33), _mm_cvtss_f32(vec34),
				_mm_cvtss_f32(vec41), _mm_cvtss_f32(vec42), _mm_cvtss_f32(vec43), _mm_cvtss_f32(vec44));
			//*/

		}
		inline Engine::Math::Vector4 operator*(const Matrix & lhs, Engine::Math::Vector4 rhs)
		{
			return Engine::Math::Vector4(
				lhs.m11 * rhs.x + lhs.m12 * rhs.y + lhs.m13 * rhs.z + lhs.m14 * rhs.w,
				lhs.m21 * rhs.x + lhs.m22 * rhs.y + lhs.m23 * rhs.z + lhs.m24 * rhs.w,
				lhs.m31 * rhs.x + lhs.m32 * rhs.y + lhs.m33 * rhs.z + lhs.m34 * rhs.w,
				lhs.m41 * rhs.x + lhs.m42 * rhs.y + lhs.m43 * rhs.z + lhs.m44 * rhs.w
			);
		}
		inline Engine::Math::Vector4 operator*(Engine::Math::Vector4 lhs, const Matrix & rhs)
		{
			return rhs * lhs;
		}

		inline Matrix operator+(const Matrix & lhs, const Matrix & rhs)
		{
			return Matrix(
				lhs.m11 + rhs.m11, lhs.m12 + rhs.m12, lhs.m13 + rhs.m13, lhs.m14 + rhs.m14,
				lhs.m21 + rhs.m21, lhs.m22 + rhs.m22, lhs.m23 + rhs.m23, lhs.m24 + rhs.m24,
				lhs.m31 + rhs.m31, lhs.m32 + rhs.m32, lhs.m33 + rhs.m33, lhs.m34 + rhs.m34,
				lhs.m41 + rhs.m41, lhs.m42 + rhs.m42, lhs.m43 + rhs.m43, lhs.m44 + rhs.m44
				);
		}

		inline Matrix operator-(const Matrix & lhs, const Matrix & rhs)
		{
			return Matrix(
				lhs.m11 - rhs.m11, lhs.m12 - rhs.m12, lhs.m13 - rhs.m13, lhs.m14 - rhs.m14,
				lhs.m21 - rhs.m21, lhs.m22 - rhs.m22, lhs.m23 - rhs.m23, lhs.m24 - rhs.m24,
				lhs.m31 - rhs.m31, lhs.m32 - rhs.m32, lhs.m33 - rhs.m33, lhs.m34 - rhs.m34,
				lhs.m41 - rhs.m41, lhs.m42 - rhs.m42, lhs.m43 - rhs.m43, lhs.m44 - rhs.m44
				);
		}

		inline Matrix operator*(const Matrix & lhs, float scale)
		{
			return Matrix(
				lhs.m11 * scale, lhs.m12 * scale, lhs.m13 * scale, lhs.m14 * scale,
				lhs.m21 * scale, lhs.m22 * scale, lhs.m23 * scale, lhs.m24 * scale,
				lhs.m31 * scale, lhs.m32 * scale, lhs.m33 * scale, lhs.m34 * scale,
				lhs.m41 * scale, lhs.m42 * scale, lhs.m43 * scale, lhs.m44 * scale
				);
		}

		inline Matrix operator*(float scale, const Matrix & lhs)
		{
			return lhs * scale;
		}

		inline Matrix operator/(const Matrix & lhs, float scale)
		{
			return Matrix(
				lhs.m11 / scale, lhs.m12 / scale, lhs.m13 / scale, lhs.m14 / scale,
				lhs.m21 / scale, lhs.m22 / scale, lhs.m23 / scale, lhs.m24 / scale,
				lhs.m31 / scale, lhs.m32 / scale, lhs.m33 / scale, lhs.m34 / scale,
				lhs.m41 / scale, lhs.m42 / scale, lhs.m43 / scale, lhs.m44 / scale
				);
		}
	}
}
#endif