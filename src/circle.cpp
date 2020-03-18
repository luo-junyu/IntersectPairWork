#include "circle.h"

void Circle::lineIntersect(Line& line, vector<struct Position>& res_vector) {
	struct Position res1;
	struct Position res2;

	long long x2_x1 = line.x2 - line.x1;
	long long y2_y1 = line.y2 - line.y1;
	long long norm = line.a * line.a + line.b * line.b;		// A^2+B^2

	long long d_x1 = this->x - line.x1;
	long long d_y1 = this->y - line.y1;
	double denominator = sqrt((double)norm);

	// dis = Ax0+By0+C / denominator
	// distance from the line to circle
	double distance = fabs((line.a * this->x + line.b * this->y + line.c)/ denominator);
	if (distance - this->r * 1.0 < eps) {	// has intersect
		double r_ = (d_x1 * x2_x1 + d_y1 * y2_y1) * 1.0 / norm;
		double d_x4 = x2_x1 / denominator;
		double d_y4 = y2_y1 / denominator;
		double d_x3 = line.x1 + x2_x1 * r_;
		double d_y3 = line.y1 + y2_y1 * r_;
		double d_x5 = d_x3 - this->x;
		double d_y5 = d_y3 - this->y;

		if (fabs(distance - 1.0 * this->r) > eps) {
			double base = sqrt(this_r_power - (d_x5 * d_x5 + d_y5 * d_y5));
			res1.x = d_x3 + d_x4 * base;
			res1.y = d_y3 + d_y4 * base;
			res2.x = d_x3 - d_x4 * base;
			res2.y = d_y3 - d_y4 * base;
			res_vector.push_back(res1);
			res_vector.push_back(res2);
			return;
		} else {
			res1.x = d_x3;
			res1.y = d_y3;
			res_vector.push_back(res1);
			return;
		}
	} 
}


void Circle::rayLineIntersect(rayLine& line, vector<struct Position>& res_vector) {
	struct Position res1;
	struct Position res2;

	long long x2_x1 = line.x2 - line.x1;
	long long y2_y1 = line.y2 - line.y1;
	long long norm = line.a * line.a + line.b * line.b;		// A^2+B^2

	long long d_x1 = this->x - line.x1;
	long long d_y1 = this->y - line.y1;
	double denominator = sqrt((double)norm);

	// dis = Ax0+By0+C / denominator
	// distance from the line to circle
	double distance = fabs((line.a * this->x + line.b * this->y + line.c) / denominator);
	if (distance - this->r * 1.0 < eps) {	// has intersect
		double r_ = (d_x1 * x2_x1 + d_y1 * y2_y1) * 1.0 / norm;
		double d_x4 = x2_x1 / denominator;
		double d_y4 = y2_y1 / denominator;
		double d_x3 = line.x1 + x2_x1 * r_;
		double d_y3 = line.y1 + y2_y1 * r_;
		double d_x5 = d_x3 - this->x;
		double d_y5 = d_y3 - this->y;

		if (fabs(distance - 1.0 * this->r) > eps) {
			double base = sqrt(this_r_power - (d_x5 * d_x5 + d_y5 * d_y5));
			res1.x = d_x3 + d_x4 * base;
			if (!line.outRangeX(res1.x)) {
				res1.y = d_y3 + d_y4 * base;
				if (line.x_forward == 0 && line.outRangeY(res1.y)) {
					// out range
				} else {
					res_vector.push_back(res1);
				}
			}

			res2.x = d_x3 - d_x4 * base;
			if (!line.outRangeX(res2.x)) {
				res2.y = d_y3 - d_y4 * base;
				if (line.x_forward == 0 && line.outRangeY(res2.y)) {
					// out range
				} else {
					res_vector.push_back(res2);
				}
			}
			return;
		} else {
			res1.x = d_x3;
			if (!line.outRangeX(res1.x)) {
				res1.y = d_y3;
				if (line.x_forward == 0 && line.outRangeY(res1.y)) {
					// out range
				} else {
					res_vector.push_back(res1);
				}
			}
			return;
		}
	}
}

