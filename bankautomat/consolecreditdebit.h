#ifndef CONSOLECREDITDEBIT_H
#define CONSOLECREDITDEBIT_H

#include <QDialog>
#include <QDebug>
#include "consolemain.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class consoleCreditDebit;
}

class consoleCreditDebit : public QDialog
{
    Q_OBJECT

public:
    explicit consoleCreditDebit(QWidget *parent = nullptr);
    ~consoleCreditDebit();

signals:
    void signalID(const QString &);
    void sendSaldo(const QString &);

private slots:
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();
    void slotCardID(const QString &);
   void getSaldoSlot(QNetworkReply *);
   void getLuottorajaSlot(QNetworkReply *);

private:
    Ui::consoleCreditDebit *ui;
    QString korttiID;
    consoleMain *objConMain;
    QNetworkAccessManager *getManager, *getManager1;
    QNetworkReply *replysaldo;
    QNetworkReply *replyLuottoraja;
    QByteArray response_data, response_data1;
    consoleSaldo *objConSaldo;
};

#endif // CONSOLECREDITDEBIT_H
