#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Engine/Math/Vector2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine::Math;

namespace UnitTest
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestInit)
		{
			// TODO: Your test code here
			const Vector2 vec2(1, 2);
			Assert::AreEqual(vec2.x,1);
			Assert::AreEqual(vec2.y, 2);
		}

		TEST_METHOD(TestCopyInit)
		{
			// TODO: Your test code here
			const Vector2 vec2(1, 2);
			Vector2 copyVec(vec2);
			Assert::AreEqual(copyVec.x, 1);
			Assert::AreEqual(copyVec.y, 2);
		}

		TEST_METHOD(TestPlusEquals)
		{
			// TODO: Your test code here
			const Vector2 vec1(1, 2);
			Vector2 vec2(3, 4);
			vec2 += vec1;
			Assert::AreEqual(vec2.x, 4);
			Assert::AreEqual(vec2.y, 6);
		}

		TEST_METHOD(TestMinusEquals)
		{
			// TODO: Your test code here
			const Vector2 vec1(1, 2);
			Vector2 vec2(3, 4);
			vec2 -= vec1;
			Assert::AreEqual(vec2.x, 2);
			Assert::AreEqual(vec2.y, 2);
		}

		TEST_METHOD(TestTimesEquals)
		{
			// TODO: Your test code here
			const Vector2 vec1(1, 2);
			Vector2 vec2(3, 4);
			vec2 *= vec1;
			Assert::AreEqual(vec2.x, 3);
			Assert::AreEqual(vec2.y, 8);

			vec2 *= 2;
			Assert::AreEqual(vec2.x, 6);
			Assert::AreEqual(vec2.y, 16);

			vec2 *= 3.0f;
			Assert::AreEqual(vec2.x, 18);
			Assert::AreEqual(vec2.y, 48);
		}

		TEST_METHOD(TestDivideEquals)
		{
			// TODO: Your test code here
			const Vector2 vec1(2, 3);
			Vector2 vec2(16, 12);
			vec2 /= vec1;
			Assert::AreEqual(vec2.x, 8);
			Assert::AreEqual(vec2.y, 4);

			vec2 /= 2;
			Assert::AreEqual(vec2.x, 4);
			Assert::AreEqual(vec2.y, 2);

			vec2 /= 2.0f;
			Assert::AreEqual(vec2.x, 2);
			Assert::AreEqual(vec2.y, 1);
		}

		TEST_METHOD(TestLength)
		{
			// TODO: Your test code here
			const Vector2 vec2(16, 12);

			Assert::AreEqual(vec2.Length(), 20.0f);
		}

		TEST_METHOD(TestEquals)
		{
			// TODO: Your test code here
			const Vector2 vec2(16, 12);
			const Vector2 vec1(11, 12);

			Assert::IsFalse(vec2 == vec1);

			const Vector2 vec3(16, 12);
			Assert::IsTrue(vec2 == vec3);
		}

		TEST_METHOD(TestAdd)
		{
			// TODO: Your test code here
			const Vector2 vec2(1, 2);
			const Vector2 vec1(3, 4);
			Vector2 vec3 = vec1 + vec2;
			Assert::AreEqual(vec3.x, 4);
			Assert::AreEqual(vec3.y, 6);
		}

		TEST_METHOD(TestSubtract)
		{
			// TODO: Your test code here
			const Vector2 vec2(1, 2);
			const Vector2 vec1(3, 4);
			Vector2 vec3 = vec2 - vec1;
			Assert::AreEqual(vec3.x, -2);
			Assert::AreEqual(vec3.y, -2);
		}

		TEST_METHOD(TestMultiply1)
		{
			// TODO: Your test code here
			const Vector2 vec2(1, 2);
			const Vector2 vec1(3, 4);
			Vector2 vec3 = vec2 * vec1;
			Assert::AreEqual(vec3.x, 3);
			Assert::AreEqual(vec3.y, 8);
		}
		TEST_METHOD(TestMultiply2)
		{
			// TODO: Your test code here
			const Vector2 vec1(1, 2);
			Vector2 vec3 = vec1 * 2;
			Assert::AreEqual(vec3.x, 2);
			Assert::AreEqual(vec3.y, 4);
		}
		TEST_METHOD(TestMultiply3)
		{
			// TODO: Your test code here
			const Vector2 vec1(1, 2);
			Vector2 vec3 = vec1 * 2.0f;
			Assert::AreEqual(vec3.x, 2);
			Assert::AreEqual(vec3.y, 4);
		}

		TEST_METHOD(TestDivide1)
		{
			// TODO: Your test code here
			const Vector2 vec2(4, 6);
			const Vector2 vec1(2, 2);
			Vector2 vec3 = vec2 / vec1;
			Assert::AreEqual(vec3.x, 2);
			Assert::AreEqual(vec3.y, 3);
		}
		TEST_METHOD(TestDivide2)
		{
			// TODO: Your test code here
			const Vector2 vec1(4, 6);
			Vector2 vec3 = vec1 / 2;
			Assert::AreEqual(vec3.x, 2);
			Assert::AreEqual(vec3.y, 3);
		}
		TEST_METHOD(TestDivide3)
		{
			// TODO: Your test code here
			const Vector2 vec1(2, 4);
			Vector2 vec3 = vec1 / 2.0f;
			Assert::AreEqual(vec3.x, 1);
			Assert::AreEqual(vec3.y, 2);
		}

		TEST_METHOD(TestDot)
		{
			// TODO: Your test code here
			const Vector2 vec2(1, 2);
			const Vector2 vec1(3, 4);
			Assert::AreEqual((float)11, Dot(vec2, vec1));
		}
	};
}