#include "arena.h"
#include "mathutils.h"

#include <cmath>
#include <QPointF>

const double Arena::_renderWidth = 600;

const double Arena::_renderLenght = 600;

Arena::Arena(int nbPlayers): _nbPlayers(nbPlayers)
{
    _drawSide();
}

void Arena::paint(QPainter *painter)
{
    painter->translate(_renderWidth/2,_renderLenght/2);
    for(int i=0; i<_nbPlayers; ++i)
    {
        painter->drawLine(_arenaLines[0]);
        painter->drawLine(_arenaLines[1]);
        //painter->drawLine(_arenaLines[2]);
        painter->rotate(360/_nbPlayers);
    }
    painter->translate(-_renderWidth/2,_renderLenght/2);
}

void Arena::_drawSide()
{

    //Calcul des constantes;
    const double alphaAngle = 360/_nbPlayers;
    const double betaAngle = (180-alphaAngle)/2;
    const double radius = _renderWidth/2;
    const double x = radius*(::sin( MathUtils::degreeToRadian(alphaAngle) )/::sin( MathUtils::degreeToRadian(betaAngle) ));
    const double h = radius*::cos( MathUtils::degreeToRadian(alphaAngle/2) );

    //Determinaion des points (cf schema)
    QPoint a(-(x/2),h);
    QPoint b((x/2),h);
    //QPoint c(0,h);
    QPoint f1(-(x/4),h);
    QPoint f2((x/4),h);
    _leftBatLimit = radius-(x/4);
    _rightBatLimit = radius+(x/4);

    //Generation des droites
    QLine l1(a,f1);
    QLine l2(f2,b);
    //QLine l3(QPoint(0,0), c);

    //Ajout des droites dans le vecteur
    _arenaLines.push_back(l1);
    _arenaLines.push_back(l2);
    // _arenaLines.push_back(l3);

    //Calcul de la position initiale de la raquette du joueur local
    const double batLength = x/6;
    QPointF leftPoint(-(batLength/2)+radius,radius+h);
    QPointF rightPoint((batLength/2)+radius,radius+h);
    _playerBat=Bat(leftPoint,rightPoint,0);
}

Bat Arena::playerBat() const
{
    return _playerBat;
}

void Arena::setPlayerBat(const Bat &playerBat)
{
    _playerBat = playerBat;
}

double Arena::rightBatLimit() const
{
    return _rightBatLimit;
}

void Arena::setRightBatLimit(double rightBatLimit)
{
    _rightBatLimit = rightBatLimit;
}

double Arena::leftBatLimit() const
{
    return _leftBatLimit;
}

void Arena::setLeftBatLimit(double leftBatLimit)
{
    _leftBatLimit = leftBatLimit;
}
