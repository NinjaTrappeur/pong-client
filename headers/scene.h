#ifndef _SCENE_H
#define _SCENE_H

#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPainter>
#include <QLine>
#include <QString>
#include <QErrorMessage>
#include <QMutex>
#include <QThread>

#include "bat.h"
#include "arena.h"
#include "jobcannotbedone.h"
#include "serversync.h"
#include "PongTypes.hpp"

/*!
 * \brief Classe Scene. Classe contenant les objets (la balle et les raquettes)
 *  qu'il faudra afficher a l'ecran.
 */
class Scene : public QWidget
{
    Q_OBJECT
public:

    /*!
     * \brief Constructeur de la scene.
     */
    Scene(QWidget *parent, QHostAddress address, qint16 port);

    /*!
     * \brief Destructeur.
     */
    virtual ~Scene();

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

    /*!
     * \brief Deplace la raquette du joueur a une certaine position
     * \param pos Position ou deplacer la raquette du joueur.
     */
    void movePlayerBat(qreal pos);
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
     * \brief Objet representant l'arenne de jeu.
     */
    Arena* _arena;

    /*!
     * \brief Message d'erreur, utilise pour afficher les erreurs.
     */
    QErrorMessage* _errorMessage;

    /*!
     * \brief Difference entre la position actuelle de la raquette et la derniere
     *  position envoyee au serveur.
     */
    qreal _dx;

    /*!
     * \brief Mutex permettant de verouiller _dx.
     */
    QMutex _dxMutex;

    /*!
     * \brief Texte qui sera affiché au centre de l'aire de jeu
     */
    QString _centralText;

    /*!
     * \brief Identifiant du joueur local.
     */
    qint32 _playerId;

    /*!
     * \brief Objet realisant les operations reseau. Sera lance dans un fil d'execution different.
     */
    ServerSync _serverSync;

    /*!
     * \brief Etat de la partie.
     */
    PongTypes::E_GameState _gameState;



    /*!
     * \brief Methode auxilere qui permet de generer les objets graphiques representant les raquettes.
     */
    void _drawBats();

public slots:

    /*!
     * \brief Cree l'arene et place la raquette du joueur a sa position initiale.
     */
    void initializeArena();

    /*!
     * \brief Permet au serversync de rafraichir la position des raquettes.
     */
    void drawBats();
};

#endif // SCENE_H
