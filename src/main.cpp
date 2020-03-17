#include <iostream>
#include "intersect.h"
#include "line.h"
#include "circle.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

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
	int n;
	char flag;
	long long x1, y1, x2, y2;	// tmp var for line
	long long x, y, r;			// tmp var for circle
	int line_num = 0;
	int circle_num = 0;
	int segLine_num = 0;
	int rayLine_num = 0;


	if (debug_mood) {
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
	}

	

	input >> n;
	for (int i = 0; i < n; i++) {
		input >> flag;
		if (flag == 'L') {
			input >> x1 >> y1 >> x2 >> y2;
			Line tmpLine(x1, y1, x2, y2);
			lines.push_back(tmpLine);
			line_num++;
		} else if (flag == 'C') {
			input >> x >> y >> r;	
			Circle tmpCircle(x, y, r);
			circles.push_back(tmpCircle);
			circle_num++;
		} else if (flag == 'S') {
			input >> x1 >> y1 >> x2 >> y2;
			segLine tmpSegLine(x1, y1, x2, y2);
			segLines.push_back(tmpSegLine);
			segLine_num++;
		} else if (flag == 'R') {
			input >> x1 >> y1 >> x2 >> y2;
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
			line1.lineIntersect(line2, points);
		}
	}

	// rayLine & rayLine
	for (int i = 0; i < rayLine_num; i++) {
		for (int j = i + 1; j < rayLine_num; j++) {
			rayLine& line1 = rayLines[i];
			rayLine& line2 = rayLines[j];
			line1.lineIntersect(line2, points);
		}
	}

	// rayLine & rayLine
	for (int i = 0; i < segLine_num; i++) {
		for (int j = i + 1; j < segLine_num; j++) {
			segLine& line1 = segLines[i];
			segLine& line2 = segLines[j];
			line1.lineIntersect(line2, points);
		}
	}

	// Line & rayLine

	for (int i = 0; i < rayLine_num; i++) {
		for (int j = 0; j < line_num; j++) {
			rayLine& line1 = rayLines[i];
			Line& line2 = lines[j];
			line1.lineIntersect(line2, points);
		}
	}

	// Line & segLine

	for (int i = 0; i < segLine_num; i++) {
		for (int j = 0; j < line_num; j++) {
			segLine& line1 = segLines[i];
			Line& line2 = lines[j];
			line1.lineIntersect(line2, points);
		}
	}
	
	// rayLine & segLine

	for (int i = 0; i < rayLine_num; i++) {
		for (int j = 0; j < segLine_num; j++) {
			segLine& line1 = segLines[i];
			rayLine& line2 = rayLines[j];
			line1.lineIntersect(line2, points);
		}
	}










	// Line & Circle

	for (int i = 0; i < line_num; i++) {
		for (int j = 0; j < circle_num; j++) {
			Line& tmpLine = lines[i];
			Circle& tmpCircle = circles[j];
			tmpCircle.lineIntersect(tmpLine, points);
		}
	}

	// Circle & Circle
	
	for (int i = 0; i < circle_num; i++) {
		for (int j = i + 1; j < circle_num; j++) {
			Circle& circle1 = circles[i];
			Circle& circle2 = circles[j];
			circle1.circleIntersect(circle2, points);
		}
	}

	// delete the repeat points
	sort(points.begin(), points.end(), posCompare);
	auto points_end = unique(points.begin(), points.end(), posEqual);

	if (debug_mood) {
		cout << points_end - points.begin() << endl;
	}

	output << points_end - points.begin();
	output.close();

	return 0;
}
