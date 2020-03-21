#include "pch.h"
#include "CppUnitTest.h"
#include "../merge/errorhandler.h"
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testlineintersect
{
	TEST_CLASS(testlineintersect)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int argc = 5;
			char* argv[5];
			argv[1] = "-i";
			argv[2] = "input.txt";
			argv[3] = "-o";
			argv[4] = "output.txt";
			ErrorType errortype = CommandError(argc, argv);
			Assert::AreEqual(int(errortype), int(ErrorType::NoError));
		}
		TEST_METHOD(TestMethod2)
		{
			int argc = 4;
			char* argv[5];
			argv[1] = "-i";
			argv[2] = "input.txt";
			argv[3] = "-o";
			argv[4] = "output.txt";
			ErrorType errortype = CommandError(argc, argv);
			Assert::AreEqual(int(errortype), int(ErrorType::CommandNum));
		}
		TEST_METHOD(TestMethod3)
		{
			int argc = 5;
			char* argv[5];
			argv[1] = "";
			argv[2] = "input.txt";
			argv[3] = "";
			argv[4] = "output.txt";
			ErrorType errortype = CommandError(argc, argv);
			Assert::AreEqual(int(errortype), int(ErrorType::CommandFormat));
		}
		TEST_METHOD(TestMethod4)
		{
			int argc = 5;
			char* argv[5];
			argv[1] = "-i";
			argv[2] = "notexistfile.txt";
			argv[3] = "-o";
			argv[4] = "output.txt";
			ErrorType errortype = CommandError(argc, argv);
			Assert::AreEqual(int(errortype), int(ErrorType::FileNotExist));
		}
		TEST_METHOD(TestMethod5)
		{
			std::ifstream file;
			file.open("empty.txt");
			ErrorType errortype = EmptyFileError(file);
			Assert::AreEqual(int(errortype), int(ErrorType::EmptyFile));
		}
		TEST_METHOD(TestMethod6)
		{
			std::ifstream file;
			file.open("notempty.txt");
			ErrorType errortype = EmptyFileError(file);
			Assert::AreEqual(int(errortype), int(ErrorType::NoError));
		}
		TEST_METHOD(TestMethod7)
		{
			std::string n = "-1";
			ErrorType errortype = NumError(n);
			Assert::AreEqual(int(errortype), int(ErrorType::NumOutOfRange));
		}
		TEST_METHOD(TestMethod8)
		{
			std::string n = "s";
			ErrorType errortype = NumError(n);
			Assert::AreEqual(int(errortype), int(ErrorType::AssertNum));
		}
		TEST_METHOD(TestMethod9)
		{
			std::string n = "1";
			ErrorType errortype = NumError(n);
			Assert::AreEqual(int(errortype), int(ErrorType::NoError));
		}
		TEST_METHOD(TestMethod10)
		{
			long long n = 5;
			int low = 1;
			int high = 6;
			ErrorType errortype = BondError(n, low, high);
			Assert::AreEqual(int(errortype), int(ErrorType::NoError));
		}
		TEST_METHOD(TestMethod11)
		{
			long long n = 5;
			int low = 1;
			int high = 2;
			ErrorType errortype = BondError(n, low, high);
			Assert::AreEqual(int(errortype), int(ErrorType::FigureOutOfRange));
		}
		TEST_METHOD(TestMethod12)
		{
			long long a = 1;
			long long b = 1;
			long long c = 1;
			long long d = 1;
			ErrorType errortype = OverlapError(a, b, c, d);
			Assert::AreEqual(int(errortype), int(ErrorType::LinePointOverlap));
		}
		TEST_METHOD(TestMethod13)
		{
			long long a = 1;
			long long b = 1;
			long long c = 1;
			long long d = 2;
			ErrorType errortype = OverlapError(a, b, c, d);
			Assert::AreEqual(int(errortype), int(ErrorType::NoError));
		}
		TEST_METHOD(TestMethod14)
		{
			std::string figure = "";
			CorrectFigure correctfigure = FigureError(figure);
			Assert::AreEqual(int(correctfigure.errortype), int(ErrorType::FigureFormat));
		}
		TEST_METHOD(TestMethod15)
		{
			std::string figure = "L 1 2 3 4";
			CorrectFigure correctfigure = FigureError(figure);
			Assert::AreEqual(int(correctfigure.errortype), int(ErrorType::NoError));
		}
	};
}
