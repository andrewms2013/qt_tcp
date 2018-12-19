#include "creation_dialog.h"
#include "ui_creationdialog.h"
#include <QPushButton>

CreationDialog::CreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationDialog)
{
    this->toWorkWith = NULL;
    ui->setupUi(this);
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
}

CreationDialog::CreationDialog(TourOperator * toWorkWith, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationDialog)
{
    this->toWorkWith = toWorkWith;
    ui->setupUi(this);
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
    ui->countryEdit->setText(toWorkWith->getCountry());
    ui->durationEdit->setValue(toWorkWith->getDuration());
    ui->priceEdit->setValue(toWorkWith->getPrice());
    ui->freeMealsEdit->setChecked(toWorkWith->getMeals());
    ui->freeDrinksEdit->setChecked(toWorkWith->getDrinks());
}

CreationDialog::~CreationDialog()
{
    delete ui;
}

void CreationDialog::on_buttonBox_accepted()
{
    QString country = ui->countryEdit->text();
    float price = ui->priceEdit->value();
    int duration = ui->durationEdit->value();
    bool freeMeals = ui->freeMealsEdit->isChecked();
    bool freeDrinks = ui->freeDrinksEdit->isChecked();
    if(toWorkWith != nullptr){
        toWorkWith->setCountry(country);
        toWorkWith->setDrinks(freeDrinks);
        toWorkWith->setDuration(duration);
        toWorkWith->setMeals(freeMeals);
        toWorkWith->setPrice(price);
    }
    else{
        toWorkWith = new TourOperator(country, duration, price, freeMeals, freeDrinks);
    }
}

TourOperator * CreationDialog::getTourOperator(){
    return this->toWorkWith;
}



void CreationDialog::on_countryEdit_textChanged(const QString &arg1)
{
    QPushButton * okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    if(arg1 != NULL){
        okButton->setEnabled(true);
    }
    else{
        okButton->setEnabled(false);
    }
}
