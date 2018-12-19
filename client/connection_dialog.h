#ifndef CONNECTION_DIALOG_H
#define CONNECTION_DIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT
    QString serverFullAddress;

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();
    QString getServerFullAddress();

private slots:
    void on_buttonBox_accepted();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTION_DIALOG_H
