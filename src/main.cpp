#include "mainwindow.h"
#include "lobby.h"

#include <QApplication>
#include <iostream>
#include <cstring>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

    MainWindow w;
    Lobby lobby(&w);
    lobby.show();

    return a.exec();
}
