#include "serialisator.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <stdexcept>

Serialisator::Serialisator()
{

}

QString Serialisator::serializeRequestToString(Request request){
    QJsonObject requestObj;
    requestObj.insert("function", request.functionName);
    requestObj.insert("id", request.id);
    TourOperator * op = request.tourOperator;
    QJsonObject operatorObj;
    if(op){
        operatorObj.insert("country", op->getCountry());
        operatorObj.insert("price", op->getPrice());
        operatorObj.insert("duration", op->getDuration());
        operatorObj.insert("freeMeals", op->getMeals());
        operatorObj.insert("freeDrinks", op->getDrinks());
    }
    requestObj.insert("operator", operatorObj);
    requestObj.insert("fileName", request.fileName);
    QJsonDocument doc(requestObj);
    QString jsonString = doc.toJson();
    jsonString = QString::number(jsonString.size()) + jsonString;
    return jsonString;
}

QString Serialisator::serializeResponseToString(Response response){
    QJsonObject responseObj;
    responseObj.insert("status", response.status);
    responseObj.insert("id", response.id);
    QJsonArray filesArr;
    if(response.files){
        QJsonObject existsObj;
        existsObj.insert("exists", true);
        filesArr.append(existsObj);
        for (QString & str: (*response.files)){
            QJsonObject fileObj;
            fileObj.insert("name", str);
            filesArr.append(fileObj);
        }
    }
    QJsonArray tourOpertorArr;
    if(response.tourOperators){
        QJsonObject existsObj;
        existsObj.insert("exists", true);
        tourOpertorArr.append(existsObj);
        for (TourOperator* & op: (*response.tourOperators)) {
            QJsonObject operatorObj;
            operatorObj.insert("country", op->getCountry());
            operatorObj.insert("price", op->getPrice());
            operatorObj.insert("duration", op->getDuration());
            operatorObj.insert("freeMeals", op->getMeals());
            operatorObj.insert("freeDrinks", op->getDrinks());
            tourOpertorArr.append(operatorObj);
        }
    }
    responseObj.insert("files", filesArr);
    responseObj.insert("operators", tourOpertorArr);
    QJsonDocument doc(responseObj);
    QString jsonString = doc.toJson();
    jsonString = QString::number(jsonString.size()) + jsonString;
    return jsonString;
}

Response Serialisator::getResponceFromString(QString string){
    Response response;
    QList<TourOperator *> * operators = nullptr;
    QList<QString> * files = nullptr;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(
           string.toLocal8Bit(), &err);
    if (err.error != QJsonParseError::NoError) {
           throw std::invalid_argument("Error in reading JSON file " + err.errorString().toStdString());
    }
    QJsonObject responseObj = doc.object();
    response.id = responseObj.value("id").toInt();
    response.status = responseObj.value("status").toInt();
    QJsonArray filesArr = responseObj.value("files").toArray();
    if(filesArr.size() > 0){
        files = new QList<QString>();
    }
    for (int i = 1; i < filesArr.size(); i++) {
          QJsonValue value = filesArr.at(i);
          QJsonObject nameObj = value.toObject();
          files->push_back(nameObj.value("name").toString());
    }
    QJsonArray tourOpertorArr = responseObj.value("operators").toArray();
    if(tourOpertorArr.size() > 0){
        operators = new QList<TourOperator*>();
    }
    for (int i = 1; i < tourOpertorArr.size(); i++) {
          QJsonValue value = tourOpertorArr.at(i);
          QJsonObject tourOpertorObj = value.toObject();
          operators->push_back(new TourOperator(tourOpertorObj.value("country").toString(),
                                            tourOpertorObj.value("duration").toInt(),
                                            tourOpertorObj.value("price").toDouble(),
                                            tourOpertorObj.value("freeMeals").toBool(),
                                            tourOpertorObj.value("freeDrinks").toBool()));
    }
    response.tourOperators = operators;
    response.files = files;
    return response;
}

Request Serialisator::getRequestFromString(QString string){
    Request request;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(
           string.toLocal8Bit(), &err);
    if (err.error != QJsonParseError::NoError) {
           throw std::invalid_argument("Error in reading JSON file " + err.errorString().toStdString());
    }
    QJsonObject requestObj = doc.object();
    request.id = requestObj.value("id").toInt();
    request.fileName = requestObj.value("fileName").toString();
    TourOperator * op = nullptr;
    QJsonObject tourOpertorObj = requestObj.value("operator").toObject();
    if(tourOpertorObj.count() != 0){
            op = new TourOperator(tourOpertorObj.value("country").toString(),
                                  tourOpertorObj.value("duration").toInt(),
                                  tourOpertorObj.value("price").toDouble(),
                                  tourOpertorObj.value("freeMeals").toBool(),
                                  tourOpertorObj.value("freeDrinks").toBool());
    }
    request.tourOperator = op;
    request.functionName = (FunctionName)requestObj.value("function").toInt();
    return request;
}
