#pragma once
#ifndef FILENAMEDIALOG_H
#define FILENAMEDIALOG_H

#include <QDialog>
#include <QList>
#include <QListWidgetItem>

namespace Ui {
class FileNameDialog;
}

class FileNameDialog : public QDialog
{
    QString fileName;
    QList<QString> * files;
    Q_OBJECT

public:
    explicit FileNameDialog(QList<QString> * files, QWidget *parent = 0);
    ~FileNameDialog();
    QString getFileName();

private slots:
    void on_buttonBox_accepted();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_buttonBox_rejected();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::FileNameDialog *ui;
};

#endif // FILENAMEDIALOG_H
