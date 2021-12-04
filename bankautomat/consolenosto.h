#ifndef CONSOLENOSTO_H
#define CONSOLENOSTO_H

#include <QDialog>
#include <QDebug>
#include <QTimer>
#include "consolemuusumma.h"

namespace Ui {
class consoleNosto;
}

class consoleNosto : public QDialog
{
    Q_OBJECT

public:
    explicit consoleNosto(QWidget *parent = nullptr);
    ~consoleNosto();

private slots:
    void on_btn20e_clicked();
    void on_btn40e_clicked();
    void on_btn60e_clicked();
    void on_btn100e_clicked();
    void on_btn200e_clicked();
    void on_btn500e_clicked();
    void on_btnMuuSumma_clicked();
    void on_btnSulje_clicked();
    void timerSlot();
    void receiverMuusumma(double);
    void resetCounter(int);
    void slotKate();
    void removText();
    void rahatTulossa();

signals:
    void closeWindow();
    void signalSumma(double);
    void removConnect();    //poistaa connectit nostossa

private:
    Ui::consoleNosto *ui;
    consoleMuuSumma *objConMuuSumma;
    QTimer *objTimer;
    int counter, summa;
};

#endif // CONSOLENOSTO_H
