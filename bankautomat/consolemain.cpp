#include "consolemain.h"
#include "ui_consolemain.h"

consoleMain::consoleMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleMain)
{
    ui->setupUi(this);
    objTimer = new QTimer;
}

consoleMain::~consoleMain()
{
    delete ui;
    delete objConNosto;
    objConNosto = nullptr;
    delete objTimer;
    objTimer = nullptr;
}



void consoleMain::on_btnNosto_clicked()
{

    objConNosto->show();
    //this->hide();
    counter = 0;
    connect(objTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    connect(this, SIGNAL(closeWindow()), this, SLOT(slotClose()));
    objTimer->start(1000);
}

void consoleMain::timerSlot()
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        disconnect(objTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
        emit closeWindow();
    }
}

void consoleMain::slotClose()
{
    objConNosto->close();
}

