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
    return((radian*180)/_pi);
}

QPointF MathUtils::rotatePoint(const QPointF &point, qint32 angle)
{
    QPointF newPoint(point.x()*::cos(MathUtils::degreeToRadian(angle))+
                     point.y()*::sin(MathUtils::degreeToRadian(angle)),
                     point.y()*::cos(MathUtils::degreeToRadian(angle))-
                     point.x()*::sin(MathUtils::degreeToRadian(angle)));
    return newPoint;
}

Bat MathUtils::rotateBat(Bat &bat, qint32 angle)
{
    Bat newBat(MathUtils::rotatePoint(bat.getPoints()[0],angle),
            MathUtils::rotatePoint(bat.getPoints()[1], angle),
            bat.getId());
    return newBat;
}

QLine MathUtils::rotateQLine(QLine &line, qint32 angle)
{
    QLine newLine(MathUtils::rotatePoint(line.p1(), angle).toPoint(),
               MathUtils::rotatePoint(line.p2(), angle).toPoint());
    return newLine;
}

