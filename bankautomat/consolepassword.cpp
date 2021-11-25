#include "consolepassword.h"
#include "ui_consolepassword.h"

consolePassword::consolePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consolePassword)
{
    ui->setupUi(this);
    objConMain = new consoleMain;
    objCredeb = new consoleCreditDebit;
    credebManager = new QNetworkAccessManager;
    connect(this, SIGNAL(signalKirjaudu()), this, SLOT(loginSlotFast()));
    connect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(getIDSlot(const QString &))); // välitetään consolemainiin signaalin avulla kortin numero.

}

consolePassword::~consolePassword()
{
    delete ui;
    delete objConMain;
    objConMain = nullptr;
    delete loginManager;
    loginManager = nullptr;
    delete objCredeb;
    objCredeb = nullptr;
}

void consolePassword::connectingSlot(const QString &IDcard)
{
    ui->lineEditPIN->clear();
    cardID = IDcard;
    qDebug() << "asiakkaan ID paaswordissä" << cardID;

}

void consolePassword::on_btnKirjaudu_clicked()
{
     emit signalKirjaudu();
}

void consolePassword::loginSlotFast()
{
    objConMain->show();
}

void consolePassword::on_btnZero_clicked()
{
    ui->lineEditPIN->insert("0");
}


void consolePassword::on_btnOne_clicked()
{
    ui->lineEditPIN->insert("1");
}


void consolePassword::on_btnTwo_clicked()
{
    ui->lineEditPIN->insert("2");
}


void consolePassword::on_btnThree_clicked()
{
    ui->lineEditPIN->insert("3");
}


void consolePassword::on_btnFour_clicked()
{
    ui->lineEditPIN->insert("4");
}


void consolePassword::on_btnFive_clicked()
{
    ui->lineEditPIN->insert("5");
}


void consolePassword::on_btnSix_clicked()
{
    ui->lineEditPIN->insert("6");
}


void consolePassword::on_btnSeven_clicked()
{
    ui->lineEditPIN->insert("7");
}


void consolePassword::on_btnEight_clicked()
{
    ui->lineEditPIN->insert("8");
}


void consolePassword::on_btnNine_clicked()
{
    ui->lineEditPIN->insert("9");
}


void consolePassword::on_btnReset_clicked()
{
    ui->lineEditPIN->clear();
}


void consolePassword::on_btnOK_clicked()
{
    QJsonObject json; //create JSON object and insert data
    json.insert("idcard",cardID);
    json.insert("pincode",ui->lineEditPIN->text());
    ui->lineEditPIN->clear();
    QString site_url="http://localhost:3000/login";
    QString credentials="1234:4321";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(json).toJson());
}

void consolePassword::loginSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
     if (response_data == "true") {
         QJsonObject json;
         QString site_url="http://localhost:3000/creditdebit/"+cardID;
         QString credentials="1234:4321";
         QNetworkRequest request((site_url));
         request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
         QByteArray data = credentials.toLocal8Bit().toBase64();
         QString headerData = "Basic " + data;
         request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
         connect(credebManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(credebSlot(QNetworkReply*)));
         reply = credebManager->get(request);
     } else {
         qDebug() << "Väärä PIN";
     }
    // reply->deleteLater(); tätä ei saa olla !!!
}

void consolePassword::credebSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
      qDebug() << response_data;

      if(response_data == "true") {
          qDebug() << "Credit/Debit ominaisuus";
          connect(this, SIGNAL(sendID(const QString &)), objCredeb, SLOT(slotCardID(const QString &)));
          emit sendID(cardID);
          connect(this, SIGNAL(sendID(const QString &)), objCredeb, SLOT(slotCardID(const QString &)));
          objCredeb->show();
          this->close();
      } else if(response_data == "false") {
          qDebug() << "Ei yhdistelmakorttiominaisuutta";
          connect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(slotCardID(const QString &)));
          emit sendID(cardID); //lähetetään korttinumero seuraavalle formille
          disconnect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(slotCardID(const QString &)));
          objConMain->show();
          this->close(); //suljetaan PIN-kenttä onnistuneen kirjauksen jälkeen
      }
}

