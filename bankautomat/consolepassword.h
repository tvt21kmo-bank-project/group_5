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
    void finished(QNetworkReply*);
    void sendID(const QString &);

private slots:

    void connectingSlot(const QString &);

    void loginSlot(QNetworkReply *reply);

    void on_btnKirjaudu_clicked(); // for testing purposes

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
    Ui::consolePassword *ui;
<<<<<<< HEAD
    consoleMain *objConMain = new consoleMain;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString cardID;
=======
    consoleMain *objConMain;
>>>>>>> main
};

#endif // CONSOLEPASSWORD_H
