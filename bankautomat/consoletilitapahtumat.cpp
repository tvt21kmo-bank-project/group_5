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

void consoleTilitapahtumat::getDataSlot(const QString &tilitapahtumat)
{
    tapahtumat = tilitapahtumat; //Käytössä koko oliossa
    qDebug()<<"Asiakkaan tilitapahtumat" << tapahtumat;
    QString omistaja;
    omistaja = tapahtumat.section(',',3,4); //pilkotaan merkkijonosta omistaja
    omistaja.replace(QString(","), QString(" ")); //vaihdetaan pilkut välilyönneiksi
    tapahtumat.replace(QString (","), QString(" "));
    tapahtumat.remove(omistaja);
    QString x=" Tilin omistaja: "; //liitetään merkkijonot yhteen
    x.append(omistaja);

    qDebug()<<omistaja;
    ui->lineEditTapahtumat->setText(x); //printataan tilinomistaja
    ui->textEditTapahtumat->setText(tapahtumat); //printataan tilitapahtumat

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


void consoleTilitapahtumat::on_btnPrev10_clicked()
{

}


void consoleTilitapahtumat::on_btnNext10_clicked()
{

}

