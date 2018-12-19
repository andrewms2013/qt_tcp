#ifndef CLIENT_H
#define CLIENT_H

#include "request.h"
#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QString hostAddress, int PORT, QObject *parent = 0);
    ~Client();
    bool isConnected;
    QTcpSocket * client;
    void sendRequest(Request &req);
signals:

public slots:
    void onConnected();
    void onReadyRead();
    void onBytesWritten(qint64);
    void onDisconnected();

};

#endif // CLIENT_H
