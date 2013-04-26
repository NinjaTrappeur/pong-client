#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <QPointF>
#include <math.h>
#include <QLine>

#include "bat.h"

/*!
 * \brief Ensemble de methodes statique permettant de faciliter
 *  les calculs.
 */
class MathUtils
{
public:
    MathUtils();

    /*!
     * \brief Fonction de conversion d'un angle en degres vers un angle en radian.
     * \param degree Angle exprime en degres degres
     * \return Valeur de l'angle en radian
     */
    static double degreeToRadian(double degree);

    /*!
     * \brief Fonction de conversion d'un angle en radian vers un angle en degres.
     * \param radian Angle exprime en radian
     * \return Valeur de l'angle en radian
     */
    static double radianToDegree(double radian);

    /*!
     * \brief Approximation du nombre pi.
     */
    static const double _pi;

    /*!
     * \brief Permet de faire une rotation de angle par rapport à l'origine
     *  d'un point
     * \param point Point sur lequel appliquer la rotation
     * \param angle Angle de la rotation
     * \return Point sur lequel est applique une rotation de angle
     */
    static QPointF rotatePoint(const QPointF& point, qint32 angle);

    /*!
     * \brief Permet de faire une rotation de angle par rapport à l'origine
     *  d'une raquette
     * \param bat Raquette sur laquelle appliquer la rotation
     * \param angle Angle de la rotation
     * \return Raquette sur laquelle est appliquee une rotation de angle
     */
    static Bat rotateBat(Bat &bat, qint32 angle);

    static QLine rotateQLine(QLine &line, qint32 angle);
};

#endif // MATHUTILS_H
