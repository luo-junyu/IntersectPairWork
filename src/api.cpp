#include "api.h"

IntersectionCounter::IntersectionCounter() {
	x_max = -100000.0;
	x_min = 100000.0;
	y_max = -100000.0;
	y_min = 100000.0;
}

void IntersectionCounter::setMapRange() {
	x_max = -100000.0;
	x_min = 100000.0;
	y_max = -100000.0;
	y_min = 100000.0;
	// intersects
	for (struct Position pos : intersects) {
		x_max = std::max(x_max, pos.x);
		x_min = std::min(x_min, pos.x);
		y_max = std::max(y_max, pos.y);
		y_min = std::min(y_min, pos.y);
	}

	for (rayLine line : rayLines) {
		x_max = std::max(x_max, (double)(line.x_end1));
		x_min = std::min(x_min, (double)(line.x_end1));
		y_max = std::max(y_max, (double)(line.y_end1));
		y_min = std::min(y_min, (double)(line.y_end1));
	}

	for (segLine line : segLines) {
		x_max = std::max(x_max, (double)(line.x_endRight));
		x_min = std::min(x_min, (double)(line.x_endLeft));
		y_max = std::max(y_max, (double)(line.y_endRight));
		y_max = std::max(y_max, (double)(line.y_endLeft));
		y_min = std::min(y_min, (double)(line.y_endRight));
		y_min = std::min(y_min, (double)(line.y_endLeft));
	}

	for (Circle circle : circles) {
		x_max = std::max(x_max, (double)(circle.x + circle.r));
		x_min = std::min(x_min, (double)(circle.x - circle.r));
		y_max = std::max(y_max, (double)(circle.y + circle.r));
		y_min = std::min(y_min, (double)(circle.y - circle.r));
	}

	return;
}

void IntersectionCounter::setFigures(vector<int> numArray) {
	for (int index = 0; index < (int)numArray.size(); index += 5) {
		int flag = numArray[index];
		if (flag == 1) {			// Line
			Line tmpLine(numArray[index+1], numArray[index + 2], numArray[index + 3], numArray[index + 4]);
			lines.push_back(tmpLine);
		} else if (flag == 2) {		// rayLine
			rayLine tmprayLine(numArray[index + 1], numArray[index + 2], numArray[index + 3], numArray[index + 4]);
			rayLines.push_back(tmprayLine);
		} else if (flag == 3) {		// segLine
			segLine tmpSegLine(numArray[index + 1], numArray[index + 2], numArray[index + 3], numArray[index + 4]);
			segLines.push_back(tmpSegLine);
		} else if (flag == 4) {		// Circle
			Circle tmpCircle(numArray[index + 1], numArray[index + 2], numArray[index + 3]);
			circles.push_back(tmpCircle);
		}
	}

	setMapRange();
}

void IntersectionCounter::reset() {
	x_max = -100000.0;
	x_min = 100000.0;
	y_max = -100000.0;
	y_min = 100000.0;
	lines.clear();
	rayLines.clear();
	segLines.clear();
	circles.clear();
}

void IntersectionCounter::update() {
	int line_num = lines.size();
	int rayLine_num = rayLines.size();
	int segLine_num = segLines.size();
	int circle_num = circles.size();
	vector<struct Position> points;

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
			line1.rayLineIntersect(line2, points);
		}
	}

	// segLine & segLine
	for (int i = 0; i < segLine_num; i++) {
		for (int j = i + 1; j < segLine_num; j++) {
			segLine& line1 = segLines[i];
			segLine& line2 = segLines[j];
			line1.segLineIntersect(line2, points);
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
			rayLine& line1 = rayLines[i];
			segLine& line2 = segLines[j];
			line2.rayLineIntersect(line1, points);
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

	// rayLine & Circle

	for (int i = 0; i < rayLine_num; i++) {
		for (int j = 0; j < circle_num; j++) {
			rayLine& tmpLine = rayLines[i];
			Circle& tmpCircle = circles[j];
			tmpCircle.rayLineIntersect(tmpLine, points);
		}
	}

	// segLine & Circle

	for (int i = 0; i < segLine_num; i++) {
		for (int j = 0; j < circle_num; j++) {
			segLine& tmpLine = segLines[i];
			Circle& tmpCircle = circles[j];
			tmpCircle.segLineIntersect(tmpLine, points);
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

	intersects = vector<struct Position>(points.begin(), points_end);

	return;
}

vector<double> IntersectionCounter::getIntersects() {
	update();
	vector <double> res;
	for (struct Position pos : intersects) {
		res.push_back(pos.x);
		res.push_back(pos.y);
	}
	return res;
}

vector<double> IntersectionCounter::getFigures() {
	vector<double> res;
	for (Line line : lines) {
		double flag = 1;
		double line_x_right, line_x_left;
		double line_y_right, line_y_left;
		if (line.b == 0) {
			line_x_right = (double)line.x1;
			line_x_left = (double)line.x1;
			line_y_right = (double)y_max;
			line_y_left = (double)y_min;
		} else {
			line_x_right = (double)x_max;
			line_x_left = (double)x_min;
			line_y_right = (double)(line.c * -1. - line.a * x_max) / line.b;
			line_y_left = (double)(line.c * -1. - line.a * x_min) / line.b;
		}
		res.push_back(flag);
		res.push_back(line_x_right);
		res.push_back(line_y_right);
		res.push_back(line_x_left);
		res.push_back(line_y_left);
	}

	for (rayLine line : rayLines) {
		double line_x_right, line_x_left;
		double line_y_right, line_y_left;
		if (line.x_forward == 1) {
			line_x_right = (double)x_max;
			line_y_right = (double)(line.c * -1. - line.a * x_max) / line.b;
			line_x_left = (double)line.x_end1;
			line_y_left = (double)line.y_end1;
		} else if (line.x_forward == -1) {
			line_x_left = (double)x_min;
			line_y_left = (double)(line.c * -1. - line.a * x_min) / line.b;
			line_x_right = (double)line.x_end1;
			line_y_right = (double)line.y_end1;
		} else if (line.x_forward == 0) {
			if (line.y_forward == 1) {
				line_x_right = (double)line.x1;
				line_y_right = (double)y_max;
				line_x_left = (double)line.x1;
				line_y_left = (double)line.y_end1;
			} else if (line.y_forward == 0) {
				line_x_right = (double)line.x1;
				line_y_right = (double)y_min;
				line_x_left = (double)line.x1;
				line_y_left = (double)line.y_end1;
			}
		}
		res.push_back(2.);
		res.push_back(line_x_right);
		res.push_back(line_y_right);
		res.push_back(line_x_left);
		res.push_back(line_y_left);
	}

	for (segLine line : segLines) {
		res.push_back(3.);
		res.push_back((double)line.x1);
		res.push_back((double)line.y1);
		res.push_back((double)line.x2);
		res.push_back((double)line.y2);
	}

	for (Circle circle : circles) {
		res.push_back(4.);
		res.push_back((double)circle.x);
		res.push_back((double)circle.y);
		res.push_back((double)circle.r);
		res.push_back(0);
	}

	return res;
}


vector<Line> IntersectionCounter::getLines() {
	return lines;
}

vector<rayLine> IntersectionCounter::getRayLines() {
	return rayLines;
}

vector<segLine>IntersectionCounter::getSegLines() {
	return segLines;
}

vector<Circle> IntersectionCounter::getCircles() {
	return circles;
}