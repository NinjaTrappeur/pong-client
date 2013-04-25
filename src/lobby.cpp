#include "headers/lobby.h"
#include "ui_lobby.h"

#include <QDebug>
#include <QTimer>

Lobby::Lobby(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::Lobby),
    _udpSocket(),
    _multicastAddress("228.5.6.7"),
    _localPort(6665),
    _serverPort(6665)
{
    _ui->setupUi(this);
    _ui->label->setText("Vous ne vous êtes pas encore annoncé.");
    connect(_ui->connectButton, SIGNAL(clicked()), this, SLOT(parseDirectConnection()));
    connect(_ui->quitButton, SIGNAL(clicked()), this , SLOT(close()));
    connect(_ui->announceButton, SIGNAL(clicked()), this, SLOT(announce()));
    connect(&_udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagram()));
    connect(this, SIGNAL(serverLost()), this, SLOT(resetGlobalState()));
    _id.setNum(QApplication::applicationPid());
    _startNetworkConnection();
}

Lobby::~Lobby()
{
    delete _ui;
}

void Lobby::_startNetworkConnection()
{
    _udpSocket.bind(_localPort,QUdpSocket::ShareAddress);
    _udpSocket.joinMulticastGroup(_multicastAddress);
}

void Lobby::processDatagram()
{
    QString str;
    QStringList strList;
    while (_udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpSocket.pendingDatagramSize());
        _udpSocket.readDatagram(datagram.data(), datagram.size());
        str=datagram.data();
        strList=str.split(" ");
        if(strList[0]=="SERVER" && strList[1]==_id)
        {
            _ui->label->setText("Enregistré sur le serveur.\n En attente du début de partie.");
            _ui->announceButton->setEnabled(false);
            _serverAddress=strList[3];
            _serverPort=strList[2].toInt();
            _udpSocket.leaveMulticastGroup(_multicastAddress);
            disconnect(&_udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagram()));
            connect(&_udpSocket, SIGNAL(readyRead()), this, SLOT(readServerSync()));
            _packetsEmited=0;
            synchroniseWithServer();
        }
    }
}

void Lobby::announce()
{
    QString str = QString("HELLO ") + _id + QString(_localPort) + QNetworkInterface::allAddresses()[2].toString();
    QByteArray datagram(str.toStdString().c_str());
    _udpSocket.writeDatagram(datagram,_multicastAddress,6665);
}

void Lobby::acknowledgeServer()
{
    QString str = "ACK" + _id;
    QByteArray datagram(str.toStdString().c_str());
    _udpSocket.writeDatagram(datagram, QHostAddress(_serverAddress),_serverPort);
    _packetsEmited++;
    synchroniseWithServer();
}

void Lobby::readServerSync()
{
    QString str;
    QStringList strList;
    while (_udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udpSocket.pendingDatagramSize());
        _udpSocket.readDatagram(datagram.data(), datagram.size());
        str=datagram.data();
        strList=str.split(" ");
        if(strList[0]=="SYNC" && strList[1]==_id)
        {
            _packetsEmited = 0;
        }
    }
}

void Lobby::synchroniseWithServer()
{
    if(_packetsEmited<8)
        QTimer::singleShot(100,this,SLOT(acknowledgeServer()));
    else
        emit(serverLost());
}

void Lobby::resetGlobalState()
{
    disconnect(&_udpSocket, SIGNAL(readyRead()), this, SLOT(readServerSync()));
    connect(&_udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagram()));
    _udpSocket.joinMulticastGroup(_multicastAddress);
    _ui->label->setText("Déconnecté du serveur. Veuillez vous reconnecter!");
    _ui->announceButton->setEnabled(true);
}

void Lobby::parseDirectConnection()
{
    QString address = _ui->ipServer->text();
    qint16 port = _ui->portServer->text().toInt();
    emit(startGame(address,port));
    this->close();
}
