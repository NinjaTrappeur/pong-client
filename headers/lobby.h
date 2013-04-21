#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QUdpSocket>
#include <QHostAddress>

#include "mainwindow.h"

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT
    
public:
    explicit Lobby(MainWindow* mainWindow, QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~Lobby();
    
private:
    MainWindow* _mainWindow;
    Ui::Lobby *_ui;
    QUdpSocket _udpSocket;
    QHostAddress _multicastAddress;
    bool _clientRegistered;
    qint64 _id;

    void _startNetworkConnection();

public slots:
    void processDatagrams();
    void announce();

signals:
    void start(QString address, qint64 port);
    void showMainWindow();
};

#endif // LOBBY_H
