#ifndef MATHUTILS_H
#define MATHUTILS_H

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
};

#endif // MATHUTILS_H
