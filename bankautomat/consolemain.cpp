#include "consolemain.h"
#include "ui_consolemain.h"

consoleMain::consoleMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleMain)
{
    ui->setupUi(this);
    objTimer = new QTimer;
    counter = 0;
}

consoleMain::~consoleMain()
{
    delete ui;

    delete objConNosto;
    objConNosto = nullptr;

    delete objTimer;
    objTimer = nullptr;

    delete objConTilitapahtumat;
    objConTilitapahtumat = nullptr;
}



void consoleMain::on_btnNosto_clicked()
{

    objConNosto->show();
    counter = 0;
    connect(objTimer, SIGNAL(timeout()), objConNosto, SLOT(timerSlot()));
    connect(objConNosto, SIGNAL(closeWindow()), this, SLOT(slotCloseNosto()));
    objTimer->start(1000);
    this->hide();
}

void consoleMain::timerSlot()
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit closeWindow();
    }
}

void consoleMain::slotCloseNosto()
{
    disconnect(objTimer, SIGNAL(timeout()), objConNosto, SLOT(timerSlot()));
    objConNosto->close();
    this->show();
}

void consoleMain::slotCloseTilitapahtumat()
{
    disconnect(objTimer, SIGNAL(timeout()), objConTilitapahtumat, SLOT(timerSlot()));
    objConTilitapahtumat->close();
    this->show();
}

void consoleMain::on_btnTilitapahtumat_clicked()
{
    objConTilitapahtumat->show();
    counter = 0;
    connect(objTimer, SIGNAL(timeout()), objConTilitapahtumat, SLOT(timerSlot()));
    connect(objConTilitapahtumat, SIGNAL(closeWindow()), this, SLOT(slotCloseTilitapahtumat()));
    objTimer->start(1000);
    this->hide();
}


void consoleMain::on_btnSaldo_clicked()
{

}

void consoleMain::on_btnKirjauduUlos_clicked()
{
    this->close();
}


