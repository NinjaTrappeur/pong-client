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
    connect(timer, SIGNAL(timeout()), _ui->label, SLOT(animate()));
    timer->start(17);
}

MainWindow::~MainWindow()
{
    delete _ui;
}
