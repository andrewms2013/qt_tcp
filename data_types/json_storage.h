#pragma once
#ifndef JSON_STORAGE_H
#define JSON_STORAGE_H

#include <QList>
#include <QDebug>
#include <tour_operator.h>
#include "data_types_global.h"

class DATA_TYPESSHARED_EXPORT JsonDeveloperStorage{
    QString name;
public:
    JsonDeveloperStorage(QString & name) { this->name = name; }
    QList<TourOperator *> * load();
    void save(QList<TourOperator *> * entities);
};

#endif // JSON_STORAGE_H
