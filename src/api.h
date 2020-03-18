#ifndef API__H
#define API__H

#include "intersect.h"
#include "line.h"
#include "circle.h"
#include <string>

using namespace std;

class IntersectionCounter {
public:
	IntersectionCounter();
	void deleteLineIndex(int);
	void deleteCircleIndex(int);
	void deleteRayLineIndex(int);
	void deleteSegLineIndex(int);

	void addGraphicItem(string);
	void addGraphicFile(string);
	vector<struct Position> getIntersects();
	vector<Line> getLines();
	vector<rayLine> getRayLines();
	vector<segLine> getSegLines();
	vector<Circle> getCircles();

private:
	void upate();
	vector<Line> lines;
	vector<rayLine> rayLines;
	vector<segLine> segLines;
	vector<Circle> circles;
	vector<struct Position> pos;
};

#endif // !API__H
