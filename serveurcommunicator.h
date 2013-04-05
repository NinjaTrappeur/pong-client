#ifndef SERVEURCOMMUNICATOR_H
#define SERVEURCOMMUNICATOR_H

#include <QObject>
#include <QVector>
#include <QLineF>
#include "GameState.hpp"

class ServeurCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ServeurCommunicator(QObject *parent = 0);

    void operator>>(QDataStream & out)const;
    void operator<<(QDataStream & in);

    friend QDataStream & operator>>(QDataStream & in, ServeurCommunicator & client);
    friend QDataStream & operator<<(QDataStream & out, const ServeurCommunicator & client);
    
private:
    int _nbPlayers;
    QVector<QLineF> _batVector;
    PongTypes::E_GameState _gameState;
    int _loserIndex;

signals:
    
public slots:
    
};

#endif // SERVEURCOMMUNICATOR_H
