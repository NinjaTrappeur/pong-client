#include "serveurcommunicator.h"

ServeurCommunicator::ServeurCommunicator(QObject *parent) :
    QObject(parent)
{
}

void ServeurCommunicator::operator>>(QDataStream& out)const
{
    out << _batVector.size()<< _nbPlayers << _loserIndex << _gameState<< _batVector;
}


void ServeurCommunicator::operator<<(QDataStream& in)
{
    int vectorSize;
    in >> vectorSize;
    in >> _nbPlayers >> _loserIndex >> _gameState;
    for(int i=0;i<vectorSize;++i)
        in >> _batVector[i];
}


QDataStream & operator>>(QDataStream & in, ServeurCommunicator & client)
{
    client<<in;
    return in;
}

QDataStream & operator<<(QDataStream & out, const ServeurCommunicator & client)
{
    client>>out;
    return out;
}
