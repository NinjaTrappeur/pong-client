#ifndef SERVERSYNC_H
#define SERVERSYNC_H

#include <QObject>
#include <QPointF>
#include <QErrorMessage>
#include <QString>
#include <QMutex>
#include <QDataStream>

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#include "bat.h"
#include "PongTypes.hpp"


/*!
 * \brief Classe gerant la liaison avec le serveur sur un reseau. Permet d'envoyer la position
 *  de la raquette du joueur local au serveur et de recuperer la position des autres raquettes et de la balle.
 *  Doit etre lance dans un thread a part a l'aide du slot startSync().
 */
class ServerSync : public QObject
{
    Q_OBJECT
public:
    explicit ServerSync(qreal& dx, QMutex &dxMutex,  QVector<Bat>& bats, QPointF& ball, QErrorMessage* errorMessage, PongTypes::E_GameState& gamestate, QString& _centralText);
    virtual ~ServerSync();

private:
    /*!
     * \brief Difference entre la derniere position de la raquette du joueur envoyee au serveur et
     *  la position actuelle de la raquette du joueur.
     */
    qreal& _dx;

    /*!
     * \brief Mutex permettant de verouiller _dx.
     */
    QMutex& _dxMutex;
    /*!
     * \brief Vecteur contenant les positions des raquettes des autres joueurs.
     */
    QVector<Bat>& _otherPlayersVector;

    /*!
     * \brief Position de la balle.
     */
    QPointF& _ball;

    /*!
     * \brief Socket permettant de communiquer avec le serveur.
     */
    QTcpSocket* _socket;

    /*!
     * \brief Fenetre pour les messages d'erreur.
     */
    QErrorMessage* _errorMessage;

    /*!
     * \brief Port d'ecoute du serveur
     */
    quint16 _port;

    /*!
     * \brief Adresse ipv4 du serveur
     */
    QHostAddress _adress;

    /*!
     * \brief Nom du serveur
     */
    QString _host;

    /*!
     * \brief Etat de la partie
     */
    PongTypes::E_GameState& _gameState;

    /*!
     * \brief Texte affiché au centre de la fenetre
     */
    QString& _centralText;

    QDataStream _stream;

signals:
    void error(QString error);
    void readyToBuildArena();
    void connectToHostSignal();
    
public slots:


    /*!
     * \brief Slot qui lance la scrutation de la socket
     */
    void startSync();

    /*!
     * \brief Connecte la socket au serveur.
     */
    void connectToHost();

    /*!
     * \brief Slot permettant de recuperer les erreurs generes par le socket.
     */
    void handleSocketError(QAbstractSocket::SocketError errorCode);

    /*!
     * \brief Slot permettant de donner l'état de la socket à l'utilisateur.
     */
    void changeSocketState(QAbstractSocket::SocketState state);

};

#endif // SERVERSYNC_H
