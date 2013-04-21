#include "bat.h"
Bat::Bat():_point(2),_id(0)
{
}

Bat::Bat(const Bat& bat):_point(bat._point), _id(bat._id)
{
}


Bat::Bat(const QPointF &point1, const QPointF &point2, quint32 id): _point(2),_id(id)
{
    _point[0]=point1;
    _point[1]=point2;
}

Bat::Bat(const QVector<QPointF> &points, quint32 id): _point(points), _id(id)
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

void Bat::operator>>(QDataStream& out)const
{
    out << qint32(_id) << _point[0]<<_point[1];
}


void Bat::operator<<(QDataStream& in)
{
    in >> _id >> _point[0] >> _point[1];
}


QDataStream & operator>>(QDataStream & in, Bat & bat)
{
    bat<<in;
    return in;
}

QDataStream & operator<<(QDataStream & out, const Bat & bat)
{
    bat>>out;
    return out;
}
