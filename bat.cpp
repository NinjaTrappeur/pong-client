#include "bat.h"
Bat::Bat()
{
}

Bat::Bat(const QPointF &point1, const QPointF &point2, int id): _id(id)
{
    _point.push_back(point1);
    _point.push_back(point2);
}

Bat::Bat(const QVector<QPointF> &points, int id): _point(points), _id(id)
{
}

int Bat::getId()
{
    return(_id);
}

void Bat::moveBat(QPointF &pos1, QPointF &pos2)
{
    _point[0]=pos1;
    _point[1]=pos2;
}

QVector<QPointF> Bat::getPoints()
{
    return(_point);
}
