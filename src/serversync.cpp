#include "serversync.h"

#include <QApplication>
#include <QTimer>
#include <QByteArray>

#include "mathutils.h"

ServerSync::ServerSync(Bat &playerBat, QMutex& dxMutex, QVector<Bat> &bats, QPointF &ball, QErrorMessage *errorMessage, PongTypes::E_GameState& gameState, qint16 port, QHostAddress address, QString& centraltext, qint32 &playerId, bool &gameOver) :
    _playerBat(playerBat),
    _dxMutex(dxMutex),
    _otherPlayersVector(bats),
    _ball(ball),
    _socket(new QTcpSocket),
    _errorMessage(errorMessage),
    _port(port),
    _adress(address),
    _gameState(gameState),
    _centralText(centraltext),
    _arenaDrawn(false),
    _playerId(playerId),
    _gameoverLocalPlayer(gameOver)
{
    //Recuperation des parametres de connection
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
    QDataStream socketStream(_socket);
    QByteArray byteArray;
    QDataStream byteArrayStream(&byteArray, QIODevice::ReadWrite);
    ServeurCommunicator serveurCommunicator;

    socketStream >> byteArray;
    byteArrayStream >> serveurCommunicator;

    _parseServeurCommunicator(serveurCommunicator);

    if(_gameState == PongTypes::INITIALIZING && !_arenaDrawn)
    {
        _arenaDrawn=true;
        emit(readyToBuildArena());
    }
    if(serveurCommunicator.downCounter()>0 && _gameState!=PongTypes::RUNNING)
        _centralText= QString::number(serveurCommunicator.downCounter());
    else
        _centralText="";
    emit newBatsPosition();
    emitSync();
}

void ServerSync::emitSync(){
    QDataStream socketStream(_socket);
    QByteArray byteArray;
    QDataStream byteArrayStream(&byteArray, QIODevice::ReadWrite);

    qint32 angle;

    if( (_otherPlayersVector.size()+1) == 2 && _playerId==1)
        angle=180;
    else
        angle=(_playerId*(360/(_otherPlayersVector.size()+1)));
    Bat playerBat=MathUtils::rotateBat( _playerBat, angle);

    _dxMutex.lock();
    byteArrayStream << playerBat;
    socketStream << byteArray;
    _dxMutex.unlock();
}

void ServerSync::connectToHost()
{
    _socket->connectToHost(_adress, _port);
}


void ServerSync::changeSocketState(QAbstractSocket::SocketState state)
{
    _centralText= QString("En attente du serveur...\n") + QString("Etat de la socket: ") + QString::number(state);
}

void ServerSync::_parseServeurCommunicator(ServeurCommunicator &serveurCommunicator)
{
    qint32 nbPlayers = serveurCommunicator.batVector().size()+1;
    qint32 angle=0, id=serveurCommunicator.playerId();
    if(nbPlayers==2 && id==1)
        angle=180;
    else
        angle=-(id*(360/nbPlayers));
    QVector<Bat> otherPlayersVector(serveurCommunicator.batVector().size());
    for(qint32 i=0;i<serveurCommunicator.batVector().size();++i)
    {
        otherPlayersVector[i]=MathUtils::rotateBat( serveurCommunicator.batVector()[i], angle);

    }
    _otherPlayersVector = otherPlayersVector;
    _ball = MathUtils::rotatePoint(serveurCommunicator.ball(), angle);
    _gameState = serveurCommunicator.gameState();
    _playerId = serveurCommunicator.playerId();
    _gameoverLocalPlayer = serveurCommunicator.gameOverPlayer();
}
