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
    lobby.show();


    return a.exec();

}
