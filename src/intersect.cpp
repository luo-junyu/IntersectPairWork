#include "intersect.h"
#include <math.h>

bool posCompare(const Position& point1, const Position& point2)
{
	double delta = point1.x - point2.x;
	if (delta > eps or delta < eps_neg) {
		return delta > 0;
	} else {
		return point1.y > point2.y;
	}
}

bool posEqual(const Position& point1, const Position& point2)
{
	double delta1 = point1.x - point2.x;
	if (delta1 > eps or delta1 < eps_neg) {
		return false;
	}

	double delta2 = point1.y - point2.y;
	if (delta2 > eps or delta2 < eps_neg) {
		return false;
	}
	return true;
}
