#include "consolenosto.h"
#include "ui_consolenosto.h"

consoleNosto::consoleNosto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleNosto)
{
    ui->setupUi(this);
}

consoleNosto::~consoleNosto()
{
    delete ui;
}

void consoleNosto::on_btn20e_clicked()
{

}


void consoleNosto::on_btn40e_clicked()
{

}


void consoleNosto::on_btn60e_clicked()
{

}


void consoleNosto::on_btn100e_clicked()
{

}


void consoleNosto::on_btn200e_clicked()
{

}


void consoleNosto::on_btn500e_clicked()
{

}


void consoleNosto::on_btnMuuSumma_clicked()
{

}


void consoleNosto::on_btnSulje_clicked()
{
    this->close();
}
