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
    connect(objConNosto, SIGNAL(removConnect()), this, SLOT(conRemov()));
}


consoleMain::~consoleMain()
{
    delete ui;

    delete objConNosto;
    objConNosto = nullptr;
    qDebug() << "con main destroyer";

    delete objTimer;
    objTimer = nullptr;

    delete objConTilitapahtumat;
    objConTilitapahtumat = nullptr;

    delete getManager;
    getManager = nullptr;

    delete objConSaldo;
    objConSaldo = nullptr;
}

void consoleMain::getIDSlot(const QString &cardID)
{
    IDcard = cardID;
    qDebug() << "asiakkaan ID consolemainissa" << IDcard;

}

void consoleMain::getYhdistelmaIDSlot(const QString &korttiID)
{
    iiteekortti = korttiID;
    qDebug() <<"asiakkaan id korttityyppivalinnasta" << iiteekortti;
}

void consoleMain::on_btnNosto_clicked()
{
    QString site_urlKorttityyppi="http://localhost:3000/korttityyppi/"+korttiID;
    QString credentialsKorttityyppi="1234:4321";
    QNetworkRequest requestKorttityyppi((site_urlKorttityyppi)); requestKorttityyppi.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray dataKorttityyppi = credentialsKorttityyppi.toLocal8Bit().toBase64();
    QString headerDataKorttityyppi = "Basic " + dataKorttityyppi;
    requestKorttityyppi.setRawHeader( "Authorization", headerDataKorttityyppi.toLocal8Bit() );
    korttityyppiManager = new QNetworkAccessManager(this);
    connect(korttityyppiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getKorttityyppiNostoSlot(QNetworkReply*)));
    replyKorttityyppi = korttityyppiManager->get(requestKorttityyppi);

    objConNosto->show();
    counter = 0;
    connect(objTimer, SIGNAL(timeout()), objConNosto, SLOT(timerSlot()));
    connect(objConNosto, SIGNAL(closeWindow()), this, SLOT(slotCloseNosto()));
    objTimer->start(1000);
    this->hide();
}

void consoleMain::getKorttityyppiNostoSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();

    if(response_data == "credit") {
        qDebug() << " credit, ei yhdistelma";
        connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
    } else if(response_data == "debit") {
        qDebug() << "debit, ei yhdistelma";
        connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
    } else {
            if(tyyppiValinta == "debit") {
                qDebug() << "yhdistelma debit";
                connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
            } else if(tyyppiValinta == "credit") {
               qDebug() << "yhdistelma credit";
               connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
            } else {
                qDebug() << "Invalid data";
            }
    }
}

void consoleMain::transferCredit(double summa)
{
    qDebug() << "credit " << summa;

   // disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));

}

void consoleMain::conRemov()
{
     disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
     disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
     qDebug() << "disc toimii!";
}

void consoleMain::transferDebit(double summa)
{
    qDebug() << "debit " << summa;

   // disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
}

void consoleMain::slotTyyppiValinta(const QString &valinta)
{
    tyyppiValinta = valinta;
    qDebug() << "tyyppivalinta" + tyyppiValinta;
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

void consoleMain::slotCardID(const QString &id)
{
    korttiID = id;
    qDebug() << korttiID;
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

void consoleMain::getTapahtumatSlot(QNetworkReply*)
{
    response_data=replytapahtumat->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumat;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       tilitapahtumat+=QString::number(json_obj["summa"].toInt())+"€ "+json_obj["tapahtuma"].toString()+" "+json_obj["date"].toString()+" Tilin omistaja: "+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r";
       //Qstring tyyppinen olio datan esittämistä varten tilitapahtumissa
    }
    qDebug() << "Tilitapahtumat: "<< tilitapahtumat;
    emit sendTilitapahtumat(tilitapahtumat); //lähetetään data tilitapahtumille.
    replytapahtumat->deleteLater();
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
   // replysaldo->deleteLater();
}

void consoleMain::getLuottorajaSlot(QNetworkReply*)
{
    response_data=replysaldo->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString saldo;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       saldo+=QString::number(json_obj["luottoraja"].toInt())+"€ luottoraja Asiakas: "+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r"; //Määritetään QString saldon sisältämä tieto.

    }
    emit sendSaldo(saldo); //Lähetetään tietokannasta saatu data saldo-ikkunaan.
    //replysaldo->deleteLater();
}

