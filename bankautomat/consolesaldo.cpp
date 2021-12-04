#include "consolesaldo.h"
#include "ui_consolesaldo.h"

consoleSaldo::consoleSaldo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleSaldo)
{
    ui->setupUi(this);
    counter = 0;
}

consoleSaldo::~consoleSaldo()
{
    delete ui;
}

void consoleSaldo::on_btnSulje_clicked()
{
    counter = 0;
    this->close();
    emit closeWindow();
}

void consoleSaldo::getSaldo(const QString &saldo) //Vastaanottaa mainwindowsta tulevan tiedon ja näyttää sen tekstikentässä.
{
    asiakkaanSaldo = saldo;
    qDebug() <<"täältä tulee saldo:"<<asiakkaanSaldo;
    ui->lineEditSaldo->setText(asiakkaanSaldo);
}

void consoleSaldo::timerSlot()
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit closeWindow();
    }
}

