#ifndef ARENA_H
#define ARENA_H

#include <QPainter>
#include <QPen>
#include <QVector>
#include <QLine>

#include "bat.h"

/*!
 * \brief Classe representant l'arene dans laquelle va se derouler le jeu de pong.
 */

class Arena
{
public:
    /*!
     * \brief Constructeur
     * \param nbPlayers Nombre de joueurs dans la partie.
     */
    Arena(QVector<QLine>& batVector, bool& gameOver, qint32& playerId);

    /*!
     * \brief Peint l'arene.
     * \param painter Painter dans lequel on doit tracer l'arene.
     * \param pen Stylo a utiliser pour dessiner l'arene.
     */
    void paint(QPainter* painter);

    /*!
     * \brief Donne la raquette du joueur local dans sa position initiale.
     * \return Raquette du joueur local.
     */

    Bat playerBat() const;
    void setPlayerBat(const Bat &playerBat);

    double leftBatLimit() const;
    void setLeftBatLimit(double leftBatLimit);

    double rightBatLimit() const;
    void setRightBatLimit(double rightBatLimit);

protected:

    /*!
     * \brief Nombre de joueurs dans la partie.
     */
    QVector<QLine>& _batVector;

    /*!
     * \brief Nombre de joueurs dans la partie.
     */
    int _nbPlayers;

    /*!
     * \brief Lignes représentant l'arene.
     */
    QVector<QLine> _arenaLines;

    /*!
     * \brief Cree les lignes representant une face de l'arene.
     */
    void _drawSide();

    /*!
     * \brief Largeur de la fenetre de rendu.
     */
    static const double _renderWidth;

    /*!
     * \brief Longueur de la fenetre de rendu.
     */
    static const double _renderLenght;

    /*!
     * \brief Raquette du joueur dans sa position initiale.
     */
    Bat _playerBat;

    /*!
     * \brief Position butoir du cote gauche de la batte du joueur local.
     */
    double _leftBatLimit;

    /*!
     * \brief Position butoir du cote gauche de la batte du joueur local.
     */
    double _rightBatLimit;

    /*!
     * \brief Vrai si le joueur local a perdu.
     */
    bool& _playerGameOver;

    /*!
     * \brief ID du joueur.
     */
    qint32& _playerId;
};

#endif // ARENA_H
