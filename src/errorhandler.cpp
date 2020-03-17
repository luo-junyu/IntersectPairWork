#include<iostream>
#include<fstream>
#include<regex>
#include<sstream>
#include"errorhandler.h"

void CommandError(int argc, char* argv[]) {
	if (argc != 5) {
		std::cout << "命令行参数数量不正确！";
		exit(0);
	}
	else {
		std::string i = argv[1];
		std::string o = argv[3];
		if (i != "-i" || o != "-o") {
			std::cout << "命令行参数格式不正确！";
			exit(0);
		}
		else {
			struct stat buffer;
			if (stat(argv[2], &buffer) != 0) {
				std::cout << "输入文件不存在！";
				exit(0);
			}
		}
	}
}

void EmptyFileError(std::ifstream &ifile) {
	ifile.seekg(0, std::ios::end);
	if (int(ifile.tellg()) == 0) {
		std::cout << "输入文件为空！";
		exit(0);
	}
	ifile.seekg(0, std::ios::beg);
}

void NumError(std::string ntmp) {
	std::regex partten("-?[0-9]+");
	if (std::regex_match(ntmp, partten)) {
		int n;
		n = atoi(ntmp.c_str());
		if (n <= 0 || n > 500000) {
			std::cout << "n超过范围！";
			exit(0);
		}
	}
	else {
		std::cout << "n必须为数字！";
		exit(0);
	}
}

void BondError(long long num, int low, int high) {
	if (num > high || num < low) {
		std::cout << "图形参数超过范围！";
		exit(0);
	}
}

void OverlapError(long long a, long long b, long long c, long long d) {
	if (a == c && b == d) {
		std::cout << "线两点重合！";
		exit(0);
	}
}

Figure FigureError(std::string figuretmp) {
	std::regex partten("(L -?[0-9]+ -?[0-9]+ -?[0-9]+ -?[0-9]+)|(R -?[0-9]+ -?[0-9]+ -?[0-9]+ -?[0-9]+)|(S -?[0-9]+ -?[0-9]+ -?[0-9]+ -?[0-9]+)|(C -?[0-9]+ -?[0-9]+ -?[0-9]+)");
	if (std::regex_match(figuretmp, partten)) {
		Figure figure;
		std::stringstream ss(figuretmp);
		std::string shape;
		long long a;
		long long b;
		long long c;
		long long d;
		ss >> shape;
		if (shape == "L" || shape == "R" || shape == "S") {
			ss >> a >> b >> c >> d;
			BondError(a, -100000, 100000);
			BondError(b, -100000, 100000);
			BondError(c, -100000, 100000);
			BondError(d, -100000, 100000);
			OverlapError(a, b, c, d);
			figure.shape = shape[0];
			figure.a = a;
			figure.b = b;
			figure.c = c;
			figure.d = d;
		}
		else {
			ss >> a >> b >> c;
			BondError(a, -100000, 100000);
			BondError(b, -100000, 100000);
			BondError(c, 1, 100000);
			figure.shape = shape[0];
			figure.a = a;
			figure.b = b;
			figure.c = c;
		}
		return figure;
	}
	else {
		std::cout << "输入图形格式错误！";
		exit(0);
	}
}