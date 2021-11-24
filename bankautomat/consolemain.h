#ifndef CONSOLEMAIN_H
#define CONSOLEMAIN_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include "consolenosto.h"
#include "consoletilitapahtumat.h"
#include "consolesaldo.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class consoleMain;
}

class consoleMain : public QDialog
{
    Q_OBJECT

public:
    explicit consoleMain(QWidget *parent = nullptr);
    ~consoleMain();

private slots:
    void getTapahtumatSlot(QNetworkReply*);
    void getIDSlot(const QString &);//Kortinnumeron vastaanottaja
    void slotCloseNosto();
    void slotCloseSaldo();
    void timerSlot();
    void slotCardID(const QString &);
    void slotCloseTilitapahtumat();
    void on_btnNosto_clicked();
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnKirjauduUlos_clicked();
    void getSaldoSlot(QNetworkReply*);


signals:
    void closeWindow();
    void sendTilitapahtumat(const QString &);
    void finished(QNetworkReply*);
    void sendSaldo(const QString &);

private:
    Ui::consoleMain *ui;
    consoleNosto *objConNosto;
    consoleTilitapahtumat *objConTilitapahtumat;
    consoleSaldo *objConSaldo;
    QTimer *objTimer;
    int counter;
    QString korttiID;
    QString tilitapahtumat; //Datan välittämistä varten
    QString saldo;
    QString IDcard;
    QNetworkAccessManager *getManager;
    QNetworkReply *replytapahtumat;
    QNetworkReply *replysaldo;
    QByteArray response_data;

};

#endif // CONSOLEMAIN_H
