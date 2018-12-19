#include "for_free.h"

ForFree::ForFree(bool freeMeals, bool freeDrinks, QObject *parent) : QObject(parent){
    this->freeMeals = freeMeals;
    this->freeDrinks = freeDrinks;
}

ForFree::ForFree(QObject *parent) : QObject(parent){
    this->freeDrinks = false;
    this->freeMeals = false;
}

void    ForFree::setMeals(bool isIncluded){
    this->freeMeals = isIncluded;
}

void    ForFree::setDrinks(bool isIncluded){
    this->freeDrinks = isIncluded;
}

bool    ForFree::getMeals(){
    return this->freeMeals;
}

bool    ForFree::getDrinks(){
    return this->freeDrinks;
}
