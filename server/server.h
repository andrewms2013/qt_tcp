#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "tour_operator.h"

class Server : public QObject
{
    QTcpServer * tcpServer;
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    QList <TourOperator *> * tourOperators;
signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onBytesWritten(qint64);
    void onClientDisconnected();
};


#endif // SERVER_H
