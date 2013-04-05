#include "serversync.h"

#include "serveurcommunicator.h"
#include "clientcommunicator.h"

ServerSync::ServerSync(float &dx, QVector<Bat> &bats, QPointF &ball, QHostAddress serverAdress, quint16 port, QErrorMessage *errorMessage, QObject *parent) :
    _dx(dx),
    _otherPlayersVector(bats),
    _ball(ball),
    _errorMessage(errorMessage),
    QObject(parent)
{
    _socket = new QTcpSocket;
    _socket->connectToHost(serverAdress, port);

    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(startSync()));
    connect(this, SIGNAL(error(QString)), _errorMessage, SLOT(showMessage(QString)));
}

ServerSync::~ServerSync()
{
    _socket->disconnectFromHost();
    _socket->deleteLater();
}

void ServerSync::handleSocketError(QAbstractSocket::SocketError)
{
    emit(QString("Problème avec la socket!"));
}

void ServerSync::startSync()
{
    ServeurCommunicator serveurCommunicator;

    *_socket>>serveurCommunicator;
    _otherPlayersVector = serveurCommunicator.batVector();
    _ball = serveurCommunicator.ball();

    ClientCommunicator clientCommunicator(_dx);
    *_socket<<clientCommunicator;
}
