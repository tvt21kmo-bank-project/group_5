#include "consolenosto.h"
#include "ui_consolenosto.h"

consoleNosto::consoleNosto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleNosto)
{
    ui->setupUi(this);
    counter = 0;
}

consoleNosto::~consoleNosto()
{
    delete ui;
}

void consoleNosto::on_btn20e_clicked()
{
    counter = 0;
}


void consoleNosto::on_btn40e_clicked()
{
    counter = 0;
}


void consoleNosto::on_btn60e_clicked()
{
    counter = 0;
}


void consoleNosto::on_btn100e_clicked()
{
    counter = 0;
}


void consoleNosto::on_btn200e_clicked()
{
    counter = 0;
}


void consoleNosto::on_btn500e_clicked()
{
    counter = 0;
}


void consoleNosto::on_btnMuuSumma_clicked()
{
    counter = 0;
}


void consoleNosto::on_btnSulje_clicked()
{
    this->close();
    emit closeWindow();
}

void consoleNosto::timerSlot()
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit closeWindow();
    }
}

