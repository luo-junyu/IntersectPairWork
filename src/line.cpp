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


void Line::	lineIntersect(Line& other_line, vector<struct Position>& res_vector) {
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		return;
	}
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


// Rag Line

rayLine::rayLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2)
{
	this->x_end1 = x1;
	this->y_end1 = y1;
	if (x2 > x1) {
		this->x_forward = 1;
	} else if (x2 == x1) {
		this->x_forward = 0;
	} else {
		this->x_forward = -1;
	}
	if (y2 > y1) {
		this->y_forward = 1;
	} else if (y2 == y1) {
		this->y_forward = 0;
	} else {
		this->y_forward = -1;
	}
}

inline bool rayLine::outRangeX(long long x) {
	if ((x_forward == 1 && x < x_end1) || (x_forward == -1 && x > x_end1)) {
		// For x_forward == 0, we use y_forward to check
		return true;
	}
	return false;
}

inline bool rayLine::outRangeY(long long y) {
	if ((y_forward == 1 && y < y_end1) || (y_forward == -1 && y > y_end1)) {
		return true;
	}
	return false;
}


/* rayLine intersect with Line */
void rayLine::lineIntersect(Line& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		return;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (outRangeX(x)) {
		return;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;
	if (x_forward == 0) {
		if (outRangeY(y)) {
			return;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return;
}

/* rayLine intersect with rayLine */
void rayLine::rayLineIntersect(rayLine& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		return;
	}
	long long x_upper = this->b * other_line.c - other_line.b * this->c;

	double x = x_upper * 1.0 / lower;

	if ((this->outRangeX(x)) || (other_line.outRangeX(x))) {
		return;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->x_forward == 0) {
		if (this->outRangeY(y)) {
			return;
		}
	}

	if (other_line.x_forward == 0) {
		if (other_line.outRangeY(y)) {
			return;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return;
}




segLine::segLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2)
{
	if (x1 < x2) {
		this->x_endLeft = x1;
		this->x_endRight = x2;
	} else {
		this->x_endLeft = x2;
		this->x_endRight = x1;
	}
	if (y1 < y2) {
		this->y_endLeft = y1;
		this->y_endRight = y2;
	} else {
		this->y_endLeft = y2;
		this->y_endRight = y1;
	}
	this->vertical = (x_endLeft == x_endRight);
}

inline bool segLine::outRangeX(long long x) {
	if (x < this->x_endLeft || x > x_endRight) {
		return true;
	}
	return false;
}

inline bool segLine::outRangeY(long long y) {
	if (y < y_endLeft || y > y_endRight) {
		return true;
	}
	return false;
}

/* segLine intersect with Line */
void segLine::lineIntersect(Line& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		return;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (outRangeX(x)) {
		return;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->vertical) {
		if (outRangeY(y)) {
			return;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return;
}

/* segLine intersect with rayLine */
void segLine::rayLineIntersect(rayLine& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		return;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (this->outRangeX(x) || other_line.outRangeX(x)) {
		return;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->vertical) {
		if (this->outRangeY(y)) {
			return;
		}
	}

	if (other_line.x_forward == 0) {
		if (other_line.outRangeY(y)) {
			return;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return;
}

/* segLine intersect with rayLine */
void segLine::segLineIntersect(segLine& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		return;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (this->outRangeX(x) || other_line.outRangeX(x)) {
		return;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->vertical) {
		if (this->outRangeY(y)) {
			return;
		}
	}

	if (other_line.vertical) {
		if (other_line.outRangeY(y)) {
			return;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return;
}
