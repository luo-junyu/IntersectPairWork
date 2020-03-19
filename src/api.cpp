#include "api.h"

IntersectionCounter::IntersectionCounter() {}

tuple<double, double, double, double> IntersectionCounter::getMapRange() {
	double x_max = -100000.0, x_min = 100000.0, y_max = -100000.0, y_min = 100000.0;
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

	return tuple<double, double, double, double>(x_max, x_min, y_max, y_min);
}


void IntersectionCounter::update() {

	int line_num = lines.size();
	int rayLine_num = rayLines.size();
	int segLine_num = segLines.size();
	int circle_num = circles.size();
	vector<struct Position> points;


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

vector<struct Position> IntersectionCounter::getIntersects() {
	update();
	return intersects;
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