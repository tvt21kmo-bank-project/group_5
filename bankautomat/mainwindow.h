#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "consolepassword.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnKirjaudu_clicked(); // for testing purposes
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

private:
    Ui::MainWindow *ui;
    consolePassword *objConPass = new consolePassword;
    QNetworkReply *reply;
    QNetworkAccessManager *checkCardManager;
    QByteArray response_data;
    int ID;

signals:
   void signalLogin(const QString &);
   void finished(QNetworkReply*);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

};
#endif // MAINWINDOW_H
