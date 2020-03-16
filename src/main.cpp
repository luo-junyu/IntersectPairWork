#include <iostream>
#include "intersect.h"
#include "line.h"
#include "circle.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

vector<struct Position> points;
vector<Line> lines;
vector<Circle> circles;

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


	for (int index = 0; index < argc; index++) {
		if ((string)argv[index] == "-i") {
			index++;
			input.open(argv[index]);
		} else if ((string)argv[index] == "-o") {
			index++;
			output.open(argv[index]);
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
		}
	}

	input.close();
	

	// Line & Line

	for (int i = 0; i < line_num; i++) {
		for (int j = i + 1; j < line_num; j++) {
			Line& line1 = lines[i];
			Line& line2 = lines[j];
			long long denominator = line1.a * line2.b - line1.b * line2.a;
			if (denominator != 0) {
				points.push_back(line1.intersect(line2));
			} 
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

	// TODO: Ray, Line segment
	
	// delete the repeat points
	sort(points.begin(), points.end(), posCompare);
	auto points_end = unique(points.begin(), points.end(), posEqual);

	// cout << points_end - points.begin() << endl;

	output << points_end - points.begin();
	output.close();

	return 0;
}
