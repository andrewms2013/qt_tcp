#pragma once

#ifndef FOR_FREE_H
#define FOR_FREE_H

#include <QDebug>
#include "data_types_global.h"

class DATA_TYPESSHARED_EXPORT ForFree : public QObject{
    Q_OBJECT
    bool freeMeals;
    bool freeDrinks;
public:
    bool    getMeals();
    bool    getDrinks();
    void    setMeals(bool isIncluded);
    void    setDrinks(bool isIncluded);
    explicit ForFree(bool freeMeals, bool freeDrinks, QObject *parent = 0);
    ForFree(QObject *parent = 0);
    ~ForFree(){}
};


#endif // FOR_FREE_H
