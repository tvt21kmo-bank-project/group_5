#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "consolepassword.h"
#include "consolemain.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void finished(QNetworkReply*);
    void signalLogin(const QString &);
    void closeWindow();
    void signalKortinLukitus(int);

private slots:
    void checkCardSlot(QNetworkReply *reply);
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
    void closeConsolePassSlot();
    void stopTimerSlot();
    void startTimerSlot();
    void slotTekstiIlmoitus(const QString &);
    void pyyhiTeksti();

private:
    Ui::MainWindow *ui;
    consolePassword *objConPass;
    consoleMain *objConMain;
    QNetworkReply *reply;
    QNetworkAccessManager *checkCardManager;
    QByteArray response_data;
    QString IDcard; //välitetään signaalina muille olioille
    QString strCounterPIN;
    int counterPIN;
    QTimer *objTimer;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

};
#endif // MAINWINDOW_H
