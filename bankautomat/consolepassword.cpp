#include "consolepassword.h"
#include "ui_consolepassword.h"

consolePassword::consolePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consolePassword)
{
    ui->setupUi(this);
    counter = 0;
    counterPIN = 0;
    objConMain = new consoleMain;
    objCredeb = new consoleCreditDebit;

    objTimer = new QTimer;
    objTimeri = new QTimer;
    objTekstiTimer = new QTimer;
    connect(this,SIGNAL(sendAsiakastiedot(const QString &)), objConMain, SLOT(getAsiakastiedot(const QString &)));
    connect(objTimer, SIGNAL(timeout()), objCredeb, SLOT(timerSlot()));
    connect(objCredeb, SIGNAL(stopTimercredeb()), this, SLOT(slotStopTimer()));
    connect(objCredeb, SIGNAL(closeWindow()), this, SLOT(slotCloseWindow()));
    connect(this, SIGNAL(signalLukitseKortti()), this,SLOT(updateKorttiLukittu()));
    connect(this, SIGNAL(sendTeksti(const QString &)), this, SLOT(slotIlmoitus(const QString &)));
    connect(objTekstiTimer, SIGNAL(timeout()), this, SLOT(pyyhiTeksti()));



}

consolePassword::~consolePassword()
{
    delete ui;
    delete objConMain;
    objConMain = nullptr;
    delete objCredeb;
    objCredeb = nullptr;
    delete objTimer;
    objTimer = nullptr;
    delete objTimeri;
    objTimeri = nullptr;
    delete objTekstiTimer;
    objTekstiTimer = nullptr;

}

void consolePassword::connectingSlot(const QString &IDcard)
{
    ui->lineEditPIN->clear();
    cardID = IDcard;
    qDebug() << "asiakkaan ID passwordissa" << cardID;

}

void consolePassword::on_btnZero_clicked()
{
    ui->lineEditPIN->insert("0");
    counter = 0;
}


void consolePassword::on_btnOne_clicked()
{
    ui->lineEditPIN->insert("1");
    counter = 0;
}


void consolePassword::on_btnTwo_clicked()
{
    ui->lineEditPIN->insert("2");
    counter = 0;
}


void consolePassword::on_btnThree_clicked()
{
    ui->lineEditPIN->insert("3");
    counter = 0;
}


void consolePassword::on_btnFour_clicked()
{
    ui->lineEditPIN->insert("4");
    counter = 0;
}


void consolePassword::on_btnFive_clicked()
{
    ui->lineEditPIN->insert("5");
    counter = 0;
}


void consolePassword::on_btnSix_clicked()
{
    ui->lineEditPIN->insert("6");
    counter = 0;
}


void consolePassword::on_btnSeven_clicked()
{
    ui->lineEditPIN->insert("7");
    counter = 0;
}


void consolePassword::on_btnEight_clicked()
{
    ui->lineEditPIN->insert("8");
    counter = 0;
}


void consolePassword::on_btnNine_clicked()
{
    ui->lineEditPIN->insert("9");
    counter = 0;
}


void consolePassword::on_btnReset_clicked()
{
    ui->lineEditPIN->clear();
    counter = 0;
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
    reply = loginManager->post(request, QJsonDocument(json).toJson());
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));



}

void consolePassword::loginSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
     if (response_data == "true") {

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
         counter = 0;
         objTimeri->start(1000);
         objTimer->start(1000);
          emit stopTimerPass(); //pys??ytet????n conpass:n timeri
            this->close();


     } else {

         objTimeri->stop(); //pys??ytet????n conmainin timeri jos pin menee v????rin
  
         if(counterPIN == 3){
             emit signalLukitseKortti();
             counterPIN = 0;
             this->close();
             objTimeri->stop();
             objTimer->stop();
             counter = 0;
             emit stopTimerPass();
         } else {
                qDebug() << "V????r?? PIN";
                emit sendTeksti("V????r?? PIN");
                counterPIN++;
                emit signalLukitseKortti();
                qDebug() << "v????ri?? kertoja" << counterPIN;

                objTimeri->stop();
                objTimer->stop();
                counter = 0;
         }
    }

loginManager->deleteLater();
reply->deleteLater();
}

void consolePassword::updateKorttiLukittu()
{
    QJsonObject json1;
    json1.insert("korttilukittu",counterPIN);
    QString site_url1="http://localhost:3000/korttilukittu/"+cardID;
    QString credentials1="1234:4321";
    QNetworkRequest request1((site_url1));
    request1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data1 = credentials1.toLocal8Bit().toBase64();
    QString headerData1 = "Basic " + data1;
    request1.setRawHeader( "Authorization", headerData1.toLocal8Bit() );
    putManager = new QNetworkAccessManager(this);
    replyLukitseKortti = putManager->put(request1, QJsonDocument(json1).toJson());
    connect(putManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateKorttiLukittuSlot(QNetworkReply*)));
}
void consolePassword::updateKorttiLukittuSlot(QNetworkReply *replyLukitseKortti)
{
    response_dataKorttilukittu=replyLukitseKortti->readAll();

    if (counterPIN == 3) {
        counter = 0;
        emit stopTimerPass();
        emit sendTeksti("Kortti lukittu!");
    }
    replyLukitseKortti->deleteLater();
    putManager->deleteLater();
}

