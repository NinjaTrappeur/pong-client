#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H

#include <QObject>
#include <QDataStream>

/*!
 * \brief Classe envoyee dans le reseau par le client
 */
class ClientCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ClientCommunicator(QObject *parent = 0);
    ClientCommunicator(qint32 dx);

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

    friend QDataStream & operator>>(QDataStream & in, ClientCommunicator & client);
    friend QDataStream & operator<<(QDataStream & out, const ClientCommunicator & client);

    int dx() const;
    void setDx(int dx);

private:
    /*!
     * \brief Deplacement de la raquette du joueur.
     */
    qint32 _dx;

signals:
    
public slots:
    
};

#endif // CLIENTCOMMUNICATOR_H
