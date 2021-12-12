#include "consolemuusumma.h"
#include "ui_consolemuusumma.h"

consoleMuuSumma::consoleMuuSumma(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleMuuSumma)
{
    ui->setupUi(this);
    counter = 0;
    objTimer = new QTimer;
    connect(objTimer, SIGNAL(timeout()), this, SLOT(clearText()));
}

consoleMuuSumma::~consoleMuuSumma()
{
    delete ui;
}

void consoleMuuSumma::on_btnZero_clicked()
{
    ui->lineEditMaara->insert("0");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnOne_clicked()
{
    ui->lineEditMaara->insert("1");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnTwo_clicked()
{
    ui->lineEditMaara->insert("2");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnThree_clicked()
{
    ui->lineEditMaara->insert("3");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnFour_clicked()
{
    ui->lineEditMaara->insert("4");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnFive_clicked()
{
    ui->lineEditMaara->insert("5");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnSix_clicked()
{
    ui->lineEditMaara->insert("6");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnSeven_clicked()
{
    ui->lineEditMaara->insert("7");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnEight_clicked()
{
    ui->lineEditMaara->insert("8");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnNine_clicked()
{
    ui->lineEditMaara->insert("9");
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnReset_clicked()
{
    ui->lineEditMaara->clear();
    ui->textEditIlmoitus->clear();
    emit signalReset(counter);
}


void consoleMuuSumma::on_btnOK_clicked() //tarkistaa luvun vastaavan setelirahaa
{
    emit signalReset(counter);
    strluku = ui->lineEditMaara->text();
    konsoliLuku = strluku.toInt();
    if(konsoliLuku == 0) {
        objTimer->start(3000);
        ui->textEditIlmoitus->setText("Näppäile jokin summa!");
    } else if(konsoliLuku == 10 or konsoliLuku == 30) {
        objTimer->start(3000);
        ui->textEditIlmoitus->setText("Ei sopivia seteleitä");
    } else {
        testi10 = konsoliLuku % 10;
        if(testi10 == 0) {
            maara = strluku.toDouble();
            emit signalSumma(maara);
            ui->lineEditMaara->clear();
            ui->textEditIlmoitus->clear();
            this->close();
        } else {
            objTimer->start(3000);
            ui->textEditIlmoitus->setText("Ei sopivia seteleitä!");
        }
    }
}
void consoleMuuSumma::on_btnSulje_clicked()
{
    emit signalReset(counter);
    ui->lineEditMaara->clear();
    this->close();
}

void consoleMuuSumma::clearText()
{
    objTimer->stop();
    ui->textEditIlmoitus->clear();
}