void consolePassword::credebSlot(QNetworkReply *reply)
{

    QByteArray response_data=reply->readAll();
      qDebug() << response_data;

      if(response_data == "true") {

          qDebug() << "Credit/Debit ominaisuus";
          connect(this, SIGNAL(sendID(const QString &)), objCredeb, SLOT(slotCardID(const QString &)));
          emit sendID(cardID);
          counter = 0;
          objTimeri->stop();
          disconnect(objTimer, SIGNAL(timeout()), objCredeb, SLOT(timerSlot()));
          disconnect(this, SIGNAL(sendID(const QString &)), objCredeb, SLOT(slotCardID(const QString &)));
          disconnect(objConMain, SIGNAL(startTimer()), this, SLOT(startTimerSlot()));
          disconnect(objTimeri, SIGNAL(timeout()), objConMain, SLOT(timer30Slot()));
          disconnect(objConMain, SIGNAL(closeMainWindow()), this, SLOT(slotCloseConsoleMain()));
          connect(objTimer, SIGNAL(timeout()), objCredeb, SLOT(timerSlot()));
          connect(objCredeb, SIGNAL(stopTimercredeb()), this, SLOT(slotStopTimer()));
          connect(objCredeb, SIGNAL(closeWindow()), this, SLOT(slotCloseWindow()));
          objCredeb->show();
          this->close();
          emit stopTimerPass();
          counterPIN = 0;
          emit signalLukitseKortti();


      } else if(response_data == "false") {
          counter = 0;
          objTimer->stop();
          disconnect(objTimeri, SIGNAL(timeout()), objConMain, SLOT(timer30Slot()));
          disconnect(objTimer, SIGNAL(timeout()), objCredeb, SLOT(timerSlot()));
          disconnect(objCredeb, SIGNAL(stopTimercredeb()), this, SLOT(slotStopTimer()));
          disconnect(objCredeb, SIGNAL(closeWindow()), this, SLOT(slotCloseWindow()));
          connect(objConMain, SIGNAL(closeMainWindow()), this, SLOT(slotCloseConsoleMain()));
          connect(objConMain,SIGNAL(stopTimer()), this, SLOT(slotStopTimerMain()));
          connect(objTimeri, SIGNAL(timeout()), objConMain, SLOT(timer30Slot()));
          connect(objConMain, SIGNAL(startTimer()), this, SLOT(startTimerSlot()));
          qDebug() << "Ei yhdistelmakorttiominaisuutta";
          connect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(slotCardID(const QString &)));
          emit sendID(cardID); //l??hetet????n korttinumero seuraavalle formille
          disconnect(this, SIGNAL(sendID(const QString &)), objConMain, SLOT(slotCardID(const QString &)));
          objConMain->show();
          this->close(); //suljetaan PIN-kentt?? onnistuneen kirjauksen j??lkeen
          emit stopTimerPass();
          counterPIN = 0;
          emit signalLukitseKortti();

      }
reply->deleteLater();
credebManager->deleteLater();

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
    emit sendAsiakastiedot(asiakastiedot); //L??hetet????n asiakastiedot consoleMainiin, jossa ne tulostuvat tekstikentt????n.
    emit stopTimer();
            QJsonObject json;
             QString site_url="http://localhost:3000/creditdebit/"+cardID;
             QString credentials="1234:4321";
             QNetworkRequest request((site_url));
             request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
             QByteArray data = credentials.toLocal8Bit().toBase64();
             QString headerData = "Basic " + data;
             request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
             credebManager = new QNetworkAccessManager;
             reply = credebManager->get(request);
            connect(credebManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(credebSlot(QNetworkReply*)));

    replyAsiakastiedot->deleteLater();
    asiakastiedotManager->deleteLater();
}

void consolePassword::slotStopTimer()
{
    objTimer->stop();


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
void consolePassword::timerSlot() // timeri ikkunan sulkemiseen
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit closeWindow();
        emit stopTimerPass();
    }
}


void consolePassword::slotStopTimerMain()
{
     objTimeri->stop();
}
void consolePassword::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        this->close();
        emit stopTimerPass();
        emit stopTimer();
        counter = 0;
    }
}

void consolePassword::slotPinLukitus(int pinArvaukset)
{
    counterPIN = pinArvaukset;
}

void consolePassword::slotIlmoitus(const QString &arg)
{
    ui->lineEditIlmoitus->setText(arg);
    objTekstiTimer->start(3000);
}

void consolePassword::pyyhiTeksti()
{
    ui->lineEditIlmoitus->clear();
    objTekstiTimer->stop();
}
