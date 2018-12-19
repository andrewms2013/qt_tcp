#include "request.h"

Request::Request(FunctionName functionName, int id, TourOperator * tourOperator, QString fileName)
{
    this->functionName = functionName;
    this->id = id;
    this->tourOperator = tourOperator;
    this->fileName = fileName;
}
