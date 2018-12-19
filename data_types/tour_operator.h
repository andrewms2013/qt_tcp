#pragma once
#ifndef TOUR_OPERATOR_H
#define TOUR_OPERATOR_H
#include <QDebug>
#include "for_free.h"
#include "data_types_global.h"


class DATA_TYPESSHARED_EXPORT TourOperator : public QObject{
    Q_OBJECT
    QString  country;
    int     duration;
    float   price;
    ForFree * facilities;
public:
    explicit TourOperator(QString country, int duration, float price, ForFree * facilities, QObject *parent = 0);
    explicit TourOperator(QString country, int duration, float price, bool freeMeals, bool freeDrinks, QObject *parent = 0);
    ~TourOperator();
    QString getCountry();
    int     getDuration();
    float   getPrice();
    bool    getMeals();
    bool    getDrinks();
    void    setCountry(QString country);
    void    setDuration(int duration);
    void    setPrice(float price);
    void    setMeals(bool isIncluded);
    void    setDrinks(bool isIncluded);
};

#endif // TOUR_OPERATOR_H
