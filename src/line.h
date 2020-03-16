#ifndef LINE__H
#define LINE__H

#include "intersect.h"
#include <vector>

class Line
{
public:
	Line(long long x1, long long y1, long long x2, long long y2);
	struct Position intersect(Line&, vector<struct Position>&);
	long long a, b, c;
	long long x1, y1, x2, y2;
private:
	
};



#endif // !LINE__H
