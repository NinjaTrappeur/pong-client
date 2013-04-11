#include "serversync.h"

#include <QApplication>

#include "serveurcommunicator.h"
#include "clientcommunicator.h"

ServerSync::ServerSync(qreal &dx, QMutex& dxMutex, QVector<Bat> &bats, QPointF &ball, QErrorMessage *errorMessage) :
    _dx(dx),
    _dxMutex(dxMutex),
    _otherPlayersVector(bats),
    _ball(ball),
    _socket(new QTcpSocket()),
    _errorMessage(errorMessage),
    _timer()
{
    //Recuperation des parametres de connection

    for(int i=1; i<QApplication::arguments().size(); i+=2)
    {
        if(QApplication::arguments().at(i)=="-p")
            _port=QApplication::arguments().at(i+1).toInt();
        else if(QApplication::arguments().at(i)=="-h")
            _host=QApplication::arguments().at(i+1);
        else if(QApplication::arguments().at(i)=="-a")
            _adress=QApplication::arguments().at(i+1);
    }

    //Connectiond des signaux
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(error(QString)), _errorMessage, SLOT(showMessage(QString)));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(startSync()));
}

ServerSync::~ServerSync()
{
    _socket->disconnectFromHost();
    _socket->deleteLater();
}

void ServerSync::handleSocketError(QAbstractSocket::SocketError)
{
    emit(error(QString("Problème avec la socket!")));
}

void ServerSync::startSync()
{
    ServeurCommunicator serveurCommunicator;
    QDataStream stream(_socket);
    stream>>serveurCommunicator;
    _otherPlayersVector = serveurCommunicator.batVector();
    _ball = serveurCommunicator.ball();
    _dxMutex.lock();
    ClientCommunicator clientCommunicator(_dx);
    stream<<clientCommunicator;
    _dx=0;
    _dxMutex.unlock();
}

void ServerSync::launchTimer()
{
    _timer.start(50);
}

void ServerSync::connectToHost()
{


    if(_host=="")
        _socket->connectToHost(_adress, _port);
    else
        _socket->connectToHost(_host, _port);
    connect(_socket, SIGNAL(connected()), this, SLOT(launchTimer()));
}
