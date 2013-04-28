#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QUdpSocket>
#include <QString>
#include <QNetworkInterface>

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT
    
public:
    explicit Lobby(QWidget *parent = 0);
    ~Lobby();
    /*!
     * \brief Envoie un paquet UDP au serveur.
     */
    void synchroniseWithServer();
    
private:
    void _startNetworkConnection();

    /*!
     * \brief Renvoie l'addresse IP locale du client.
     * \return Addresse IP locale du client sous la forme d'un QString.
     */
    QString _findLocalAddress();

    /*!
     * \brief Interface graphique du lobby.
     */
    Ui::Lobby *_ui;

    /*!
     * \brief Socket UDP (sera utilisée en multicast et unicast)
     */
    QUdpSocket _udpSocket;

    /*!
     * \brief Addresse du canal multicast qui sera utilisé.
     */
    QHostAddress _multicastAddress;

    /*!
     * \brief Addresse du serveur de jeu pong.
     */
    QHostAddress _serverAddress;

    /*!
     * \brief Addresse du serveur du lobby.
     */
    QHostAddress _lobbyServerAddress;

    /*!
     * \brief ID du client (pid du programme).
     */
    QString _id;

    /*!
     * \brief Port local sur lequel écouter.
     */
    qint16 _localPort;

    /*!
     * \brief Port d'écoute du serveur de jeu de pong.
     */
    qint16 _serverPort;

    /*!
     * \brief Port d'écoute du lobby.
     */
    qint16 _lobbyServerPort;

    /*!
     * \brief Nombre de paquets émis depuis la dernière synchro avec le lobby.
     */
    qint16 _packetsEmited;

signals:
    /*!
     * \brief Emit lorsque l'on a trouvé l'addresse IP du lobby.
     */
    void lobbyServerFound();

    /*!
     * \brief Emit lorsque la synchro avec le lobby est perdue.
     */
    void serverLost();

    /*!
     * \brief Emit lorsque la partie démarre.
     */
    void startGame(QString,qint16);

public slots:
    /*!
     * \brief Permet de parser les paramètres dans le cas
     *  d'une connection directe au serveur de jeu
     *  (sans passer par le lobby).
     */
    void parseDirectConnection();

    /*!
     * \brief Analyse les datagrames reçus via le canal multicast.
     */
    void processDatagram();

    /*!
     * \brief Analyse les datagrames venant du serveur en unicast.
     */
    void readServerSync();

    /*!
     * \brief Annonce le client sur le canal multicast.
     */
    void announce();

    /*!
     * \brief Envoie au serveur un acquittement.
     */
    void acknowledgeServer();

    /*!
     * \brief Remet le lobby dans son état initial.
     */
    void resetGlobalState();
};

#endif // LOBBY_H
