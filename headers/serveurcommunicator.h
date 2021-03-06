#ifndef SERVEURCOMMUNICATOR_H
#define SERVEURCOMMUNICATOR_H

#include <QObject>
#include <QVector>
#include <QLineF>
#include <QDataStream>

#include "GameState.hpp"
#include "bat.h"

/*!
 * \brief Classe envoyee dans le reseau par le serveur vers le client
 */
class ServeurCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ServeurCommunicator(QObject *parent = 0);
    ServeurCommunicator(QVector<Bat> batVector, QPointF ball, PongTypes::E_GameState gameState, qint32 loserIndex, qint32 playerId, QObject *parent = 0);
    /*!
     * \brief Definition du flux sortant pour cette classe. Permet d'envoyer la classe dans une socket de maniere
     *  aisee
     * \param out Flux sortant
     */
    void operator>>(QDataStream & out)const;

    /*!
     * \brief Definition du flux sortant pour cette classe. Permet de lire la classe depuis une socket de maniere
     *  aisee.
     * \param in
     */
    void operator<<(QDataStream & in);

    friend QDataStream & operator>>(QDataStream & in, ServeurCommunicator & client);
    friend QDataStream & operator<<(QDataStream & out, const ServeurCommunicator & client);
    
    int nbPlayers() const;
    void setNbPlayers(int nbPlayers);

    QVector<Bat> batVector() const;
    void setBatVector(const QVector<Bat> &batVector);

    PongTypes::E_GameState gameState() const;
    void setGameState(const PongTypes::E_GameState &gameState);

    int loserIndex() const;
    void setLoserIndex(int loserIndex);

    QPointF ball() const;
    void setBall(const QPointF &ball);

    qint32 downCounter() const;
    void setDownCounter(const qint32 &downCounter);

    qint32 playerId() const;
    void setPlayerId(const qint32 &playerId);

    bool gameOverPlayer() const;
    void setGameOverPlayer(bool gameOverPlayer);

private:

    /*!
     * \brief Raquettes des differents joueurs
     */
    QVector<Bat> _batVector;

    /*!
     * \brief Position de la balle.
     */
    QPointF _ball;

    /*!
     * \brief Etat du jeu
     */
    PongTypes::E_GameState _gameState;

    /*!
     * \brief Joueurs ayant deja perdu
     */
    qint32 _loserIndex;

    /*!
     * \brief Numero du joueur local
     */
    qint32 _playerId;

    /*!
     * \brief Vrai si le joueur local a perdu la partie.
     */
    bool _gameOverPlayer;

    /*!
     * \brief Decompte avant la partie.
     */
    qint32 _downCounter;
};

#endif // SERVEURCOMMUNICATOR_H
