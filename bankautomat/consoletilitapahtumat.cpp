#include "consoletilitapahtumat.h"
#include "ui_consoletilitapahtumat.h"

consoleTilitapahtumat::consoleTilitapahtumat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleTilitapahtumat)
{
    ui->setupUi(this);
    counter = 0;
}

consoleTilitapahtumat::~consoleTilitapahtumat()
{
    delete ui;
}

void consoleTilitapahtumat::on_btnSulje_clicked()
{
    this->close();
    emit closeWindow();
}

void consoleTilitapahtumat::timerSlot()
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit closeWindow();
    }
}

