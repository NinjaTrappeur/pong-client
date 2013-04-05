#include "clientcommunicator.h"

ClientCommunicator::ClientCommunicator(QObject *parent) :
    QObject(parent)
{
}


void ClientCommunicator::operator>>(QDataStream& out)const
{
    out << _dx;
}


void ClientCommunicator::operator<<(QDataStream& in)
{
    in >> _dx;
}


QDataStream & operator>>(QDataStream & in, ClientCommunicator & client)
{
    client<<in;
    return in;
}

QDataStream & operator<<(QDataStream & out, const ClientCommunicator & client)
{
    client>>out;
    return out;
}
