#include "file_name_dialog.h"
#include "ui_filenamedialog.h"
#include <QPushButton>

FileNameDialog::FileNameDialog(QList<QString> * files, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileNameDialog)
{
    ui->setupUi(this);
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    this->files = files;
    auto filesList = (*(this->files));
    for (QString & file: filesList){
        QListWidgetItem * newItem = new QListWidgetItem();
        newItem->setText(file);
        ui->listWidget->addItem(newItem);
    }
    okButton->setEnabled(false);
}

FileNameDialog::~FileNameDialog()
{
    delete ui;
}

void FileNameDialog::on_buttonBox_accepted()
{
    this->fileName = ui->lineEdit->text();
    ui->listWidget->clear();
}

void FileNameDialog::on_lineEdit_textChanged(const QString &arg1)
{
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if(arg1 != NULL){
        okButton->setEnabled(true);
    }
    else{
        okButton->setEnabled(false);
    }
}

QString FileNameDialog::getFileName(){
    return this->fileName;
}

void FileNameDialog::on_buttonBox_rejected()
{
    ui->listWidget->clear();
}

void FileNameDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->lineEdit->setText(item->text());
}
