#ifndef CIRCLE__H
#define CIRCLE__H

#include "intersect.h"
#include "line.h"
#include "errorhandler.h"
#include <math.h>
#include <vector>

class Circle 
{
public:
	Circle(long long x, long long y, long long r) {
		this->x = x;
		this->y = y;
		this->r = r;
		this_r_power = this->r * this->r;
		this_x_power = this->x * this->x;
		this_y_power = this->y * this->y;
	}
	Circle() {
		this->x = 0;
		this->y = 0;
		this->r = 0;
	}
	ErrorType lineIntersect(Line&, vector<struct Position>&);
	ErrorType rayLineIntersect(rayLine&, vector<struct Position>&);
	ErrorType segLineIntersect(segLine&, vector<struct Position>&);
	ErrorType circleIntersect(const Circle&, vector<struct Position>&);

	long long x, y, r;
	long long this_r_power;
	long long this_x_power;
	long long this_y_power;
};



#endif // !CIRCLE__H
