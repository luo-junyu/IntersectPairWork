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

	tuple<double, double, double, double> getMapRange();

	void deleteLineIndex(int);
	void deleteCircleIndex(int);
	void deleteRayLineIndex(int);
	void deleteSegLineIndex(int);

	void addGraphicItem(string);
	void addGraphicFile(string);
	vector<struct Position> getIntersects();

	vector<struct Position> getIntersects(vector<Line>&, vector<rayLine>&, vector<segLine>&, vector<Circle>&);

	vector<Line> getLines();
	vector<rayLine> getRayLines();
	vector<segLine> getSegLines();
	vector<Circle> getCircles();

private:
	void update();
	vector<Line> lines;
	vector<rayLine> rayLines;
	vector<segLine> segLines;
	vector<Circle> circles;
	vector<struct Position> intersects;
};

#endif // !API__H
