#include "scene.h"

#include <QBrush>
#include <QPen>
#include <QColor>


Scene::Scene(QWidget *parent):
    QWidget(parent),
    _whitePen(QColor(255,255,255)),
    _arena(NULL),
    _errorMessage(new QErrorMessage()),
    _dx(0),
    _centralText("En attente du serveur..."),
    _serverSync(_dx, _dxMutex, _otherPlayersBatVector, _ball, _errorMessage, _gameState, _centralText)
{
    //Initialisation GUI

    _ball.setX(50);
    _ball.setY(50);

    _whitePen.setWidth(4);
    _whitePen.setStyle(Qt::SolidLine);
    _whitePen.setCapStyle(Qt::SquareCap);

    //Initialisation reseau
    connect(&_serverSync,SIGNAL(readyToBuildArena()), this, SLOT(initializeArena()));
}

Scene::~Scene()
{
    _errorMessage->deleteLater();
    if(_arena!=NULL)
        delete _arena;
}

void Scene::paint(QPainter *painter)
{
    painter->setPen(_whitePen);

    if(_arena!=NULL)
    {
        painter->setPen(_whitePen);
        for(int i=0;i<_graphicsBatVector.size();++i)
        {
            painter->drawLine(_graphicsBatVector[i]);
        }
        painter->drawPoint(_ball);
        _arena->paint(painter);
    }
    painter->drawText(QRect(QPoint(200,200), QPoint(400,400)),_centralText);
}

void Scene::addBat(Bat& bat) throw(JobCannotBeDone)
{
    int i = 0;
    while(i<_otherPlayersBatVector.size())
    {
        if(_otherPlayersBatVector[i].getId()==bat.getId())
            throw(JobCannotBeDone(QString("Bat already exist!")));
        ++i;
    }
    _otherPlayersBatVector.push_back(bat);
    _drawBats();
}

void Scene::addBall(QPointF &ball)
{
  _ball = ball;
}

void Scene::moveBall(QPointF &newPos)
{
  _ball = newPos;
}

void Scene::moveBat(int id, QPointF &pos1, QPointF &pos2) throw(JobCannotBeDone)
{
    bool idFound = false;
    int i=0;
    while(i<_otherPlayersBatVector.size())
    {
        if(_otherPlayersBatVector[i].getId()==id)
        {
            _otherPlayersBatVector[i].moveBat(pos1, pos2);
            idFound=true;
        }
        ++i;
    }
    if(!idFound)
        throw(JobCannotBeDone(QString("Can't find bat id ")+QString::number(id)));
    _drawBats();
}

void Scene::moveBat(int id, QVector<QPointF> &newPos) throw(JobCannotBeDone)
{
    if(newPos.size()!=2)
        throw(JobCannotBeDone(QString("moveBat funtion need 2 points, not ")+QString::number(newPos.size())));
    try{
        moveBat(id, newPos[0], newPos[1]);
    }
    catch(JobCannotBeDone &exception)
    {
        throw(exception);
    }
}

void Scene::_drawBats()
{
    if(_graphicsBatVector.size()>0)
        _graphicsBatVector.clear();
    QVector<QPointF> points;
    for(int i=0; i<_otherPlayersBatVector.size(); ++i)
    {
        points=_otherPlayersBatVector[i].getPoints();
        QLine bat(QPoint(points[0].x(), points[0].y()),
                    QPoint(points[1].x(), points[1].y()));
        _graphicsBatVector.push_back(bat);
    }

    points=_playerBat.getPoints();
    QLine playerGraphicBat(QPoint(points[0].x(), points[0].y()),
            QPoint(points[1].x(), points[1].y()));
    _graphicsBatVector.push_back(playerGraphicBat);
}

void Scene::setPlayerBat(QPointF &pos1, QPointF &pos2)
{
    _playerBat.moveBat(pos1,pos2);
}

void Scene::movePlayerBatToLeft(float pos)
{
    QVector<QPointF> actualPosition;
    actualPosition= _playerBat.getPoints();
    if((actualPosition[0].x()-pos)>_arena->leftBatLimit() &&
            (actualPosition[1].x()-pos)>_arena->leftBatLimit())
    {
        actualPosition[0].setX(actualPosition[0].x()-pos);
        actualPosition[1].setX(actualPosition[1].x()-pos);
        _playerBat.moveBat(actualPosition[0], actualPosition[1]);
        _dxMutex.lock();
        _dx-=pos;
        _dxMutex.unlock();
        _drawBats();
    }
}

void Scene::movePlayerBatToRight(float pos)
{
    QVector<QPointF> actualPosition;
    actualPosition= _playerBat.getPoints();
    if((actualPosition[0].x()+pos)<_arena->rightBatLimit() &&
            (actualPosition[1].x()+pos)<_arena->rightBatLimit())
    {
        actualPosition[0].setX(actualPosition[0].x()+pos);
        actualPosition[1].setX(actualPosition[1].x()+pos);
        _playerBat.moveBat(actualPosition[0], actualPosition[1]);
        _dxMutex.lock();
        _dx+=pos;
        _dxMutex.unlock();
        _drawBats();
    }
}

void Scene::initializeArena()
{
    _arena = new Arena(_otherPlayersBatVector.size()+1);
    _playerBat=_arena->playerBat();
    _drawBats();
}
