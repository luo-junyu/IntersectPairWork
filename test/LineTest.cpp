#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../IntersectPairWork/src/intersect.h"
#include "../IntersectPairWork/src/line.h"
#include "../IntersectPairWork/src/circle.h"
#include "../IntersectPairWork/src/errorhandler.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LineTest
{
	TEST_CLASS(LineAndLine)
	{
	public:
		TEST_METHOD(LineAndLine_1)
		{
			vector<struct Position> res;
			Line line1(1, 1, 1, 0);
			Line line2(0, 0, 0, -1);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndLine_2)
		{
			// same line

			vector<struct Position> res;
			Line line1(1, 1, 1, 0);
			Line line2(1, 2, 1, 3);
			ErrorType err = line2.lineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}
	};
	TEST_CLASS(LineAndRayLine)
	{
	public:
		TEST_METHOD(LineAndRayLine_1)
		{
			vector<struct Position> res;
			Line line1(1,1,1,0);
			rayLine line2(0,0,0,-1);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndRayLine_2)
		{
			vector<struct Position> res;
			Line line1(1, 1, 1, 0);
			rayLine line2(2, 2, 2, 3);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndRayLine_3)
		{
			vector<struct Position> res;
			Line line1(1, 1, 0, 1);
			rayLine line2(0, 2, 0, 3);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndRayLine_4)
		{
			vector<struct Position> res;
			Line line1(1, 1, 0, 1);
			rayLine line2(0, -2, 0, -3);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndRayLine_5)
		{
			// intersect

			vector<struct Position> res;
			Line line1(1, 0, 0, 1);
			rayLine line2(0, 0, 1, 1);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(LineAndRayLine_6)
		{
			// intersect on line

			vector<struct Position> res;
			Line line1(0, 0, 0, 1);
			rayLine line2(0, 0, 1, 1);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(LineAndRayLine_7)
		{
			// eps test

			vector<struct Position> res;
			Line line1(0, 0, 0, 1);
			rayLine line2(0, 0, 1, 1);
			line2.x_end1_sub_eps = -eps / 10;
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(LineAndRayLine_8)
		{
			// eps test

			vector<struct Position> res;
			Line line1(0, 0, 0, 1);
			rayLine line2(0, 0, 1, 1);
			line2.x_end1_sub_eps = eps * 10;
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndRayLine_9)
		{
			// eps test
			vector<struct Position> res;
			Line line1(1, 1, 1, 0);
			rayLine line2(1, 2, 1, 3);
			ErrorType err = line2.lineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}
	};

	TEST_CLASS(LineAndSegLine)
	{
	public:
		TEST_METHOD(LineAndSegLine_1)
		{
			vector<struct Position> res;
			Line line1(0, 0, 1, 1);
			segLine line2(0, 1, 1, 0);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
			vector<struct Position> res2;
			segLine line3(1, 0, 0, 1);
			line3.lineIntersect(line1, res2);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(LineAndSegLine_2)
		{
			vector<struct Position> res;
			Line line1(0, 0, 1, 1);
			segLine line2(1, 1, 1, 0);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
			vector<struct Position> res2;
			segLine line3(1, 0, 1, 1);
			line3.lineIntersect(line1, res2);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(LineAndSegLine_3)
		{
			vector<struct Position> res;
			Line line1(0, 0, 1, 1);
			segLine line2(1, 0, 2, 0);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndSegLine_4)
		{
			vector<struct Position> res;
			Line line1(0, 0, 1, 1);
			segLine line2(0, 0, 0, 1);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(LineAndSegLine_5)
		{
			vector<struct Position> res;
			Line line1(0, 3, 1, 3);
			segLine line2(0, 0, 0, 1);
			line2.lineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(LineAndSegLine_6)
		{
			vector<struct Position> res;
			Line line1(0, 1, 1, 1);
			segLine line2(0, 1, 1, 1);
			ErrorType err = line2.lineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}
	};


	TEST_CLASS(rayLineAndrayLine)
	{
	public:
		TEST_METHOD(RayLineAndRayLine_1)
		{
			vector<struct Position> res;
			rayLine line1(1, 1, 2, 2);
			rayLine line2(-1, 1, -2, 2);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndRayLine_2)
		{
			vector<struct Position> res;
			rayLine line1(1, 1, 2, 2);
			rayLine line2(-1, -1, -2, -2);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndRayLine_3)
		{
			rayLine line1(0, 0, 2, 2);
			/* // TODO: 添加射线平行的情况
			rayLine line2(0, 0, -1, -1);
			vector<struct Position> res;
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);*/

			rayLine line3(0, 0, -1, 1);
			vector<struct Position> res2;
			line3.rayLineIntersect(line1, res2);
			Assert::IsTrue(res2.size() == 1);

			rayLine line4(0, 0, 1, -1);
			vector<struct Position> res3;
			line4.rayLineIntersect(line1, res3);
			Assert::IsTrue(res3.size() == 1);
		}

		TEST_METHOD(RayLineAndRayLine_4)
		{
			vector<struct Position> res;
			rayLine line1(1, 1, 2, 2);
			rayLine line2(5, 1, 5, 0);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndRayLine_5)
		{
			vector<struct Position> res;
			rayLine line1(1, 1, 2, 2);
			rayLine line2(5, 1, 5, 3);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(RayLineAndRayLine_6)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			rayLine line2(0, 0, -1, -1);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(RayLineAndRayLine_7)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			rayLine line2(1, 1, -1, -1);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndRayLine_8)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			rayLine line2(-1, -1, -2, -2);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}
	};

	TEST_CLASS(rayLineAndsegLine)
	{
		TEST_METHOD(RayLineAndSegLine_1)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			segLine line2(1, 0, 0, 1);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(RayLineAndSegLine_2)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			segLine line2(1, 0, 2, 0);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndSegLine_3)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			segLine line2(2, -1, 2, 0);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndSegLine_4)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 0, 1);
			segLine line2(-1, 2, 1, 2);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(RayLineAndSegLine_5)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 0, 1);
			segLine line2(-1, -2, 1, -2);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndSegLine_6)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 0, 1);
			segLine line2(-1, -2, 1, -2);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(RayLineAndSegLine_7)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			segLine line2(-1, -1, 0, 0);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(RayLineAndSegLine_8)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, -1, 1);
			segLine line2(0, 0, 1, -1);
			line2.rayLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(RayLineAndSegLine_9)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, -1, 1);
			segLine line2(-1, 1, 1, -1);
			ErrorType err = line2.rayLineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}

		TEST_METHOD(RayLineAndSegLine_10)
		{
			vector<struct Position> res;
			rayLine line1(0, 0, 1, 1);
			segLine line2(-1, -1, 1, 1);
			ErrorType err = line2.rayLineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}

	};

	TEST_CLASS(segLineAndsegLine) {
		TEST_METHOD(SegLineAndSegLine_1)
		{
			vector<struct Position> res;
			segLine line1(0, 0, 1, 1);
			segLine line2(-1, -1, 0, 0);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(SegLineAndSegLine_2)
		{
			vector<struct Position> res;
			segLine line1(-1, -1, 0, 0);
			segLine line2(0, 0, 1, 1);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(SegLineAndSegLine_3)
		{
			vector<struct Position> res;
			segLine line1(0, 0, 2, 2);
			segLine line2(0, 0, 1, 1);
			ErrorType err = line2.segLineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}

		TEST_METHOD(SegLineAndSegLine_4)
		{
			vector<struct Position> res;
			segLine line1(0, -1, 0, 0);
			segLine line2(0, 0, 0, 1);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(SegLineAndSegLine_5)
		{
			vector<struct Position> res;
			segLine line1(0, 0, 0, 1);
			segLine line2(0, -1, 0, 0);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 1);
		}

		TEST_METHOD(SegLineAndSegLine_6)
		{
			vector<struct Position> res;
			segLine line1(0, 0, 0, 1);
			segLine line2(5, -1, 5, 0);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(SegLineAndSegLine_7)
		{
			vector<struct Position> res;
			segLine line1(0, 1, 0, 2);
			segLine line2(1, 0, 2, 0);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(SegLineAndSegLine_8)
		{
			vector<struct Position> res;
			segLine line1(0, 0, 0, 1);
			segLine line2(0, -1, 0, -2);
			line2.segLineIntersect(line1, res);
			Assert::IsTrue(res.size() == 0);
		}

		TEST_METHOD(SegLineAndSegLine_9)
		{
			vector<struct Position> res;
			segLine line1(0, 0, 0, 5);
			segLine line2(0, -1, 0, 2);
			ErrorType err = line2.segLineIntersect(line1, res);
			Assert::IsTrue(err == ErrorType::SameLine);
		}

	};

}
