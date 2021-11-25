#ifndef CONSOLETILITAPAHTUMAT_H
#define CONSOLETILITAPAHTUMAT_H

#include <QDialog>
#include <QDebug>
#include <QString>

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

    void on_btnPrev10_clicked();

    void on_btnNext10_clicked();

signals:
    void closeWindow();

private:
    Ui::consoleTilitapahtumat *ui;
    int counter;
    QString tapahtumat; //vastaanottaa jälleen kortinnumeron ym.välitettävän datan.
};

#endif // CONSOLETILITAPAHTUMAT_H
