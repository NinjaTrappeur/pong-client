#include "headers/lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(MainWindow *mainWindow, QWidget *parent) :
    ui(new Ui::Lobby),
    _readyToStart(false),
    _mainWindow(mainWindow),
    QWidget(parent)
{
    ui->setupUi(this);
    connect(ui->announceButton, SIGNAL(clicked()), _mainWindow, SLOT(show()));
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::readyToStart()
{
    _readyToStart=true;
}
