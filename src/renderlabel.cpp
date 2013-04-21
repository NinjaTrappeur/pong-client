#include "renderlabel.h"

RenderLabel::RenderLabel(QWidget *parent):
    QLabel(parent)
{
}

RenderLabel::~RenderLabel()
{
    delete _scene;
}

void RenderLabel::startGame(QString address, qint64 port)
{
    _scene= new Scene(this, address, port);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void RenderLabel::paintEvent(QPaintEvent *event)
{
    if(_scene!=NULL)
    {
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate(600/2,600/2);
        _scene->paint(&painter);
        painter.end();
    }
}

void RenderLabel::animate()
{
    repaint();
}

void RenderLabel::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
        case Qt::Key_Right:
        _scene->movePlayerBatToRight(5);
        break;

        case Qt::Key_Left:
        _scene->movePlayerBatToLeft(5);
        break;
    }
}

void RenderLabel::mouseMoveEvent(QMouseEvent *ev)
{
    _scene->movePlayerBat(ev->x()-300);
}
