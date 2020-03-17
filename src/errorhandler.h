#pragma once

struct Figure {
	char shape;
	long long a;
	long long b;
	long long c;
	long long d;
};

void CommandError(int argc, char* argv[]);
void EmptyFileError(std::ifstream &ifile);
void NumError(std::string ntmp);
void BondError(int num, int low, int high);
void OverlapError(int a, int b, int c, int d);
Figure FigureError(std::string figure);