void consoleMain::getYhdistelmaSlotSaldo(const QString &saldoYhdistelma )
{
    saldo = saldoYhdistelma;
    emit sendSaldo(saldo);

    }

void consoleMain::getYhdistelmaSlotLuottoraja(const QString &luottorajaYhdistelma)
{
    saldo = luottorajaYhdistelma;
    emit sendSaldo(saldo);
}

void consoleMain::on_btnSaldo_clicked()
{
    QString site_urlKorttityyppi="http://localhost:3000/korttityyppi/"+korttiID;
    QString credentialsKorttityyppi="1234:4321";
    QNetworkRequest requestKorttityyppi((site_urlKorttityyppi)); requestKorttityyppi.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray dataKorttityyppi = credentialsKorttityyppi.toLocal8Bit().toBase64();
    QString headerDataKorttityyppi = "Basic " + dataKorttityyppi;
    requestKorttityyppi.setRawHeader( "Authorization", headerDataKorttityyppi.toLocal8Bit() );
    korttityyppiManager = new QNetworkAccessManager(this);
    connect(korttityyppiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getKorttityyppiSlot(QNetworkReply*)));
    replyKorttityyppi = korttityyppiManager->get(requestKorttityyppi);
    objConSaldo->show();

    counter = 0;
    connect(objTimer, SIGNAL(timeout()), objConSaldo, SLOT(timerSlot()));
    connect(objConSaldo, SIGNAL(closeWindow()), this, SLOT(slotCloseSaldo()));
    objTimer->start(1000);
    this->hide();
}

void consoleMain::getKorttityyppiSlot(QNetworkReply *replyKorttityyppi)
{
    QByteArray response_dataKorttityyppi=replyKorttityyppi->readAll();

    if (response_dataKorttityyppi == "debit") {

        QString site_url="http://localhost:3000/saldo/"+korttiID; //Haetaan asiakkaan saldo tietokannasta kortin id:n perusteella.
            QString credentials="1234:4321";
            QNetworkRequest request((site_url));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QByteArray data = credentials.toLocal8Bit().toBase64();
            QString headerData = "Basic " + data;
            request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

            getManager = new QNetworkAccessManager(this);
            connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getSaldoSlot(QNetworkReply*)));
            replysaldo = getManager->get(request);

    }
    else if (response_dataKorttityyppi == "credit") {
        QString site_url="http://localhost:3000/luottoraja/"+korttiID; //Haetaan asiakkaan luottoraja tietokannasta kortin id:n perusteella.
            QString credentials="1234:4321";
            QNetworkRequest request((site_url));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QByteArray data = credentials.toLocal8Bit().toBase64();
            QString headerData = "Basic " + data;
            request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

            getManager = new QNetworkAccessManager(this);
            connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLuottorajaSlot(QNetworkReply*)));
            replysaldo = getManager->get(request);

    }

}

void consoleMain::getAsiakastiedot(const QString &asiakastiedot) //Vastaanottaa mainwindowsta tulevan tiedon ja näyttää sen tekstikentässä.
{
    asiakkaanTiedot = asiakastiedot;;
    ui->lineEditAsiakastiedot->setText(asiakkaanTiedot);
}

void consoleMain::getYhdistelmaSlotAsiakastiedot(const QString &asiakkaantiedot)
{
    asiakkaanTiedot=asiakkaantiedot;
    ui->lineEditAsiakastiedot->setText(asiakkaanTiedot);
}

void consoleMain::on_btnKirjauduUlos_clicked()
{
    this->close();
    disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
    disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
}


