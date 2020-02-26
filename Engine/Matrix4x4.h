#ifndef __MATRIX4_H
#define __MATRIX4_H
#include "Vector4.h"

namespace Engine
{
	namespace Matrix
	{
		class Matrix
		{
		public:
			float m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
			Matrix() {};

			inline Matrix(
				float i_11, float i_12, float i_13, float i_14,
				float i_21, float i_22, float i_23, float i_24,
				float i_31, float i_32, float i_33, float i_34,
				float i_41, float i_42, float i_43, float i_44)
			{
				m11 = i_11;
				m12 = i_12;
				m13 = i_13;
				m14 = i_14;

				m21 = i_21;
				m22 = i_22;
				m23 = i_23;
				m24 = i_24;

				m31 = i_31;
				m32 = i_32;
				m33 = i_33;
				m34 = i_34;

				m41 = i_41;
				m42 = i_42;
				m43 = i_43;
				m44 = i_44;
			};

			inline Matrix Transpose();

			inline Matrix Inverse();
		};

		inline Matrix CreateIdentity();
		inline Matrix CreateYRot(float rad);
		inline Matrix CreateXRot(float rad);
		inline Matrix CreateZRot(float rad);

		inline Matrix CreateScale(float scale);
		inline Matrix CreateScale(float scaleX, float scaleY, float scaleZ);
		inline Matrix CreateScaleX(float scale);
		inline Matrix CreateScaleY(float scale);
		inline Matrix CreateScaleZ(float scale);

		inline Matrix CreateTranslate(float x, float y, float z);
		inline Matrix CreateTranslate(Engine::Math::Vector2);


		inline Matrix operator*(const Matrix & lhs, const Matrix & rhs);
		inline Engine::Math::Vector4 operator*(const Matrix & lhs, Engine::Math::Vector4 rhs);
		inline Engine::Math::Vector4 operator*(Engine::Math::Vector4 lhs, const Matrix & rhs);
		inline Matrix operator+(const Matrix & lhs, const Matrix & rhs);
		inline Matrix operator-(const Matrix & lhs, const Matrix & rhs);
		inline Matrix operator*(const Matrix & lhs, float scale);
		inline Matrix operator*(float scale, const Matrix & lhs);
		inline Matrix operator/(const Matrix & lhs, float scale);
	}
}

#include "Matrix4x4-inl.h"
#endif