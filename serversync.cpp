#include "serversync.h"

#include <QApplication>

#include "mathutils.h"

ServerSync::ServerSync(Bat &playerBat, QMutex& dxMutex, QVector<Bat> &bats, QPointF &ball, QErrorMessage *errorMessage, PongTypes::E_GameState& gameState, QString& centraltext, qint32 &playerId) :
    _playerBat(playerBat),
    _dxMutex(dxMutex),
    _otherPlayersVector(bats),
    _ball(ball),
    _socket(new QTcpSocket),
    _errorMessage(errorMessage),
    _gameState(gameState),
    _centralText(centraltext),
    _stream(_socket),
    _arenaDrawn(false),
    _playerId(playerId)
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


    _stream.resetStatus();
    qint32 angle;
    if( (_otherPlayersVector.size()+1) == 2 && _playerId==1)
        angle=180;
    else
        angle=-(_playerId*(360/(_otherPlayersVector.size()+1)));
    Bat playerBat=MathUtils::rotateBat( _playerBat, angle);
    _dxMutex.lock();
    _stream<<playerBat;
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
}
