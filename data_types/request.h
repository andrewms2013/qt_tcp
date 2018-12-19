#pragma once
#ifndef REQUEST_H
#define REQUEST_H

#include "tour_operator.h"

typedef  enum{
   FN_GET_FILES,
   FN_NEW_LIST,
   FN_LOAD_LIST,
   FN_SAVE_LIST,
   FN_INSERT_OPERATOR,
   FN_UPDATE_OPERATOR,
   FN_DELETE_OPERATOR
} DATA_TYPESSHARED_EXPORT FunctionName;

class DATA_TYPESSHARED_EXPORT Request
{
public:
    Request(){}
    Request(FunctionName functionName, int id, TourOperator * tourOperator, QString fileName);
    FunctionName functionName;
    int id;
    TourOperator * tourOperator;
    QString fileName;
};

#endif // REQUEST_H
