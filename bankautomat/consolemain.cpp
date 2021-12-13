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
    connect(this, SIGNAL(signalIlmoitaKate()), objConNosto, SLOT(slotKate()));
    connect(this, SIGNAL(signalRahatTulossa()), objConNosto, SLOT(rahatTulossa()));
    connect(this, SIGNAL(sendIdKortti(const QString &)), objConTilitapahtumat, SLOT(slotKorttiId(const QString &)));

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

    delete objConSaldo;
    objConSaldo = nullptr;
}

void consoleMain::slotCardID(const QString &id) // kortti id ilman yhdistelmäominaisuutta
{
    korttiID = id;
    qDebug() << "kortin id on" << korttiID;
}

void consoleMain::getYhdistelmaIDSlot(const QString &kortti) // yhdistelmäkortin kortti id
{
    counter = 0;
    korttiID = kortti;
    qDebug() <<"asiakkaan id korttityyppivalinnasta" << korttiID;
}

void consoleMain::on_btnNosto_clicked() //hakee kortin tyypin tietokannasta ja käynnistää timerin ja avaa nosto ikkunan
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
    this->close();
    emit stopTimer();
    emit stopTimerMain();

}

void consoleMain::getKorttityyppiNostoSlot(QNetworkReply *reply) // yhdistää korttityypin mukaan proceduuriin
{
    QByteArray response_data = reply->readAll();

    if(response_data == "credit") {
        qDebug() << " credit, ei yhdistelma";
        emit stopTimer();
        emit stopTimerMain();

        connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));    
    } else if(response_data == "debit") {
        qDebug() << "debit, ei yhdistelma";
        emit stopTimer();
        emit stopTimerMain();

        connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
    } else {
            if(tyyppiValinta == "debit") {
                qDebug() << "yhdistelma debit";
                emit stopTimer();
                emit stopTimerMain();

                connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
            } else if(tyyppiValinta == "credit") {
               qDebug() << "yhdistelma credit";
               emit stopTimer();
               emit stopTimerMain();

               connect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
            } else {
                qDebug() << "Invalid data";
                emit stopTimer();
                emit stopTimerMain();
            }
    }
    korttityyppiManager->deleteLater();
    replyKorttityyppi->deleteLater();
}

void consoleMain::transferCredit(double summa) // hakee tiedot pankkisiirto creditin mukaan
{

    siirtosumma = summa;
    qDebug() << "credit " << siirtosumma;

    QString site_url="http://localhost:3000/pankki/"+korttiID;
    QString credentials="1234:4321";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pankkiCreditManager = new QNetworkAccessManager(this);
    connect(pankkiCreditManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(pankkiCreditSlot(QNetworkReply*)));
    replyData = pankkiCreditManager->get(request);


}

void consoleMain::pankkiCreditSlot(QNetworkReply*) // sijoittaa haettuun olioon valitun määrän ja lähettää proceduuriin
{
    response_data=replyData->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject objJson;
    foreach (const QJsonValue &value, json_array) {
       objJson = value.toObject();
       objJson.insert("maara",siirtosumma);
       qDebug() << objJson;
    }
    replyData->deleteLater();

    QString site_url="http://localhost:3000/pankki/transfer_credit";
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    creditManager = new QNetworkAccessManager(this);
    connect(creditManager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(creditVastausSlot(QNetworkReply*)));
    creditReply = creditManager->post(request, QJsonDocument(objJson).toJson());
}

void consoleMain::creditVastausSlot(QNetworkReply *creditReply) // ilmoittaa onko siirto onnistunut
{
    QByteArray responseData = creditReply->readAll();
    qDebug() << responseData;
    if (responseData == "1") {
        emit signalRahatTulossa();
        qDebug() << "Siirto onnistui";
    } else {
        emit signalIlmoitaKate();
        qDebug() << "Siirto epaonnistui";
    }
    pankkiCreditManager->deleteLater();
    creditManager->deleteLater();

}

void consoleMain::conRemov()
{
     disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
     disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
}

void consoleMain::transferDebit(double summa) // hakee tiedot pankkisiirto debitin mukaan
{
    siirtosumma = summa;
    qDebug() << "debit " << siirtosumma;

    QString site_url="http://localhost:3000/pankki/"+korttiID;
    QString credentials="1234:4321";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,
    "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    pankkiDebitManager = new QNetworkAccessManager(this);
    connect(pankkiDebitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(pankkiDebitSlot(QNetworkReply*)));
    replyData = pankkiDebitManager->get(request);

}

void consoleMain::pankkiDebitSlot(QNetworkReply*) // sijoittaa haettuun olioon valitun määrän ja lähettää proceduuriin
{

    response_data=replyData->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject objJson;
    foreach (const QJsonValue &value, json_array) {
       objJson = value.toObject();
       objJson.insert("maara",siirtosumma);
       qDebug() << objJson;
    }
    replyData->deleteLater();

    QString site_url="http://localhost:3000/pankki/transfer_debit";
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    debitManager = new QNetworkAccessManager(this);
    connect(debitManager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(debitVastausSlot(QNetworkReply*)));
    debitReply = debitManager->post(request, QJsonDocument(objJson).toJson());
}

void consoleMain::debitVastausSlot(QNetworkReply *debitReply) // ilmoittaa onko siirto onnistunut
{
    QByteArray responseData = debitReply->readAll();
    qDebug() << responseData;
    if (responseData == "1") {
        emit signalRahatTulossa();
        qDebug() << "Siirto onnistui";
    } else {
        emit signalIlmoitaKate();
        qDebug() << "Siirto epaonnistui";
    }
    pankkiDebitManager->deleteLater();
    debitManager->deleteLater();
}

