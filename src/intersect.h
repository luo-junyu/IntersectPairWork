#ifndef INTERSECT__H
#define INTERSECT__H

using namespace std;
const double eps = 0.0000000000001;
const double eps_neg = -1 * eps;

struct Position
{
	double x;
	double y;
};

bool posCompare(const Position& point1, const Position& point2);

bool posEqual(const Position& point1, const Position& point2);

#endif // !INTERSECT__H
