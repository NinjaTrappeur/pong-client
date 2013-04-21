#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>

#include "mainwindow.h"

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT
    
public:
    explicit Lobby(MainWindow* mainWindow, QWidget *parent = 0);
    ~Lobby();
    
private:
    Ui::Lobby *ui;
    bool _readyToStart;
    MainWindow* _mainWindow;

public slots:
    void readyToStart();
};

#endif // LOBBY_H
