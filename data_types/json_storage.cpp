#include <vector>
#include <json_storage.h>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

QList<TourOperator *> * JsonDeveloperStorage::load(){
    QList<TourOperator *> * toLoad = new QList<TourOperator*>();
    // https://stackoverflow.com/a/33635201
    string buffer;
    ifstream ifs (this->name.toStdString());
    if(ifs.is_open()){
        getline (ifs, buffer, (char) ifs.eof());
        ifs.close();
    }
    else{
        throw invalid_argument("Can't open the file");
    }
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(
           QByteArray::fromStdString(buffer), &err);
    if (err.error != QJsonParseError::NoError) {
           throw invalid_argument("Error in reading JSON file " + err.errorString().toStdString());
    }
    QJsonArray tourOpertorArr = doc.array();
    for (int i = 0; i < tourOpertorArr.size(); i++) {
          QJsonValue value = tourOpertorArr.at(i);
          QJsonObject tourOpertorObj = value.toObject();
          toLoad->push_back(new TourOperator(tourOpertorObj.value("country").toString(),
                                            tourOpertorObj.value("duration").toInt(),
                                            tourOpertorObj.value("price").toDouble(),
                                            tourOpertorObj.value("freeMeals").toBool(),
                                            tourOpertorObj.value("freeDrinks").toBool()));
    }
    return toLoad;
}

void JsonDeveloperStorage::save(QList<TourOperator *> * entities){
    QJsonArray tourOpertorArr;
    auto operatorList = (*entities);
    for (TourOperator* & op: operatorList) {
        QJsonObject operatorObj;
        operatorObj.insert("country", op->getCountry());
        operatorObj.insert("price", op->getPrice());
        operatorObj.insert("duration", op->getDuration());
        operatorObj.insert("freeMeals", op->getMeals());
        operatorObj.insert("freeDrinks", op->getDrinks());
        tourOpertorArr.append(operatorObj);
    }
    QJsonDocument doc(tourOpertorArr);
    string jsonString = doc.toJson().toStdString();
    ofstream outfile;
    outfile.open(this->name.toStdString(), ios::out | ios::trunc );
    if(outfile.is_open()){
        outfile << jsonString;
        outfile.close();
    }
    else{
        throw invalid_argument("Can't open the file");
    }
}
