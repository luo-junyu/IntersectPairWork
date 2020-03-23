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


ErrorType Line::lineIntersect(Line& other_line, vector<struct Position>& res_vector) {
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		if (this->a * other_line.x1 + this->b * other_line.y1 + this->c == 0) {
			return ErrorType::SameLine;
		}
		return ErrorType::NoError;
	}
	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	long long y_upper = other_line.a * this->c - this->a * other_line.c;

	double x = x_upper * 1.0 / lower;
	double y = y_upper * 1.0 / lower;
	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return ErrorType::NoError;
}


// Ray Line

rayLine::rayLine(long long x1, long long y1, long long x2, long long y2) : Line(x1, y1, x2, y2)
{
	this->x_end1 = x1;
	this->y_end1 = y1;
	this->x_end1_add_eps = x1 + eps;
	this->x_end1_sub_eps = x1 - eps;
	this->y_end1_add_eps = y1 + eps;
	this->y_end1_sub_eps = y1 - eps;
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

inline bool rayLine::outRangeX(double x) {
	if ((x_forward == 1 && x < x_end1_sub_eps) || (x_forward == -1 && x > x_end1_add_eps)) {
		// For x_forward == 0, we use y_forward to check
		return true;
	}
	return false;
}

inline bool rayLine::outRangeY(double y) {
	if ((y_forward == 1 && y < y_end1_sub_eps) || (y_forward == -1 && y > y_end1_add_eps)) {
		return true;
	}
	return false;
}


/* rayLine intersect with Line */
ErrorType rayLine::lineIntersect(Line& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		if (this->a * other_line.x1 + this->b * other_line.y1 + this->c == 0) {
			return ErrorType::SameLine;
		}
		return ErrorType::NoError;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (outRangeX(x)) {
		return ErrorType::NoError;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;
	if (x_forward == 0) {
		if (outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return ErrorType::NoError;
}

/* rayLine intersect with rayLine */
ErrorType rayLine::rayLineIntersect(rayLine& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;

	if (lower == 0) {
		if (this->a * other_line.x1 + this->b * other_line.y1 + this->c == 0) {	// same line
			if ((this->x_forward == -1 && other_line.x_forward == 1) ||
				(this->x_forward == 1 && other_line.x_forward == -1) ||
				(this->x_forward == 0 && (this->y_forward == -1 * other_line.y_forward))
			) {
				// different forward
				if (this->x_end1 == other_line.x_end1 && this->y_end1 == other_line.y_end1) {
					struct Position res;
					res.x = this->x_end1;
					res.y = this->x_end1;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if ((this->x_forward == -1 && other_line.x_end1 < this->x_end1) ||
					(this->x_forward == 1 && other_line.x_end1 > this->x_end1) ||
					(this->x_forward == 0 && ((this->y_forward == 1 && other_line.y_end1 > this->y_end1) ||
					(this->y_forward == -1 && other_line.y_end1 < this->y_end1)))) {
					return ErrorType::SameLine;
				} else {
					// not error
				}
			} else {
				return (ErrorType::SameLine);
			}
		}
		return ErrorType::NoError;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;

	double x = x_upper * 1.0 / lower;

	if ((this->outRangeX(x)) || (other_line.outRangeX(x))) {
		return ErrorType::NoError;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->x_forward == 0) {
		if (this->outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	if (other_line.x_forward == 0) {
		if (other_line.outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return ErrorType::NoError;
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
	this->x_endLeft_sub_eps = this->x_endLeft - eps;
	this->x_endLeft_add_eps = this->x_endLeft + eps;
	this->y_endLeft_sub_eps = this->y_endLeft - eps;
	this->y_endLeft_add_eps = this->y_endLeft + eps;
	this->x_endRight_sub_eps = this->x_endRight - eps;
	this->x_endRight_add_eps = this->x_endRight + eps;
	this->y_endRight_sub_eps = this->y_endRight - eps;
	this->y_endRight_add_eps = this->y_endRight + eps;
}

inline bool segLine::outRangeX(double x) {
	if (x < this->x_endLeft_sub_eps || x > this->x_endRight_add_eps) {
		return true;
	}
	return false;
}

inline bool segLine::outRangeY(double y) {
	if (y < this->y_endLeft_sub_eps || y > this->y_endRight_add_eps) {
		return true;
	}
	return false;
}

/* segLine intersect with Line */
ErrorType segLine::lineIntersect(Line& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		if (this->a * other_line.x1 + this->b * other_line.y1 + this->c == 0) {
			return (ErrorType::SameLine);
		}
		return ErrorType::NoError;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (outRangeX(x)) {
		return ErrorType::NoError;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->vertical) {
		if (outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return ErrorType::NoError;
}

/* segLine intersect with rayLine */
ErrorType segLine::rayLineIntersect(rayLine& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;

	if (lower == 0) {
		if (this->a * other_line.x1 + this->b * other_line.y1 + this->c == 0) {	// same line
			
			if (other_line.x_forward == 1) {
				if (this->x_endRight == other_line.x_end1) {
					struct Position res;
					res.x = other_line.x_end1;
					res.y = other_line.y_end1;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if (this->x_endRight > other_line.x_end1) {
					return (ErrorType::SameLine);
				} 
			} else if (other_line.x_forward == -1) {
				if (this->x_endLeft == other_line.x_end1) {
					struct Position res;
					res.x = other_line.x_end1;
					res.y = other_line.y_end1;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if (this->x_endLeft < other_line.x_end1) {
					return (ErrorType::SameLine);
				}
			} else if (other_line.x_forward == 0 && other_line.y_forward == 1) {
				if (this->y_endRight == other_line.y_end1) {
					struct Position res;
					res.x = other_line.x_end1;
					res.y = other_line.y_end1;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if (this->y_endRight > other_line.y_end1) {
					return (ErrorType::SameLine);
				}
			} else if (other_line.x_forward == 0 && other_line.y_forward == -1) {
				if (this->y_endLeft == other_line.y_end1) {
					struct Position res;
					res.x = other_line.x_end1;
					res.y = other_line.y_end1;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if (this->y_endLeft < other_line.y_end1) {
					return (ErrorType::SameLine);
				}
			}

		}
		return ErrorType::NoError;
	}

	if (lower == 0) {
		return ErrorType::NoError;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (this->outRangeX(x) || other_line.outRangeX(x)) {
		return ErrorType::NoError;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->vertical) {
		if (this->outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	if (other_line.x_forward == 0) {
		if (other_line.outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return ErrorType::NoError;
}

/* segLine intersect with rayLine */
ErrorType segLine::segLineIntersect(segLine& other_line, vector<struct Position>& res_vector)
{
	long long lower = this->a * other_line.b - this->b * other_line.a;
	if (lower == 0) {
		if (this->a * other_line.x1 + this->b * other_line.y1 + this->c == 0) {	// same line
			if (this->x_endLeft == this->x_endRight) {
				if (this->y_endLeft == other_line.y_endRight) {
					struct Position res;
					res.x = this->x_endLeft;
					res.y = this->y_endLeft;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if (this->y_endRight == other_line.y_endLeft) {
					struct Position res;
					res.x = this->x_endLeft;
					res.y = this->y_endRight;
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if ((this->y1 >= other_line.y_endLeft && this->y1 <= other_line.y_endRight) ||
					(this->y2 >= other_line.y_endLeft && this->y2 <= other_line.y_endRight)) {
					return (ErrorType::SameLine);
				}
			} else {
				if (this->x_endLeft == other_line.x_endRight) {
					struct Position res;
					res.x = this->x_endLeft;
					if (this->x_endLeft == this->x1) {
						res.y = this->y1;
					} else {
						res.y = this->y2;
					}
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if (this->x_endRight == other_line.x_endLeft) {
					struct Position res;
					res.x = this->x_endRight;
					if (this->x_endRight == this->x1) {
						res.y = this->y1;
					} else {
						res.y = this->y2;
					}
					res_vector.push_back(res);
					return ErrorType::NoError;
				} else if ((this->x1 >= other_line.x_endLeft && this->x1 <= other_line.x_endRight) || 
					(this->x2 >= other_line.x_endLeft && this->x2 <= other_line.x_endRight)) {
					return (ErrorType::SameLine);
				}
			}
		}
		return ErrorType::NoError;
	}

	long long x_upper = this->b * other_line.c - other_line.b * this->c;
	double x = x_upper * 1.0 / lower;

	if (this->outRangeX(x) || other_line.outRangeX(x)) {
		return ErrorType::NoError;
	}

	long long y_upper = other_line.a * this->c - this->a * other_line.c;
	double y = y_upper * 1.0 / lower;

	if (this->vertical) {
		if (this->outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	if (other_line.vertical) {
		if (other_line.outRangeY(y)) {
			return ErrorType::NoError;
		}
	}

	struct Position res;
	res.x = x;
	res.y = y;
	res_vector.push_back(res);
	return ErrorType::NoError;
}
