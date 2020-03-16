#include "line.h"
#include<stdio.h>
/*
	Bulid a line (ax + by + c = 0)
	INPUT: 2 points: x1,y1,x2,y2
*/
Line::Line(long long x1, long long y1, long long x2, long long y2)
{
	this->a = y2 - y1;
	this->b = x1 - x2;
	this->c = x2 * y1 - x1 * y2;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}


void Line::intersect(Line& other_line, vector<struct Position>& res_vector) {
	long long lower = this->a * other_line.b - this->b * other_line.a;
	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	long long y_upper = other_line.a * this->c - this->a * other_line.c;

	double x = x_upper * 1.0 / lower;
	double y = y_upper * 1.0 / lower;
	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return;
}
