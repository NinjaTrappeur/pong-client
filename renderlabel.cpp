#include "renderlabel.h"

RenderLabel::RenderLabel(QWidget *parent):
    _parent(parent),
    QLabel(parent)
{
    _scene= new Scene;
    setFocusPolicy(Qt::StrongFocus);
}

RenderLabel::~RenderLabel()
{
    delete _scene;
}

void RenderLabel::paintEvent(QPaintEvent *event)
{
    if(_scene!=NULL)
    {
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing);
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