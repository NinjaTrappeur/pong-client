#ifndef CLIENTCOMMUNICATOR_H
#define CLIENTCOMMUNICATOR_H

#include <QObject>

class ClientCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ClientCommunicator(QObject *parent = 0);
    
private:
    int _dx;

signals:
    
public slots:
    
};

#endif // CLIENTCOMMUNICATOR_H
