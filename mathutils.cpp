#include "mathutils.h"

const double MathUtils::_pi = 3.141592653589793238462643383279;

MathUtils::MathUtils()
{
}

double MathUtils::degreeToRadian(double degree)
{
    return((degree*_pi)/180);
}

double MathUtils::radianToDegree(double radian)
{
    return((radian*_pi)/180);
}
