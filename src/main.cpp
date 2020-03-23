#include <iostream>
#include "intersect.h"
#include "line.h"
#include "circle.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include "errorhandler.h"
#include <string>

const int debug_mood = 1;

using namespace std;

vector<struct Position> points;
vector<Line> lines;
vector<Circle> circles;
vector<segLine> segLines;
vector<rayLine> rayLines;


int main(int argc, char** argv)
{

	// TODO: Add a test mood

	ifstream input;
	ofstream output;
	string ntmp;
	int n;
	char flag;
	//long long x1, y1, x2, y2;	// tmp var for line
	//long long x, y, r;			// tmp var for circle
	int line_num = 0;
	int circle_num = 0;
	int segLine_num = 0;
	int rayLine_num = 0;
	ErrorType errortype;
	

	/*if (debug_mood) {
		input.open("input.txt");
	} else {
		for (int index = 0; index < argc; index++) {
			if ((string)argv[index] == "-i") {
				index++;
				input.open(argv[index]);
			} else if ((string)argv[index] == "-o") {
				index++;
				output.open(argv[index]);
			}
		}
	}*/
	if (debug_mood) {
		input.open("input.txt");
	} else {
		errortype = CommandError(argc, argv);
		HandleError(errortype);
		input.open(argv[2], ios::in);
		errortype = EmptyFileError(input);
		HandleError(errortype);

		output.open(argv[4], ios::out);
	}
	input >> ntmp;
	input.ignore();
	errortype = NumError(ntmp);
	HandleError(errortype);
	n = atoi(ntmp.c_str());
	

	//input >> n;
	for (int i = 0; i < n; i++) {
		string figuretmp;
		CorrectFigure figure;
		getline(input, figuretmp);
		figure = FigureError(figuretmp);
		HandleError(figure.errortype);
		long long x1, x2, y1, y2;
		long long x, y, r;
		flag = figure.shape;
		if (flag != 'C') {
			x1 = figure.a;
			y1 = figure.b;
			x2 = figure.c;
			y2 = figure.d;
		}
		else {
			x = figure.a;
			y = figure.b;
			r = figure.c;
		}
		
		//input >> flag;
		if (flag == 'L') {
			//input >> x1 >> y1 >> x2 >> y2;
			Line tmpLine(x1, y1, x2, y2);
			lines.push_back(tmpLine);
			line_num++;
		} else if (flag == 'C') {
			//input >> x >> y >> r;	
			Circle tmpCircle(x, y, r);
			circles.push_back(tmpCircle);
			circle_num++;
		} else if (flag == 'S') {
			//input >> x1 >> y1 >> x2 >> y2;
			segLine tmpSegLine(x1, y1, x2, y2);
			segLines.push_back(tmpSegLine);
			segLine_num++;
		} else if (flag == 'R') {
			//input >> x1 >> y1 >> x2 >> y2;
			rayLine tmprayLine(x1, y1, x2, y2);
			rayLines.push_back(tmprayLine);
			rayLine_num++;
		}
	}

	input.close();
	
	// Line & Line

	for (int i = 0; i < line_num; i++) {
		for (int j = i + 1; j < line_num; j++) {
			Line& line1 = lines[i];
			Line& line2 = lines[j];
			ErrorType err = line1.lineIntersect(line2, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// rayLine & rayLine
	for (int i = 0; i < rayLine_num; i++) {
		for (int j = i + 1; j < rayLine_num; j++) {
			rayLine& line1 = rayLines[i];
			rayLine& line2 = rayLines[j];
			ErrorType err = line1.rayLineIntersect(line2, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// segLine & segLine
	for (int i = 0; i < segLine_num; i++) {
		for (int j = i + 1; j < segLine_num; j++) {
			segLine& line1 = segLines[i];
			segLine& line2 = segLines[j];
			ErrorType err = line1.segLineIntersect(line2, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// Line & rayLine

	for (int i = 0; i < rayLine_num; i++) {
		for (int j = 0; j < line_num; j++) {
			rayLine& line1 = rayLines[i];
			Line& line2 = lines[j];
			ErrorType err = line1.lineIntersect(line2, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// Line & segLine

	for (int i = 0; i < segLine_num; i++) {
		for (int j = 0; j < line_num; j++) {
			segLine& line1 = segLines[i];
			Line& line2 = lines[j];
			ErrorType err = line1.lineIntersect(line2, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// rayLine & segLine

	for (int i = 0; i < rayLine_num; i++) {
		for (int j = 0; j < segLine_num; j++) {
			rayLine& line1 = rayLines[i];
			segLine& line2 = segLines[j];
			ErrorType err = line2.rayLineIntersect(line1, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// Line & Circle

	for (int i = 0; i < line_num; i++) {
		for (int j = 0; j < circle_num; j++) {
			Line& tmpLine = lines[i];
			Circle& tmpCircle = circles[j];
			ErrorType err = tmpCircle.lineIntersect(tmpLine, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// rayLine & Circle

	for (int i = 0; i < rayLine_num; i++) {
		for (int j = 0; j < circle_num; j++) {
			rayLine& tmpLine = rayLines[i];
			Circle& tmpCircle = circles[j];
			ErrorType err = tmpCircle.rayLineIntersect(tmpLine, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// segLine & Circle

	for (int i = 0; i < segLine_num; i++) {
		for (int j = 0; j < circle_num; j++) {
			segLine& tmpLine = segLines[i];
			Circle& tmpCircle = circles[j];
			ErrorType err = tmpCircle.segLineIntersect(tmpLine, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// Circle & Circle

	for (int i = 0; i < circle_num; i++) {
		for (int j = i + 1; j < circle_num; j++) {
			Circle& circle1 = circles[i];
			Circle& circle2 = circles[j];
			ErrorType err = circle1.circleIntersect(circle2, points);
			if (err != ErrorType::NoError) {
				HandleError(err);
			}
		}
	}

	// delete the repeat points
	sort(points.begin(), points.end(), posCompare);
	auto points_end = unique(points.begin(), points.end(), posEqual);

	// if (debug_mood) {
	cout << points_end - points.begin() << endl;
	// }

	output << points_end - points.begin();
	output.close();

	return 0;
}