void Circle::segLineIntersect(segLine& line, vector<struct Position>& res_vector) {
	struct Position res1;
	struct Position res2;

	long long x2_x1 = line.x2 - line.x1;
	long long y2_y1 = line.y2 - line.y1;
	long long norm = line.a * line.a + line.b * line.b;		// A^2+B^2

	long long d_x1 = this->x - line.x1;
	long long d_y1 = this->y - line.y1;
	double denominator = sqrt((double)norm);

	// dis = Ax0+By0+C / denominator
	// distance from the line to circle
	double distance = fabs((line.a * this->x + line.b * this->y + line.c) / denominator);
	if (distance - this->r * 1.0 < eps) {	// has intersect
		double r_ = (d_x1 * x2_x1 + d_y1 * y2_y1) * 1.0 / norm;
		double d_x4 = x2_x1 / denominator;
		double d_y4 = y2_y1 / denominator;
		double d_x3 = line.x1 + x2_x1 * r_;
		double d_y3 = line.y1 + y2_y1 * r_;
		double d_x5 = d_x3 - this->x;
		double d_y5 = d_y3 - this->y;

		if (fabs(distance - 1.0 * this->r) > eps) {
			double base = sqrt(this_r_power - (d_x5 * d_x5 + d_y5 * d_y5));
			res1.x = d_x3 + d_x4 * base;
			if (!line.outRangeX(res1.x)) {
				res1.y = d_y3 + d_y4 * base;
				if (line.vertical && line.outRangeY(res1.y)) {
					// out range
				} else {
					res_vector.push_back(res1);
				}
			}

			res2.x = d_x3 - d_x4 * base;
			if (!line.outRangeX(res2.x)) {
				res2.y = d_y3 - d_y4 * base;
				if (line.vertical && line.outRangeY(res2.y)) {
					// out range
				} else {
					res_vector.push_back(res2);
				}
			}
			return;
		} else {
			res1.x = d_x3;
			if (!line.outRangeX(res1.x)) {
				res1.y = d_y3;
				if (line.vertical && line.outRangeY(res1.y)) {
					// out range
				} else {
					res_vector.push_back(res1);
				}
			}
			return;
		}
	}
}


void Circle::circleIntersect(const Circle& circle, vector<struct Position>& res_vector) {

	struct Position res1;
	struct Position res2;
	long long circle_r_power = circle.this_r_power;
	long long circle_x_power = circle.this_x_power;
	long long circle_y_power = circle.this_y_power;

	long long x_power = this_x_power - 2 * this->x * circle.x + circle_x_power;
	long long y_power = this_y_power - 2 * this->y * circle.y + circle_y_power;
	long long r_power = this_r_power + 2 * this->r * circle.r + circle_r_power;
	long long r_neg_power = this_r_power - 2 * this->r * circle.r + circle_r_power;
	long long x_y_power = x_power + y_power;
	if (x_y_power == 0) {
		return;
	}
	long long sigma = (r_power - x_power - y_power) * (x_y_power - r_neg_power);
	if (sigma < 0) {
		return;
	} 
	
	double sigma_sqrt = sqrt((double)sigma);

	long long subs2 = -this_r_power * this->x + this_r_power * circle.x + circle_r_power * this->x - 
		circle_r_power * circle.x + this_x_power * this->x - this_x_power * circle.x - this->x * circle_x_power +
		this->x * this_y_power - 2 * this->x * this->y * circle.y + this->x * circle_y_power +
		circle_x_power * circle.x + circle.x * this_y_power - 2 * circle.x * this->y * circle.y + circle.x * circle_y_power;
	long long subs3 = -this_r_power * this->y + this_r_power * circle.y + circle_r_power * this->y -
		circle_r_power * circle.y + this_x_power * this->y + this_x_power * circle.y - 2 * this->x * circle.x * this->y -
		2 * this->x * circle.x * circle.y + circle_x_power * this->y + circle_x_power * circle.y + this_y_power * this->y -
		this_y_power * circle.y - this->y * circle_y_power + circle_y_power * circle.y;

	res1.x = (subs2 - sigma_sqrt * this->y + sigma_sqrt * circle.y) / (2 * x_y_power);
	res2.x = (subs2 + sigma_sqrt * this->y - sigma_sqrt * circle.y) / (2 * x_y_power);
	res1.y = (subs3 + sigma_sqrt * this->x - sigma_sqrt * circle.x) / (2 * x_y_power);
	res2.y = (subs3 - sigma_sqrt * this->x + sigma_sqrt * circle.x) / (2 * x_y_power);
	res_vector.push_back(res1);
	res_vector.push_back(res2);
}