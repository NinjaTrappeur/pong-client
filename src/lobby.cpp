#include "headers/lobby.h"
#include "ui_lobby.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QTime>
#include <QDebug>


Lobby::Lobby(MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    _mainWindow(mainWindow),
    _ui(new Ui::Lobby),
    _udpSocket(),
    _multicastAddress("228.5.6.7"),
    _clientRegistered(false)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    _ui->setupUi(this);
    _ui->label->setText("Vous ne vous êtes pas encore annoncé.");
    connect(_ui->quitButton, SIGNAL(clicked()), this , SLOT(close()));
    connect(_ui->announceButton, SIGNAL(clicked()), this, SLOT(announce()));
    connect(this, SIGNAL(start(QString,qint64)), _mainWindow->ui()->label, SLOT(startGame(QString,qint64)));
    connect(this, SIGNAL(showMainWindow()), _mainWindow, SLOT(show()));
    connect(&_udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagrams()));
    _startNetworkConnection();
    QString str;
    _id.setNum(QApplication::applicationPid());
    str.setNum(qrand() % (1000));
    _id.append(str);
}

Lobby::~Lobby()
{
    delete _ui;
}



void Lobby::_startNetworkConnection()
{
    _udpSocket.bind(6665,QUdpSocket::ShareAddress);
    _udpSocket.joinMulticastGroup(_multicastAddress);
}

void Lobby::processDatagrams()
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
        if(strList[0]=="ACK" && strList[1]==_id)
            _ui->label->setText("Enregistré sur le serveur.\n En attente du début de partie.");
        else if(strList[0]=="GO")
            emit start(strList[1], strList[2].toInt());
    }
}

void Lobby::announce()
{
    QString str = QString("HELLO ") + _id;
    QByteArray datagram(str.toStdString().c_str());
    _udpSocket.writeDatagram(datagram,QHostAddress("228.5.6.7"),6665);
}

void Lobby::closeEvent(QCloseEvent *event)
{
    QString str = QString("BYE ") + _id;
    QByteArray datagram(str.toStdString().c_str());
    _udpSocket.writeDatagram(datagram,QHostAddress("228.5.6.7"),6665);
    event->accept();
}
