#ifndef CONSOLEMAIN_H
#define CONSOLEMAIN_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include "consolenosto.h"
#include "consoletilitapahtumat.h"

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
    void timerSlot();
    void slotCloseNosto();
    void slotCloseTilitapahtumat();
    void on_btnNosto_clicked();
    void on_btnTilitapahtumat_clicked();
    void on_btnSaldo_clicked();
    void on_btnKirjauduUlos_clicked();

signals:
    void closeWindow();

private:
    Ui::consoleMain *ui;
    consoleNosto *objConNosto = new consoleNosto;
    consoleTilitapahtumat *objConTilitapahtumat = new consoleTilitapahtumat;
    QTimer *objTimer;
    int counter;
};

#endif // CONSOLEMAIN_H
