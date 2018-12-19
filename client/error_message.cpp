#include "error_message.h"
#include "ui_errormessage.h"

ErrorMessage::ErrorMessage(QString message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessage)
{
    ui->setupUi(this);
    ui->label->setText(message);
}

ErrorMessage::~ErrorMessage()
{
    delete ui;
}

void ErrorMessage::on_pushButton_clicked()
{
    this->close();
}
