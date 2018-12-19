#pragma once
#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QDialog>

namespace Ui {
class ErrorMessage;
}

class ErrorMessage : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorMessage(QString message, QWidget *parent = 0);
    ~ErrorMessage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorMessage *ui;
};

#endif // ERRORMESSAGE_H
