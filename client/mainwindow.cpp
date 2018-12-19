#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tour_operator.h>
#include "creation_dialog.h"
#include "file_name_dialog.h"
#include <QListWidgetItem>
#include <json_storage.h>
#include <storage_manager.h>
#include "error_message.h"
#include <string>
#include <QCloseEvent>
#include <QMessageBox>
#include <response.h>
#include <request.h>
#include <serialisator.h>
#include "connection_dialog.h"
#include <QTimer>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int connectionStatus = 0;
    while(!connectionStatus){
        ConnectionDialog dialog(this);
        if(dialog.exec() == QDialog::Accepted){
            QString serverFullAddress = dialog.getServerFullAddress();
            connectionStatus = tryToConnect(serverFullAddress);
            if(!connectionStatus){
                ErrorMessage error("Error connecting to server, try again", this);
                error.exec();
            }
        }
        else{
            exit(0);
        }
    }
    this->tourOperators = new QList<TourOperator*>;
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::tryToConnect(QString serverFullAddress){
    if(this->client != nullptr){
        delete client;
    }
    int spaceIndex = serverFullAddress.indexOf(" ");
    QString hostAddress = serverFullAddress.left(spaceIndex);
    QString portAddress = serverFullAddress.mid(spaceIndex + 1);
    int PORT = portAddress.toInt();
    client = new Client(hostAddress,PORT, this);
    if(client->isConnected){
        return true;
    }
    return false;
}

void MainWindow::on_addButton_clicked()
{
    CreationDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        QListWidgetItem * newItem = new QListWidgetItem();
        newItem->setData(Qt::UserRole, QVariant::fromValue(dialog.getTourOperator()));;
        newItem->setText(dialog.getTourOperator()->getCountry());
        Request req(FN_INSERT_OPERATOR, 0, dialog.getTourOperator(), "");
        client->sendRequest(req);
        this->tourOperators->push_back(dialog.getTourOperator());
        ui->tourOperatorList->addItem(newItem);
    }
}

void MainWindow::on_editButton_clicked()
{
    QListWidgetItem * selected = ui->tourOperatorList->currentItem();
    TourOperator * toEdit = tourOperatorFromItem(selected);
    CreationDialog dialog(toEdit, this);
    dialog.exec();
    selected->setText(toEdit->getCountry());
    Request req(FN_UPDATE_OPERATOR, tourOperators->indexOf(toEdit), toEdit, "");
    client->sendRequest(req);
    fillLablesWithOperator(toEdit);
}

void MainWindow::on_removeButton_clicked()
{
    QListWidgetItem * selected = ui->tourOperatorList->currentItem();
    TourOperator * toDel = tourOperatorFromItem(selected);
    for(int i = 0; i < ui->resultOperatorList->count(); ++i){
        QListWidgetItem* operatorItem = ui->resultOperatorList->item(i);
        TourOperator * toSeek = tourOperatorFromItem(operatorItem);
        if(toDel == toSeek){
            delete operatorItem;
            break;
        }
    }
    Request req(FN_DELETE_OPERATOR, tourOperators->indexOf(toDel), nullptr, "");
    client->sendRequest(req);
    for (int i = 0; i < this->tourOperators->size(); i++){
      auto op = this->tourOperators->at(i);
      if (op == toDel) {
        this->tourOperators->removeAt(i);
        break;
      }
    }
    delete toDel;
    delete selected;
}


void MainWindow::on_tourOperatorList_itemSelectionChanged()
{
    int selectedItems  = ui->tourOperatorList->selectionModel()->selectedIndexes().size();
    if(selectedItems){
        ui->editButton->setEnabled(true);
        ui->removeButton->setEnabled(true);
        QListWidgetItem * selected = ui->tourOperatorList->currentItem();
        TourOperator * tourOperator = tourOperatorFromItem(selected);
        fillLablesWithOperator(tourOperator);
    }
    else{
        ui->editButton->setEnabled(false);
        ui->removeButton->setEnabled(false);
        fillLablesWithOperator(NULL);
    }

}


TourOperator * MainWindow::tourOperatorFromItem(QListWidgetItem * qListWidgetItem){
    if(qListWidgetItem){
        QVariant selectedVariant = qListWidgetItem->data(Qt::UserRole);
        TourOperator * toGet = selectedVariant.value<TourOperator *>();
        return toGet;
    }
    else{
        return NULL;
    }
}

