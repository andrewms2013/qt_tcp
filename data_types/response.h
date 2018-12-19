#pragma once
#ifndef RESPONSE_H
#define RESPONSE_H

#include <QList>
#include "tour_operator.h"

class DATA_TYPESSHARED_EXPORT Response
{
public:
    Response(){}
    Response(int status, int id, QList<QString> * files, QList<TourOperator*> * tourOperators);
    int status;
    int id;
    QList<QString> * files;
    QList<TourOperator*> * tourOperators;
};

#endif // RESPONSE_H
