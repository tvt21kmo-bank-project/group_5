#ifndef CONSOLEMAIN_H
#define CONSOLEMAIN_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QString>
#include <QKeyEvent>
#include "consolenosto.h"
#include "consoletilitapahtumat.h"
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
    void timerSlot();
    void slotCloseTilitapahtumat();
    void on_btnNosto_clicked();
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnKirjauduUlos_clicked();


signals:
    void closeWindow();
    void sendTilitapahtumat(const QString &);
    void finished(QNetworkReply*);

private:
    Ui::consoleMain *ui;
    consoleNosto *objConNosto;
    consoleTilitapahtumat *objConTilitapahtumat;
    QTimer *objTimer;
    int counter;
    QString tilitapahtumat; //Datan välittämistä varten
    QString IDcard;
    QNetworkAccessManager *getManager;
    QNetworkReply *replytapahtumat;
    QByteArray response_data;

};

#endif // CONSOLEMAIN_H
