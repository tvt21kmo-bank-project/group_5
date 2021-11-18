#ifndef CONSOLEMAIN_H
#define CONSOLEMAIN_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include "consolenosto.h"

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
    void on_btnNosto_clicked();
    void timerSlot();
    void slotClose();
    void on_btnKirjauduUlos_clicked();

signals:
    void closeWindow();

private:
    Ui::consoleMain *ui;
    consoleNosto *objConNosto = new consoleNosto;
    QTimer *objTimer;
    int counter;
};

#endif // CONSOLEMAIN_H
