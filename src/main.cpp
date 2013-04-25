#include "mainwindow.h"
#include "lobby.h"

#include <QApplication>
#include <iostream>
#include <cstring>
#include <QTextCodec>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    Lobby lobby;
    QObject::connect(&lobby, SIGNAL(startGame(QString,qint16)), &w, SLOT(startGame(QString,qint16)));
    lobby.show();


    return a.exec();

}
