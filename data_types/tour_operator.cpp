#include "tour_operator.h"
#include "for_free.h"

TourOperator::TourOperator(QString country, int duration, float price, ForFree * facilities, QObject *parent) : QObject(parent){
    this->country = country;
    this->duration = duration;
    this->price = price;
    this->facilities = facilities;
}

TourOperator::TourOperator(QString country, int duration, float price, bool freeMeals, bool freeDrinks, QObject *parent) : QObject(parent){
    this->country = country;
    this->duration = duration;
    this->price = price;
    this->facilities = new ForFree(freeMeals, freeDrinks);
}

TourOperator::~TourOperator(){
    delete this->facilities;
}

QString  TourOperator::getCountry(){
    return this->country;
}

int     TourOperator::getDuration(){
    return this->duration;
}

float   TourOperator::getPrice(){
    return this->price;
}

bool    TourOperator::getMeals(){
    return this->facilities->getMeals();
}

bool    TourOperator::getDrinks(){
    return this->facilities->getDrinks();
}

void    TourOperator::setCountry(QString country){
    this->country = country;
}

void    TourOperator::setDuration(int duration){
    this->duration = duration;
}

void    TourOperator::setPrice(float price){
    this->price = price;
}

void    TourOperator::setMeals(bool isIncluded){
    this->facilities->setMeals(isIncluded);
}

void    TourOperator::setDrinks(bool isIncluded){
    this->facilities->setDrinks(isIncluded);
}