void consoleMain::slotTyyppiValinta(const QString &valinta)
{
    tyyppiValinta = valinta;
    qDebug() << tyyppiValinta;
}

void consoleMain::timerSlot() // timeri ikkunan sulkemiseen
{
    qDebug() << counter;
    counter++;
    if(counter == 10){
        counter = 0;
        emit startTimer();
        emit closeWindow();

    }
}

void consoleMain::slotCloseNosto()
{
    disconnect(objTimer, SIGNAL(timeout()), objConNosto, SLOT(timerSlot()));
    objConNosto->close();
    this->show();
    counter = 0;
    emit startTimer();
    emit startTimerMain();
}

void consoleMain::slotCloseTilitapahtumat()
{
    disconnect(objTimer, SIGNAL(timeout()), objConTilitapahtumat, SLOT(timerSlot()));
    objConTilitapahtumat->close();
    this->show();
    counter = 0;
    emit startTimer();
    emit startTimerMain();
}

void consoleMain::slotCloseSaldo()

{
    disconnect(objTimer, SIGNAL(timeout()), objConSaldo, SLOT(timerSlot()));
    objConSaldo->close();
    this->show();
    counter = 0;
    emit startTimer();
    emit startTimerMain();
}

void consoleMain::on_btnTilitapahtumat_clicked()
{

    QString site_url="http://localhost:3000/tilitapahtumat/"+korttiID;
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    tiliTapahtumatManager = new QNetworkAccessManager(this);
    connect(tiliTapahtumatManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getTapahtumatSlot(QNetworkReply*)));
    replytapahtumat = tiliTapahtumatManager->get(request);
    objConTilitapahtumat->show();

    counter = 0;
    emit stopTimer();
    emit stopTimerMain();
    emit sendIdKortti(korttiID);
    connect(objTimer, SIGNAL(timeout()), objConTilitapahtumat, SLOT(timerSlot()));
    connect(objConTilitapahtumat, SIGNAL(closeWindow()), this, SLOT(slotCloseTilitapahtumat()));
    objTimer->start(1000);
    this->close();
}

void consoleMain::getTapahtumatSlot(QNetworkReply*)
{
    response_data=replytapahtumat->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tilitapahtumat;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       tilitapahtumat+=QString::number(json_obj["summa"].toInt())+"€"+","+json_obj["tapahtuma"].toString()+","+json_obj["date"].toString()+","+json_obj["etunimi_asiakas"].toString()+","+json_obj["sukunimi_asiakas"].toString()+","+"\r";

      //Qstring tyyppinen olio datan esittämistä varten tilitapahtumissa
    }
    //qDebug() << "Tilitapahtumat: "<< tilitapahtumat;
    emit sendTilitapahtumat(tilitapahtumat); //lähetetään data tilitapahtumille.
}

void consoleMain::getSaldoSlot(QNetworkReply*)
{
    response_data=replysaldo->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString saldo;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       saldo+=QString::number(json_obj["saldo"].toInt())+"€ tililtä nostettavissa Asiakas: "+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r"; //Määritetään QString saldon sisältämä tieto.

    }
    emit sendSaldo(saldo); //Lähetetään tietokannasta saatu data saldo-ikkunaan.
}

void consoleMain::getLuottorajaSlot(QNetworkReply*)
{
    response_data=replysaldo->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString saldo;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       saldo+=QString::number(json_obj["luottoraja"].toInt())+"€ luottorajaa jäljellä Asiakas: "+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r"; //Määritetään QString saldon sisältämä tieto.

    }
    emit sendSaldo(saldo); //Lähetetään tietokannasta saatu data saldo-ikkunaan.
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
    emit stopTimer();
    emit stopTimerMain();
    connect(objTimer, SIGNAL(timeout()), objConSaldo, SLOT(timerSlot()));
    connect(objConSaldo, SIGNAL(closeWindow()), this, SLOT(slotCloseSaldo()));
    objTimer->start(1000);
    this->close();

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

            getManager1 = new QNetworkAccessManager(this);
            connect(getManager1, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLuottorajaSlot(QNetworkReply*)));
            replysaldo = getManager1->get(request);


    }
    else if (response_dataKorttityyppi == "yhdistelma" && tyyppiValinta == "credit") {
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
    else if (response_dataKorttityyppi == "yhdistelma" && tyyppiValinta == "debit"){
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
}

void consoleMain::getAsiakastiedot(const QString &asiakastiedot) //Vastaanottaa consolePasswordista tulevan tiedon ja näyttää sen tekstikentässä.
{
    asiakkaanTiedot = asiakastiedot;;
    ui->lineEditAsiakastiedot->setText(asiakkaanTiedot);
}

void consoleMain::getYhdistelmaSlotAsiakastiedot(const QString &asiakkaantiedot) //Vastaanottaa yhdistelmäkortin tapauksessa asiakkaan tiedot ja näyttää ne tekstikentässä.
{
    counter = 0;
    asiakkaanTiedot=asiakkaantiedot;
    ui->lineEditAsiakastiedot->setText(asiakkaanTiedot);
}

void consoleMain::on_btnKirjauduUlos_clicked()
{
    this->close();
    counter = 0;
    emit stopTimer();
    emit stopTimerMain();
    disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferDebit(double)));
    disconnect(objConNosto, SIGNAL(signalSumma(double)), this, SLOT(transferCredit(double)));
}
void consoleMain::timer30Slot()
{
    qDebug() << counter;
    counter++;
    if(counter == 30){
        counter = 0;
        emit stopTimer();
        emit stopTimerMain();
        emit closeMainWindow();
    }
}
