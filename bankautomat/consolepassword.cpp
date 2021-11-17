#include "consolepassword.h"
#include "ui_consolepassword.h"

consolePassword::consolePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consolePassword)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signalKirjaudu()), this, SLOT(loginSlot()));
}

consolePassword::~consolePassword()
{
    delete ui;
    delete objConMain;
    objConMain = nullptr;
}

void consolePassword::on_btnKirjaudu_clicked()
{
     emit signalKirjaudu();
}

void consolePassword::loginSlot()
{
    objConMain->show();
    //this->close();
}
