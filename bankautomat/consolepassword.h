#ifndef CONSOLEPASSWORD_H
#define CONSOLEPASSWORD_H

#include <QDialog>
#include <consolemain.h>

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

private slots:
    void loginSlot();

    void on_btnKirjaudu_clicked();

private:
    Ui::consolePassword *ui;
    consoleMain *objConMain = new consoleMain;
};

#endif // CONSOLEPASSWORD_H
