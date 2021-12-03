#ifndef CONSOLETILITAPAHTUMAT_H
#define CONSOLETILITAPAHTUMAT_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class consoleTilitapahtumat;
}

class consoleTilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit consoleTilitapahtumat(QWidget *parent = nullptr);
    ~consoleTilitapahtumat();

private slots:
    void getDataSlot(const QString &);
    void on_btnSulje_clicked();
    void timerSlot();
    void listTapahtumatSlot(QNetworkReply *reply);
    void on_btnPrev10_clicked();
    void on_btnNext10_clicked();
    void slotKorttiId(const QString &);

signals:
    void closeWindow();

private:
    Ui::consoleTilitapahtumat *ui;
    int counter, listarajaus;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString tapahtumat, korttiID; //vastaanottaa jälleen kortinnumeron ym.välitettävän datan.
};

#endif // CONSOLETILITAPAHTUMAT_H
