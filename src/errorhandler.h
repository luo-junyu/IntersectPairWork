#pragma once

enum class ErrorType {
	NoError, CommandNum, CommandFormat, FileNotExist,
	EmptyFile, NumOutOfRange, AssertNum,
	FigureOutOfRange, LinePointOverlap, FigureFormat
};

struct CorrectFigure {
	char shape;
	long long a;
	long long b;
	long long c;
	long long d;
	ErrorType errortype;
};

ErrorType CommandError(int argc, char* argv[]);
ErrorType EmptyFileError(std::ifstream &ifile);
ErrorType NumError(std::string ntmp);
ErrorType BondError(long long num, int low, int high);
ErrorType OverlapError(long long a, long long b, long long c, long long d);
CorrectFigure FigureError(std::string figure);
void HandleError(ErrorType errortype);