#include "client.h"
#include <serialisator.h>
#include <response.h>
#include <QTcpSocket>
#include <QString>
#include <iostream>
#include "mainwindow.h"
#include "error_message.h"
#include <QHostAddress>

using namespace std;

Client::Client(QString hostAddress, int PORT, QObject *parent) : QObject(parent)
{
    client = new QTcpSocket(this);
    connect(client, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(client, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QHostAddress serverAddress(hostAddress);
    cout << "Connecting to server at port " << PORT << endl;
    client->connectToHost(serverAddress, PORT);
    isConnected = client->waitForConnected(2000);
}

Client::~Client(){
    delete client;
}

void Client::onConnected() {
    cout << "Connected" << endl;
}

void Client::onReadyRead() {
    cout << "Ready to read" << endl;
    QByteArray data = client->readAll();
    QString response = QString::fromStdString(data.toStdString());
    int index = response.indexOf('{');
    int number = response.left(index).toInt();
    response.remove(0, index);
    while(response.size() < number){
        response += QString::fromStdString(client->readAll().toStdString());
    }
    cout << "Received:" << endl << response.toStdString() << endl;
    Response resp = Serialisator::getResponceFromString(response);
    if(resp.status == 1){
        ((MainWindow*)parent())->showError("Woop, woop! File don't exist or corrupted!");
        return;
    }
    if(resp.files){
        ((MainWindow*)parent())->fileNameDialogOpen(resp.files);
    }
    if(resp.tourOperators){
        ((MainWindow*)parent())->replaceTourOperators(resp.tourOperators);
    }
}

void Client::onBytesWritten(qint64 n) {
    cout << "Bytes  written " << n << endl;
}

void Client::onDisconnected() {
    cout << "Disconnected" << endl;
    ((MainWindow*)parent())->showError("Server doesn't respond, restart the programm");
    ((MainWindow*)parent())->closeEverythingAndExit();
}

void Client::sendRequest(Request &req){
    QString requestStr = Serialisator::serializeRequestToString(req);
    cout << "Sending: " << endl << requestStr.toStdString() << endl;
    client->write(requestStr.toUtf8());
    client->flush();
}
