#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <tour_operator.h>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void showError(QString error);
    void closeEverythingAndExit();
    QList<TourOperator*> * tourOperators;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fileNameDialogOpen(QList <QString> * files);
    void replaceTourOperators(QList<TourOperator*> * loaded);
private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_removeButton_clicked();

    void on_tourOperatorList_itemSelectionChanged();

    void on_executeButton_clicked();

    void on_resultOperatorList_itemClicked(QListWidgetItem *item);

    void on_actionSave_to_JSON_triggered();

    void on_actionLoad_from_JSON_triggered();

    void on_countrySearchInput_returnPressed();

    void on_actionNew_list_triggered();

private:
    Client * client = nullptr;
    bool toSave = false;
    int tryToConnect(QString serverFullAddress);
    void closeEvent (QCloseEvent *event);
    Ui::MainWindow *ui;
    TourOperator * tourOperatorFromItem(QListWidgetItem * qListWidgetItem);
    void fillLablesWithOperator(TourOperator * tourOperator);
    QListWidgetItem * newItemFromOperator(TourOperator * tourOperator);
};

#endif // MAINWINDOW_H
