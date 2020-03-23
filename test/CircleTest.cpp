#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../IntersectPairWork/src/intersect.h"
#include "../IntersectPairWork/src/line.h"
#include "../IntersectPairWork/src/circle.h"
#include "../IntersectPairWork/src/errorhandler.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircleTest
{
	TEST_CLASS(CircleAndCircle)
	{
	public:

		TEST_METHOD(CircleAndCircle_1)
		{
			vector<struct Position> res;
			Circle c1(0,0,2);
			Circle c2(0, 0, 3);
			c1.circleIntersect(c2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndCircle_2)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Circle c2(1, 1, 1);
			c1.circleIntersect(c2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndCircle_3)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Circle c2(10, 0, 5);
			c1.circleIntersect(c2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndCircle_4)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Circle c2(8, 0, 5);
			c1.circleIntersect(c2, res);
			Assert::IsTrue(res.size() == 2);
		}

		TEST_METHOD(CircleAndCircle_5)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Circle c2(0, 0, 5);
			ErrorType err = c1.circleIntersect(c2, res);
			Assert::IsTrue(err == ErrorType::SameCircle);
		}

	};


	TEST_CLASS(CircleAndLine)
	{
	public:
		TEST_METHOD(CircleAndLine_1)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(10, 0, 10, 5);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndLine_2)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(0, 10, 5, 10);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndLine_3)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(0, 5, 5, 5);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndLine_4)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(5, 0, 5, 5);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndLine_5)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(3, 0, 3, 5);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}

		TEST_METHOD(CircleAndLine_6)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(0, 3, 5, 3);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}

		TEST_METHOD(CircleAndLine_7)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			Line l2(0, 0, 3, 3);
			c1.lineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}

	};


	TEST_CLASS(CircleAndRayLine)
	{
	public:
		TEST_METHOD(CircleAndRayLine_1)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(10, 0, 10, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndRayLine_2)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(10, 10, 20, 20);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndRayLine_3)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(0, 5, 5, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndRayLine_4)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(-5, 5, 5, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndRayLine_5)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(5, 0, 5, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndRayLine_6)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(5, -5, 5, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndRayLine_7)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(3, -5, 3, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}

		TEST_METHOD(CircleAndRayLine_8)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(3, 0, 3, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndRayLine_9)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(3, 0, 3, -5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndRayLine_10)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			rayLine l2(0, 0, 5, 5);
			c1.rayLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

	};

	TEST_CLASS(CircleAndSegLine)
	{
	public:
		TEST_METHOD(CircleAndSegLine_1)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(10, 0, 10, 5);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndSegLine_2)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(0, 10, 5, 10);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(CircleAndSegLine_3)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(5, 0, 5, 10);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndSegLine_4)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(0, 5, 5, 5);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndSegLine_5)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(0, 3, 5, 3);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(CircleAndSegLine_6)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(-50, 3, 50, 3);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}

		TEST_METHOD(CircleAndSegLine_7)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(0, -50, 0, 50);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}

		TEST_METHOD(CircleAndSegLine_8)
		{
			vector<struct Position> res;
			Circle c1(0, 0, 5);
			segLine l2(10, 10, -10, -10);
			c1.segLineIntersect(l2, res);
			Assert::IsTrue(res.size() == 2);
		}
	};



}