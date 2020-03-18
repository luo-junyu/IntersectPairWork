#ifndef LINE__H
#define LINE__H

#include "intersect.h"
#include <vector>

class Line
{
public:
	Line(long long x1, long long y1, long long x2, long long y2);
	void lineIntersect(Line&, vector<struct Position>&);
	long long a, b, c;
	long long x1, y1, x2, y2;
};

class rayLine : public Line
{
public:
	rayLine(long long, long long, long long, long long);
	void lineIntersect(Line&, vector<struct Position>&);
	void rayLineIntersect(rayLine&, vector<struct Position>&);
	inline bool outRangeX(double x);
	inline bool outRangeY(double y);
	long long x_end1, y_end1;
	double x_end1_sub_eps, x_end1_add_eps, y_end1_sub_eps, y_end1_add_eps;
	int x_forward, y_forward;
};

class segLine : public Line
{
public:
	segLine(long long, long long, long long, long long);
	void lineIntersect(Line&, vector<struct Position>&);
	void rayLineIntersect(rayLine&, vector<struct Position>&);
	void segLineIntersect(segLine&, vector<struct Position>&);
	inline bool outRangeX(double x);
	inline bool outRangeY(double y);
	long long x_endLeft, y_endLeft, x_endRight, y_endRight;
	double x_endLeft_sub_eps, x_endLeft_add_eps, y_endLeft_sub_eps, y_endLeft_add_eps, 
		x_endRight_sub_eps, x_endRight_add_eps, y_endRight_add_eps, y_endRight_sub_eps;
	bool vertical;
};



#endif // !LINE__H
