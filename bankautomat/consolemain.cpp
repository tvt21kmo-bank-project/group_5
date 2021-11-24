#include "consolemain.h"
#include "ui_consolemain.h"

consoleMain::consoleMain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleMain)
{
    ui->setupUi(this);
    objTimer = new QTimer;
    objConNosto= new consoleNosto;
    objConTilitapahtumat = new consoleTilitapahtumat;
    objConSaldo = new consoleSaldo;
    counter = 0;
    connect(this, SIGNAL(sendTilitapahtumat(const QString &)), objConTilitapahtumat, SLOT(getDataSlot(const QString &)));
    connect(this, SIGNAL(sendSaldo(const QString &)), objConSaldo,SLOT(getSaldo(const QString &)));
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

    delete getManager;
    getManager = nullptr;

    delete objConSaldo;
    objConSaldo = nullptr;
}

void consoleMain::getTapahtumatSlot(QNetworkReply*)
{
    response_data=replytapahtumat->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumat;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       tilitapahtumat+=QString::number(10)+"  "+json_obj["date"].toString()+" "+json_obj["tapahtuma"].toString()+"  "+json_obj["summa"].toInt();

    }
    qDebug() << "Tilitapahtumat: "<< tilitapahtumat;
    emit sendTilitapahtumat(tilitapahtumat); //lähetetään data tilitapahtumille.
    replytapahtumat->deleteLater();
}


void consoleMain::getIDSlot(const QString &cardID)
{
    IDcard = cardID;
    qDebug() << "asiakkaan ID consolemainissa" << IDcard;

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

void consoleMain::slotCloseSaldo()

{
    disconnect(objTimer, SIGNAL(timeout()), objConSaldo, SLOT(timerSlot()));
    objConSaldo->close();
    this->show();
}

void consoleMain::on_btnTilitapahtumat_clicked()
{
    QString site_url="http://localhost:3000/tilitapahtumat/"+IDcard;
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getTapahtumatSlot(QNetworkReply*)));
    replytapahtumat = getManager->get(request);
    objConTilitapahtumat->show();

    counter = 0;
    connect(objTimer, SIGNAL(timeout()), objConTilitapahtumat, SLOT(timerSlot()));
    connect(objConTilitapahtumat, SIGNAL(closeWindow()), this, SLOT(slotCloseTilitapahtumat()));
    objTimer->start(1000);
    this->hide();
}

void consoleMain::getSaldoSlot(QNetworkReply*)
{
    response_data=replysaldo->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString saldo;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       saldo+=QString::number(json_obj["saldo"].toInt())+"€ Asiakas: "+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r"; //Määritetään QString saldon sisältämä tieto.

    }
    emit sendSaldo(saldo); //Lähetetään tietokannasta saatu data saldo-ikkunaan.
    replysaldo->deleteLater();
}

void consoleMain::on_btnSaldo_clicked()
{
    QString site_url="http://localhost:3000/saldo/"+IDcard; //Haetaan asiakkaan saldo tietokannasta kortin id:n perusteella.
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getSaldoSlot(QNetworkReply*)));
    replysaldo = getManager->get(request);
    objConSaldo->show();

    counter = 0;
    connect(objTimer, SIGNAL(timeout()), objConSaldo, SLOT(timerSlot()));
    connect(objConSaldo, SIGNAL(closeWindow()), this, SLOT(slotCloseSaldo()));
    objTimer->start(1000);
    this->hide();
}

void consoleMain::on_btnKirjauduUlos_clicked()
{
    this->close();
}


