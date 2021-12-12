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
    void signalValinta(const QString &);
    void sendAsiakastiedot(const QString &);
    void stopTimercredeb();
    void closeWindow();
    void stopTimer();



private slots:
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();
    void slotCardID(const QString &);
    void getAsiakastiedotSlot(QNetworkReply *);
    void timerSlot();
    void startTimerSlot();
    void slotStopTimerMain();
    void slotCloseConsoleMain();


private:
    Ui::consoleCreditDebit *ui;
    QString korttiID, valinta;
    consoleMain *objConMain;
    QNetworkAccessManager *getManager, *getManager1, *asiakastiedotManager;
    QNetworkReply *replysaldo, *replyLuottoraja, *replyAsiakastiedot;
    QByteArray response_data, response_data1, response_dataAsiakastiedot;
    consoleSaldo *objConSaldo;
    int counter;
    QTimer *objTimerit;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // CONSOLECREDITDEBIT_H
