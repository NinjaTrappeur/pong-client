#include "serversync.h"

#include <QApplication>


#include "serveurcommunicator.h"
#include "clientcommunicator.h"

ServerSync::ServerSync(qreal &dx, QMutex& dxMutex, QVector<Bat> &bats, QPointF &ball, QErrorMessage *errorMessage, PongTypes::E_GameState& gameState, QString& centraltext) :
    _dx(dx),
    _dxMutex(dxMutex),
    _otherPlayersVector(bats),
    _ball(ball),
    _socket(new QTcpSocket),
    _errorMessage(errorMessage),
    _gameState(gameState),
    _centralText(centraltext),
    _stream(_socket),
    _arenaDrawn(false)
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

    _errorMessage->accept();

    //Connectiond des signaux
    connect( this, SIGNAL(connectToHostSignal()), this, SLOT(connectToHost()));
    connect(this, SIGNAL(error(QString)), _errorMessage, SLOT(showMessage(QString)));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(startSync()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleSocketError(QAbstractSocket::SocketError)));

    emit connectToHostSignal();
}

ServerSync::~ServerSync()
{
    _socket->disconnectFromHost();
    _socket->deleteLater();
}

void ServerSync::handleSocketError(QAbstractSocket::SocketError errorCode)
{
    emit(error(QString("Problème avec la socket!: " + QString::number(errorCode))));
}

void ServerSync::startSync()
{
    _stream.resetStatus();
    ServeurCommunicator serveurCommunicator;
    _stream>>serveurCommunicator;
    _otherPlayersVector = serveurCommunicator.batVector();
    _ball = serveurCommunicator.ball();
    _gameState = serveurCommunicator.gameState();
    if(_gameState == PongTypes::INITIALIZING && !_arenaDrawn)
    {
        _arenaDrawn=true;
        emit(readyToBuildArena());
    }
    if(serveurCommunicator.downCounter()>0 && _gameState!=PongTypes::RUNNING)
        _centralText= QString::number(serveurCommunicator.downCounter());
    else
        _centralText="";


    _stream.resetStatus();
    _dxMutex.lock();
    _stream<<_dx;
    _dx=0;
    _dxMutex.unlock();
}

void ServerSync::connectToHost()
{

    if(_host=="")
        _socket->connectToHost(_adress, _port);
    else
        _socket->connectToHost(_host, _port);


}


void ServerSync::changeSocketState(QAbstractSocket::SocketState state)
{
    _centralText= QString("En attente du serveur...\n") + QString("Etat de la socket: ") + QString::number(state);
}
