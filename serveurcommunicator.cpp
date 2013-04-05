#include "serveurcommunicator.h"

ServeurCommunicator::ServeurCommunicator(QObject *parent) :
    QObject(parent)
{
}

void ServeurCommunicator::operator>>(QDataStream& out)const
{
    out << quint16(_batVector.size())<< quint16(_nbPlayers) << quint16(_loserIndex) << quint16(_gameState);
    for(int i=0;i<_batVector.size();++i)
        out<<_batVector[i];
}


void ServeurCommunicator::operator<<(QDataStream& in)
{
    qint32 vectorSize, nbPlayers, loserIndex, gameState;
    in >> vectorSize;
    in >> nbPlayers >> loserIndex >> gameState;
    for(int i=0;i<vectorSize;++i)
        in >> _batVector[i];
    _nbPlayers=nbPlayers;
    _loserIndex=loserIndex;
    _gameState= (PongTypes::E_GameState)gameState;
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
