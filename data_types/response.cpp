#include "response.h"

Response::Response(int status, int id, QList<QString> * files, QList<TourOperator*> * tourOperators)
{
    this->status = status;
    this->id = id;
    this->files = files;
    this->tourOperators = tourOperators;
}
