#ifndef API__H
#define API__H

#include "intersect.h"
#include "line.h"
#include "circle.h"
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

class IntersectionCounter {
public:
	IntersectionCounter();
	void setFigures(vector<int>);
	void setMapRange();
	vector<double> getIntersects();
	void reset();

	vector<Line> getLines();
	vector<rayLine> getRayLines();
	vector<segLine> getSegLines();
	vector<Circle> getCircles();
	vector<double> getFigures();

private:
	void update();
	vector<Line> lines;
	vector<rayLine> rayLines;
	vector<segLine> segLines;
	vector<Circle> circles;
	double x_max, x_min, y_max, y_min;
	vector<struct Position> intersects;
};


#endif // !API__H
