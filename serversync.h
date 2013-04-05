#ifndef SERVERSYNC_H
#define SERVERSYNC_H

#include <QObject>
#include <QPointF>
#include <QErrorMessage>
#include <QString>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#include <bat.h>


/*!
 * \brief Classe gerant la liaison avec le serveur sur un reseau. Permet d'envoyer la position
 *  de la raquette du joueur local au serveur et de recuperer la position des autres raquettes et de la balle.
 *  Doit etre lance dans un thread a part a l'aide du slot startSync().
 */
class ServerSync : public QObject
{
    Q_OBJECT
public:
    explicit ServerSync(float& dx, QVector<Bat>& bats, QPointF& ball, QHostAddress serverAdress, quint16 port, QErrorMessage* errorMessage , QObject *parent = 0);
    virtual ~ServerSync();

private:
    /*!
     * \brief Difference entre la derniere position de la raquette du joueur envoyee au serveur et
     *  la position actuelle de la raquette du joueur.
     */
    float& _dx;

    /*!
     * \brief Vecteur contenant les positions des raquettes des autres joueurs.
     */
    QVector<Bat>& _otherPlayersVector;

    /*!
     * \brief Position de la balle.
     */
    QPointF _ball;

    /*!
     * \brief Socket permettant de communiquer avec le serveur.
     */
    QTcpSocket* _socket;

    /*!
     * \brief Fenetre pour les messages d'erreur.
     */
    QErrorMessage* _errorMessage;

signals:
    void error(QString error);
    
public slots:
    /*!
     * \brief Slot a lancer dans un thread.
     */
    void startSync();

    /*!
     * \brief Slot permettant de recuperer les erreurs generes par le socket.
     */
    void handleSocketError(QAbstractSocket::SocketError);
};

#endif // SERVERSYNC_H
