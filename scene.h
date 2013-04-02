#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QLine>

#include "bat.h"
#include "jobcannotbedone.h"

/*!
 * \brief Classe Scene. Classe contenant les objets (la balle et les raquettes)
 *  qu'il faudra afficher a l'ecran.
 */

class Scene
{

public:

    /*!
     * \brief Constructeur de la scene.
     */
    Scene();

    /*!
     * \brief Methode appellee par le renderlabel qui est associe a cette scene.
     *  Le but principal de cette methode est dessiner tous les elements presents
     *  dans la scene.
     *
     * \param painter Pointeur vers le painter qu'il faudra utiliser pour dessiner la scene.
     */
    void paint(QPainter* painter);

    /*!
     * \brief Ajoute une raquette dans la scene. (peut lever une exception si on ajoute
     *  une raquette qui existe deja)
     *
     * \param bat Raquette a ajouter
     */
    void addBat(Bat& bat) throw(JobCannotBeDone);

    /*!
     * \brief Ajoute une balle a la scene. (utilise seulement pour une version multiballes)
     *
     * \param ball Position de la balle a ajouter.
     */
    void addBall(QPointF& ball);

    /*!
     * \brief Change la position de la balle.
     *
     * \param newPos Nouvelle position de la balle.
     */
    void moveBall(QPointF& newPos);

    /*!
     * \brief Change la position d'une raquette.
     *
     * \param id Id de la raquette a deplacer.
     * \param pos1 Nouvelle position de l'extremite gauche de la raquette.
     * \param pos2 Nouvelle position de l'extremite droite de la raquette.
     */
    void moveBat(int id, QPointF& pos1, QPointF& pos2) throw(JobCannotBeDone);

    /*!
     * \brief Change la position de la raquette.
     *
     * \param id Id de la raquette a deplacer.
     * \param newPos Vecteur contenant les positions des deux extremites de la raquette.
     */
    void moveBat(int id, QVector<QPointF>& newPos) throw(JobCannotBeDone);

    /*!
     * \brief Change la position de la raquette du joueur local.
     *
     * \param pos1 Nouvelle position de l'extremite gauche de la raquette.
     * \param pos2 Nouvelle position de l'extremite droite de la raquette.
     */
    void setPlayerBat(QPointF& pos1, QPointF& pos2);

    /*!
     * \brief Deplace la raquette du joueur local vers la droite.
     * \param pos Distance a laquelle on veut decaler la raquette.
     */
    void movePlayerBatToRight(float pos);

    /*!
     * \brief Deplace la raquette du joueur local vers la gauche.
     * \param pos Distance a laquelle on veut decaler la raquette.
     */
    void movePlayerBatToLeft(float pos);
private:
    /*!
     * \brief Stylo blanc utilise pour dessiner les raquettes et les balles.
     */
    QPen _whitePen;

    /*!
     * \brief Raquette du joueur local.
     */
    Bat _playerBat;

    /*!
     * \brief Vecteur contenant les raquettes des autres joueurs.
     */
    QVector<Bat> _otherPlayersBatVector;

    /*!
     * \brief Point représentant la position de la balle.
     */
    QPointF _ball;

    /*!
     * \brief Vecteur contenant les objets graphiques représentant les raquettes.
     */
    QVector<QLine> _graphicsBatVector;

    /*!
     * \brief Methode auxilere qui permet de generer les objets graphiques representant les raquettes.
     */
    void _drawBats();
};

#endif // SCENE_H