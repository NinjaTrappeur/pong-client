#ifndef SERVEURCOMMUNICATOR_H
#define SERVEURCOMMUNICATOR_H

#include <QObject>
#include <QVector>
#include <QLineF>

//#include "PongTypes.hpp"

class ServeurCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ServeurCommunicator(QObject *parent = 0);
    
private:
    int _nbPlayers;
    QVector<QLineF> _batVector;
    //PongTypes::E_GameState _gameState;
    int _loserIndex;

signals:
    
public slots:
    
};

#endif // SERVEURCOMMUNICATOR_H
