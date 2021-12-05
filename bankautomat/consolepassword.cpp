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
    objTimer = new QTimer;
    objTimeri = new QTimer;
    connect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(getIDSlot(const QString &))); // välitetään consolemainiin signaalin avulla kortin numero.
    connect(this,SIGNAL(sendAsiakastiedot(const QString &)), objConMain, SLOT(getAsiakastiedot(const QString &)));
    connect(objTimer, SIGNAL(timeout()), objCredeb, SLOT(timerSlot()));
    connect(objCredeb, SIGNAL(stopTimer()), this, SLOT(slotStopTimer()));
    connect(objCredeb, SIGNAL(closeWindow()), this, SLOT(slotCloseWindow()));
    connect(objConMain, SIGNAL(closeMainWindow()), this, SLOT(slotCloseConsoleMain()));
    connect(objConMain,SIGNAL(stopTimer()), this, SLOT(slotStopTimer()));
    connect(objTimeri, SIGNAL(timeout()), objConMain, SLOT(timer30Slot()));
    connect(objConMain, SIGNAL(startTimer()), this, SLOT(startTimerSlot()));
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

    QString site_urlAsiakastiedot="http://localhost:3000/asiakastiedot/"+cardID; //Haetaan tietokannasta asiakastiedot kortin ID:n perusteella.
    QString credentialsAsiakastiedot="1234:4321";
    QNetworkRequest requestAsiakastiedot((site_urlAsiakastiedot));
    requestAsiakastiedot.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray dataAsiakastiedot = credentialsAsiakastiedot.toLocal8Bit().toBase64();
    QString headerDataAsiakastiedot = "Basic " + dataAsiakastiedot;
    requestAsiakastiedot.setRawHeader( "Authorization", headerDataAsiakastiedot.toLocal8Bit() );

    asiakastiedotManager = new QNetworkAccessManager(this);
    connect(asiakastiedotManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAsiakastiedotSlot(QNetworkReply*)));
    replyAsiakastiedot = asiakastiedotManager->get(requestAsiakastiedot);
    objTimeri->start(1000); //conmainin timerin aloitus
    this->close();
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
         ui->lineEditVaaraPIN->setText("Väärä PIN");
                  ui->lineEditPIN->clear();
                  counterPIN++;
                  if(counterPIN == 3){
                      connect(this, SIGNAL(signalLukitseKortti()), this,SLOT(updateKorttiLukittu()));
                      emit signalLukitseKortti();
                      ui->lineEditVaaraPIN->clear();
                      counterPIN = 0;
                      this->close();


         objTimeri->stop();
     }
}
}

void consolePassword::updateKorttiLukittu()
{
    QJsonObject json1;
    json1.insert("korttilukittu",1);
    QString site_url1="http://localhost:3000/korttilukittu/"+cardID;
    QString credentials1="1234:4321";
    QNetworkRequest request1((site_url1));
    request1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data1 = credentials1.toLocal8Bit().toBase64();
    QString headerData1 = "Basic " + data1;
    request1.setRawHeader( "Authorization", headerData1.toLocal8Bit() );

    putManager = new QNetworkAccessManager(this);
    connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateKorttiLukittuSlot(QNetworkReply*)));
    replyLukitseKortti = putManager->put(request1, QJsonDocument(json1).toJson());

    qDebug()<<replyLukitseKortti;
    qDebug()<<QJsonDocument(json1).toJson();

}
void consolePassword::updateKorttiLukittuSlot(QNetworkReply *replyLukitseKortti)
{
    response_dataKorttilukittu=replyLukitseKortti->readAll();
    //qDebug()<<reply;
    qDebug()<<response_dataKorttilukittu;
    //replyLukitseKortti->deleteLater();
}

void consolePassword::credebSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
      qDebug() << response_data;

      if(response_data == "true") {
          qDebug() << "Credit/Debit ominaisuus";
          connect(this, SIGNAL(sendID(const QString &)), objCredeb, SLOT(slotCardID(const QString &)));
          emit sendID(cardID);
          disconnect(this, SIGNAL(sendID(const QString &)), objCredeb, SLOT(slotCardID(const QString &)));
          objTimer->start(1000);
          objCredeb->show();
          counterPIN = 0;
          this->close();
      } else if(response_data == "false") {
          qDebug() << "Ei yhdistelmakorttiominaisuutta";
          connect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(slotCardID(const QString &)));
          emit sendID(cardID); //lähetetään korttinumero seuraavalle formille
          disconnect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(slotCardID(const QString &)));
          objConMain->show();
          counterPIN = 0;
          this->close(); //suljetaan PIN-kenttä onnistuneen kirjauksen jälkeen
      }
}


void consolePassword::getAsiakastiedotSlot(QNetworkReply *replyAsiakastiedot)
{
    response_dataAsiakastiedot=replyAsiakastiedot->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_dataAsiakastiedot);
    QJsonArray json_array = json_doc.array();
    QString asiakastiedot;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       asiakastiedot+=QString::fromLatin1(" Tervetuloa ")+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r";

}
    emit sendAsiakastiedot(asiakastiedot); //Lähetetään asiakastiedot consoleMainiin, jossa ne tulostuvat tekstikenttään.

}

void consolePassword::slotStopTimer()
{
    objTimer->stop();
    objTimeri->stop();
}

void consolePassword::slotCloseWindow()
{
    objCredeb->close();
}
void consolePassword::slotCloseConsoleMain()
{
    objConMain->close();
}

void consolePassword::startTimerSlot()
{
    objTimeri->start(1000);
}

