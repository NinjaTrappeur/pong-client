#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H

#include <QObject>
#include <QDataStream>

class ClientCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ClientCommunicator(QObject *parent = 0);
    void operator>>(QDataStream & out)const;
    void operator<<(QDataStream & in);

    friend QDataStream & operator>>(QDataStream & in, ClientCommunicator & client);
    friend QDataStream & operator<<(QDataStream & out, const ClientCommunicator & client);

private:
    int _dx;

signals:
    
public slots:
    
};

#endif // CLIENTCOMMUNICATOR_H
