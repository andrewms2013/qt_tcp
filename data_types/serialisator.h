#pragma once
#ifndef SERIALISATOR_H
#define SERIALISATOR_H

#include <QList>
#include "request.h"
#include "response.h"

class DATA_TYPESSHARED_EXPORT Serialisator
{
public:
    Serialisator();

    static QString serializeRequestToString(Request request);
    static QString serializeResponseToString(Response response);
    static Response  getResponceFromString(QString string);
    static Request   getRequestFromString(QString string);
};

#endif // SERIALISATOR_H
