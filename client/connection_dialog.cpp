#include "connection_dialog.h"
#include "ui_connectiondialog.h"
#include <QPushButton>

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_buttonBox_accepted()
{
    this->serverFullAddress = ui->lineEdit->text();
}


void ConnectionDialog::on_lineEdit_textChanged(const QString &arg1)
{
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if(arg1 != NULL){
        okButton->setEnabled(true);
    }
    else{
        okButton->setEnabled(false);
    }
}

QString ConnectionDialog::getServerFullAddress(){
    return this->serverFullAddress;
}
