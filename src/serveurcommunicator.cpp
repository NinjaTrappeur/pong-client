#include "serveurcommunicator.h"

#include <QDebug>
ServeurCommunicator::ServeurCommunicator(QObject *parent) :
    QObject(parent)
{
}

ServeurCommunicator::ServeurCommunicator(QVector<Bat> batVector, QPointF ball, PongTypes::E_GameState gameState, qint32 loserIndex , qint32 playerId, QObject *parent):
    QObject(parent),
    _batVector(batVector),
    _ball(ball),
    _gameState(gameState),
    _loserIndex(loserIndex),
    _playerId(playerId)
{
}

void ServeurCommunicator::operator>>(QDataStream& out)const
{
    out << _playerId << qint32(_batVector.size())<< qint32(_loserIndex) << qint32(_gameState) << _downCounter;
    for(int i=0;i<_batVector.size();++i)
        out<<_batVector[i];
}


void ServeurCommunicator::operator<<(QDataStream& in)
{
    qint32 vectorSize, nbPlayers, loserIndex, gameState;
    in >> _ball >> _playerId >> vectorSize >> nbPlayers >> loserIndex >> gameState >> _downCounter;
    for(int i=0;i<vectorSize;++i)
    {
        Bat bat;
        in >> bat;
        _batVector.push_back(bat);
    }
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

qint32 ServeurCommunicator::downCounter() const
{
    return _downCounter;
}

void ServeurCommunicator::setDownCounter(const qint32 &downCounter)
{
    _downCounter = downCounter;
}

qint32 ServeurCommunicator::playerId() const
{
    return _playerId;
}

void ServeurCommunicator::setPlayerId(const qint32 &playerId)
{
    _playerId = playerId;
}
