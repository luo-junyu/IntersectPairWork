#ifndef DLL_H
#define DLL_H
#include <string>
#include <tuple>
#include <algorithm>
#include <vector>
#include "DLL_global.h"

class DLL_EXPORT DLL
{
public:
    DLL();
    void setFigures(std::vector<int>);
    void setMapRange();
    void reset();
    void update();
    std::vector<double> getFigures();
    std::vector<double> getIntersects();
};

#endif // DLL_H
