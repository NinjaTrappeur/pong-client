#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scene.h"

#include<QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(this, SIGNAL(startRender(QString,qint16)), _ui->label, SLOT(startGame(QString,qint16)));
    connect(timer, SIGNAL(timeout()), _ui->label, SLOT(animate()));
    timer->start(17);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

Ui::MainWindow *MainWindow::ui() const
{
    return _ui;
}

void MainWindow::setUi(Ui::MainWindow *ui)
{
    _ui = ui;
}

void MainWindow::startGame(QString address, qint16 port)
{
    this->show();
    emit(startRender(address,port));
}