void MainWindow::fillLablesWithOperator(TourOperator * tourOperator){
    if(tourOperator){
        ui->countryLabel->setText(tourOperator->getCountry());
        ui->durationLabel->setText(QString::number(tourOperator->getDuration()));
        ui->priceLabel->setText(QString::number(tourOperator->getPrice()));
        ui->freeMealsLabel->setText(tourOperator->getMeals() ? "included" : "not included");
        ui->freeDrinksLabel->setText(tourOperator->getDrinks() ? "included" : "not included");
    }
    else{
        ui->countryLabel->setText("");
        ui->durationLabel->setText("");
        ui->priceLabel->setText("");
        ui->freeMealsLabel->setText("");
        ui->freeDrinksLabel->setText("");
    }
}


void MainWindow::on_executeButton_clicked()
{
    ui->resultOperatorList->clear();
    QString key = ui->countrySearchInput->text();
    for(int i = 0; i < ui->tourOperatorList->count(); ++i){
        QListWidgetItem* item = ui->tourOperatorList->item(i);
        QString text = item->text();
        if(text.toStdString().find(key.toStdString()) != std::string::npos){
            QListWidgetItem * newItem = item->clone();
            ui->resultOperatorList->addItem(newItem);
        }
    }
}

QListWidgetItem * MainWindow::newItemFromOperator(TourOperator * tourOperator){
    if(tourOperator){
        QListWidgetItem * newItem = new QListWidgetItem();
        newItem->setData(Qt::UserRole, QVariant::fromValue(tourOperator));
        newItem->setText(tourOperator->getCountry());
        return  newItem;
    }
    return NULL;
}

void MainWindow::on_resultOperatorList_itemClicked(QListWidgetItem *item)
{
    TourOperator * keyOpertor = tourOperatorFromItem(item);
    for(int i = 0; i < ui->tourOperatorList->count(); ++i){
        QListWidgetItem* operatorItem = ui->tourOperatorList->item(i);
        TourOperator * toSeek = tourOperatorFromItem(operatorItem);
        if(keyOpertor == toSeek){
            ui->tourOperatorList->setCurrentItem(operatorItem);
            break;
        }
    }
}

void MainWindow::on_actionSave_to_JSON_triggered()
{
    this->toSave = true;
    Request req(FN_GET_FILES, 0, nullptr, "");
    client->sendRequest(req);
}

void MainWindow::on_actionLoad_from_JSON_triggered()
{
    this->toSave = false;
    Request req(FN_GET_FILES, 0, nullptr, "");
    client->sendRequest(req);
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "ExitDialog",
                                                                "Are you sure?",
                                                                QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        closeEverythingAndExit();
    }
}

void MainWindow::on_countrySearchInput_returnPressed()
{
   on_executeButton_clicked();
}

void MainWindow::fileNameDialogOpen(QList <QString> * files){
    FileNameDialog dialog(files, this);
    if(dialog.exec() == QDialog::Accepted){
        QString fileName = dialog.getFileName();
        if(toSave){
            Request req(FN_SAVE_LIST, 0, nullptr, fileName);
            client->sendRequest(req);
        }
        else{
            Request req(FN_LOAD_LIST, 0, nullptr, fileName);
            client->sendRequest(req);
        }
    }
}

void MainWindow::replaceTourOperators(QList<TourOperator*> * loaded){
    ui->tourOperatorList->clear();
    ui->resultOperatorList->clear();
    for (int i = 0; i < this->tourOperators->size(); i++){
      auto op = this->tourOperators->at(i);
      delete op;
    }
    while(!this->tourOperators->isEmpty()){
        this->tourOperators->removeAt(0);
    }
    delete this->tourOperators;
    this->tourOperators = loaded;
    auto newOperatorList = (*(this->tourOperators));
    for (TourOperator* & op: newOperatorList){
        QListWidgetItem * newItem = newItemFromOperator(op);
        ui->tourOperatorList->addItem(newItem);
    }
}

void MainWindow::closeEverythingAndExit(){
    client->client->disconnect();
    delete client;
    if(this->tourOperators){
        auto operatorList = (*(this->tourOperators));
        for (TourOperator* & op: operatorList){
            delete op;
        }
        delete this->tourOperators;
        ui->tourOperatorList->clear();
        ui->resultOperatorList->clear();
    }
    exit(0);
}

void MainWindow::showError(QString error){
    ErrorMessage message(error, this);
    message.exec();
}

void MainWindow::on_actionNew_list_triggered()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Dialog",
                                                                "Are you sure?",
                                                                QMessageBox::No | QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        Request req(FN_NEW_LIST, 0, nullptr, nullptr);
        client->sendRequest(req);
    }
}
