#include "serveurcommunicator.h"

ServeurCommunicator::ServeurCommunicator(QObject *parent) :
    QObject(parent)
{
}

ServeurCommunicator::ServeurCommunicator(QVector<Bat> batVector, QPointF ball, PongTypes::E_GameState gameState, quint32 loserIndex , quint32 playerId, QObject *parent):
    _batVector(batVector),
    _ball(ball),
    _gameState(gameState),
    _loserIndex(loserIndex),
    _playerId(playerId),
    QObject(parent)
{
}

void ServeurCommunicator::operator>>(QDataStream& out)const
{
    out << quint16(_batVector.size())<< quint16(_loserIndex) << quint16(_gameState);
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

int ServeurCommunicator::loserIndex() const
{
    return _loserIndex;
}

void ServeurCommunicator::setLoserIndex(int loserIndex)
{
    _loserIndex = loserIndex;
}

PongTypes::E_GameState ServeurCommunicator::gameState() const
{
    return _gameState;
}

void ServeurCommunicator::setGameState(const PongTypes::E_GameState &gameState)
{
    _gameState = gameState;
}

QVector<Bat> ServeurCommunicator::batVector() const
{
    return _batVector;
}

void ServeurCommunicator::setBatVector(const QVector<Bat> &batVector)
{
    _batVector = batVector;
}

QPointF ServeurCommunicator::ball() const
{
    return _ball;
}

void ServeurCommunicator::setBall(const QPointF &ball)
{
    _ball = ball;
}
