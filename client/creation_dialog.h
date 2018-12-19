#pragma once
#ifndef CREATIONDIALOG_H
#define CREATIONDIALOG_H

#include <tour_operator.h>
#include <QDialog>

namespace Ui {
class CreationDialog;
}

class CreationDialog : public QDialog
{
    Q_OBJECT
    TourOperator * toWorkWith;

public:
    explicit CreationDialog(QWidget *parent = 0);
    explicit CreationDialog(TourOperator * toWorkWith, QWidget *parent = 0);
    ~CreationDialog();
    TourOperator * getTourOperator();

private slots:

    void on_buttonBox_accepted();

    void on_countryEdit_textChanged(const QString &arg1);

private:
    Ui::CreationDialog *ui;
};

#endif // CREATIONDIALOG_H
