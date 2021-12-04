#ifndef CONSOLEPASSWORD_H
#define CONSOLEPASSWORD_H

#include <QDialog>
#include <consolemain.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "consolecreditdebit.h"


namespace Ui {
class consolePassword;
}

class consolePassword : public QDialog
{
    Q_OBJECT

public:
    explicit consolePassword(QWidget *parent = nullptr);
    ~consolePassword();

signals:
    void signalKirjaudu();
    void finished(QNetworkReply*);
    void sendID(const QString &);
    void sendAsiakastiedot(const QString &);
    void signalLukitseKortti();

private slots:

    void connectingSlot(const QString &);
    void loginSlot(QNetworkReply *reply);
    void credebSlot(QNetworkReply * reply);
    void getAsiakastiedotSlot(QNetworkReply *replyAsiakastiedot);
    void on_btnZero_clicked();
    void on_btnOne_clicked();
    void on_btnTwo_clicked();
    void on_btnThree_clicked();
    void on_btnFour_clicked();
    void on_btnFive_clicked();
    void on_btnSix_clicked();
    void on_btnSeven_clicked();
    void on_btnEight_clicked();
    void on_btnNine_clicked();
    void on_btnReset_clicked();
    void on_btnOK_clicked();
    void updateKorttiLukittu();
    void updateKorttiLukittuSlot(QNetworkReply *replyKorttilukittu);
    void slotStopTimer();
    void slotCloseWindow();
    void slotCloseConsoleMain();
    void startTimerSlot();


private:
    Ui::consolePassword *ui;
    consoleMain *objConMain;
    QNetworkAccessManager *loginManager, *credebManager, *putManager;
    QNetworkReply *reply, *replyLukitseKortti;
    consoleCreditDebit *objCredeb;
    QTimer *objTimer, *objTimeri;
    QNetworkAccessManager *loginManager, *credebManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString cardID; //Kortinnumeron välittämistä varten
    QNetworkAccessManager *asiakastiedotManager;
    QNetworkReply *replyAsiakastiedot;
    QByteArray dataAsiakastiedot;
    QByteArray response_dataAsiakastiedot, response_dataKorttilukittu;
    int counterPIN;
};

#endif // CONSOLEPASSWORD_H
