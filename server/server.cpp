#include "server.h"
#include <storage_manager.h>
#include <json_storage.h>
#include <serialisator.h>
#include <response.h>
#include <request.h>
#include <iostream>
#include <QTcpSocket>
#include <QDir>

using namespace std;

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    QDir dir;
    if(!dir.exists("data")){
        dir.mkdir("data");
    }
    this->tourOperators = new QList<TourOperator*>;
    int PORT = 3000;
    if (!tcpServer->listen(QHostAddress::Any, PORT)) {
        cerr << "error listen " << endl;
    } else {
        cout << "started at " << PORT << endl;
    }
}

void Server::onNewConnection() {
    cout << "Got new connection" << endl;
    QTcpSocket * clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(onBytesWritten(qint64)));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onReadyRead() {
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    cout << "Recieveing data" << endl;
    QByteArray data = clientSocket->readAll();
    QString response = QString::fromStdString(data.toStdString());
    int index = response.indexOf('{');
    int number = response.left(index).toInt();
    response.remove(0, index);
    while(response.size() < number){
        response += QString::fromStdString(clientSocket->readAll().toStdString());
    }
    cout << "Received:" << endl << response.toStdString() << endl;
    Request req = Serialisator::getRequestFromString(response);
    Response * resp = nullptr;
    switch(req.functionName){
        case(FN_GET_FILES):{
            QDir dir;
            dir.cd("data");
            QStringList files = dir.entryList(QStringList("*.json"));
            QList<QString> * list = new QList<QString>(files.toVector().toList());
            resp = new Response(0, 0, list, nullptr);
            break;
        }
        case(FN_NEW_LIST):{
            while(!this->tourOperators->isEmpty()){
                this->tourOperators->removeAt(0);
            }
            delete this->tourOperators;
            this->tourOperators = new QList<TourOperator*>;
            resp = new Response(0, 0, nullptr, this->tourOperators);
            break;
        }
        case(FN_LOAD_LIST):{
            QString fileName = req.fileName;
            fileName = "data/" + fileName;
            try{
                string stdName = fileName.toStdString();
                JsonDeveloperStorage * jsonStorage = StorageManager::createStorage(stdName);
                auto loaded = jsonStorage->load();
                while(!this->tourOperators->isEmpty()){
                    this->tourOperators->removeAt(0);
                }
                delete this->tourOperators;
                this->tourOperators = loaded;
                delete jsonStorage;
                resp = new Response(0, 0, nullptr, loaded);
                break;
            }
            catch(MessageException &e){
                resp = new Response(1, 0, nullptr, nullptr);
                break;
            }
            catch(invalid_argument &e){
                resp = new Response(1, 0, nullptr, nullptr);
                break;
            }
            break;
        }
        case(FN_SAVE_LIST):{
            QString fileName = req.fileName;
            fileName = "data/" + fileName;
            try{
                string stdName = fileName.toStdString();
                JsonDeveloperStorage * jsonStorage = StorageManager::createStorage(stdName);
                jsonStorage->save(this->tourOperators);
                delete jsonStorage;
                resp = new Response(0, 0, nullptr, nullptr);
                break;
            }
            catch(MessageException &e){
                resp = new Response(1, 0, nullptr, nullptr);
                break;
            }
            catch(invalid_argument &e){
                resp = new Response(1, 0, nullptr, nullptr);
                break;
            }
            break;
        }
        case(FN_INSERT_OPERATOR):{
            tourOperators->append(req.tourOperator);
            resp = new Response(0, 0, nullptr, nullptr);
            break;
        }
        case(FN_UPDATE_OPERATOR):{
            TourOperator * toDel = tourOperators->at(req.id);
            tourOperators->replace(req.id, req.tourOperator);
            delete toDel;
            resp = new Response(0, 0, nullptr, nullptr);
            break;
        }
        case(FN_DELETE_OPERATOR):{
            TourOperator * toDel = tourOperators->at(req.id);
            this->tourOperators->removeAt(req.id);
            delete toDel;
            resp = new Response(0, 0, nullptr, nullptr);
            break;
        }
    }
    if(resp){
        Response res = *resp;
        QString responseStr = Serialisator::serializeResponseToString((res));
        delete resp;
        clientSocket->write(responseStr.toUtf8());
        clientSocket->flush();
    }
}

void Server::onBytesWritten(qint64 n) {
    cout << "Bytes written " << n << endl;
    //
}

void Server::onClientDisconnected() {
    cout << "Client disconnected " << endl;
    QTcpSocket * clientSocket = static_cast<QTcpSocket*>(sender());
    delete clientSocket;
    exit(0);
}
