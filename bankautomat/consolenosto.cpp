#include "consolenosto.h"
#include "ui_consolenosto.h"

consoleNosto::consoleNosto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleNosto)
{
    ui->setupUi(this);
    counter = 0;
    objTimer = new QTimer;
    objConMuuSumma = new consoleMuuSumma;
    connect(objConMuuSumma, SIGNAL(signalReset(int)), this, SLOT(resetCounter(int)));
    connect(objConMuuSumma, SIGNAL(signalSumma(double)), this, SLOT(receiverMuusumma(double)));
    connect(objTimer, SIGNAL(timeout()), this, SLOT(removText()));
}

consoleNosto::~consoleNosto()
{
    delete ui;
    delete objConMuuSumma;
    objConMuuSumma = nullptr;
}

void consoleNosto::on_btn20e_clicked()
{
    counter = 0;
    summa = 20;
    emit signalSumma(summa);
}


void consoleNosto::on_btn40e_clicked()
{
    counter = 0;
    summa = 40;
    emit signalSumma(summa);
}


void consoleNosto::on_btn60e_clicked()
{
    counter = 0;
    summa = 60;
    emit signalSumma(summa);
}


void consoleNosto::on_btn100e_clicked()
{
    counter = 0;
    summa = 100;
    emit signalSumma(summa);
}


void consoleNosto::on_btn200e_clicked()
{
    counter = 0;
    summa = 200;
    emit signalSumma(summa);
}


void consoleNosto::on_btn500e_clicked()
{
    counter = 0;
    summa = 500;
    emit signalSumma(summa);
}


void consoleNosto::on_btnMuuSumma_clicked()
{
    counter = 0;
    objConMuuSumma->show();
}


void consoleNosto::on_btnSulje_clicked()
{
   counter = 0;
    this->close();
    emit closeWindow();
    emit removConnect();
    objConMuuSumma->close();
}

void consoleNosto::timerSlot() // counter ajastin ikkunalle
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit closeWindow();
        emit removConnect();
        objConMuuSumma->close();
    }
}

void consoleNosto::receiverMuusumma(double maara) // vastaanottaa ja lähettää näppäillyn nostomäärän
{
    summa = maara;
    emit signalSumma(summa);
}

void consoleNosto::resetCounter(int luku)   //muu summa ikkunan signaalin vastaanottaja, nollaa counterin
{
    counter = luku;
}

void consoleNosto::slotKate()
{
    ui->textEditKate->setText("Kate ei riitä");
    objTimer->start(3000);

}

void consoleNosto::removText()
{
    ui->textEditKate->clear();
    objTimer->stop();
}

void consoleNosto::rahatTulossa()
{
    ui->textEditKate->setText("Rahat tulossa, odota...");
    objTimer->start(3000);
}

