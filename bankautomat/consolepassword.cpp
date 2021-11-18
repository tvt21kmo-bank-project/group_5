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
    //this->hide();
}

void consolePassword::on_btnZero_clicked()
{
    ui->lineEditPIN->insert("0");
}


void consolePassword::on_btnOne_clicked()
{
    ui->lineEditPIN->insert("1");
}


void consolePassword::on_btnTwo_clicked()
{
    ui->lineEditPIN->insert("2");
}


void consolePassword::on_btnThree_clicked()
{
    ui->lineEditPIN->insert("3");
}


void consolePassword::on_btnFour_clicked()
{
    ui->lineEditPIN->insert("4");
}


void consolePassword::on_btnFive_clicked()
{
    ui->lineEditPIN->insert("5");
}


void consolePassword::on_btnSix_clicked()
{
    ui->lineEditPIN->insert("6");
}


void consolePassword::on_btnSeven_clicked()
{
    ui->lineEditPIN->insert("7");
}


void consolePassword::on_btnEight_clicked()
{
    ui->lineEditPIN->insert("8");
}


void consolePassword::on_btnNine_clicked()
{
    ui->lineEditPIN->insert("9");
}


void consolePassword::on_btnReset_clicked()
{
    ui->lineEditPIN->clear();
}


void consolePassword::on_btnOK_clicked()
{

}

