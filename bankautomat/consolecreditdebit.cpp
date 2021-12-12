#include "consolecreditdebit.h"
#include "ui_consolecreditdebit.h"

consoleCreditDebit::consoleCreditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleCreditDebit)
{
    ui->setupUi(this);
    objConMain = new consoleMain;
    objConSaldo = new consoleSaldo;
    objTimerit = new QTimer;
    connect(this,SIGNAL(signalID(const QString &)), objConMain,SLOT(getYhdistelmaIDSlot(const QString &)));
    counter = 0;

    connect(objConMain, SIGNAL(startTimerMain()), this, SLOT(startTimerSlot()));
    connect(objConMain,SIGNAL(stopTimerMain()), this, SLOT(slotStopTimerMain()));
    connect(objTimerit, SIGNAL(timeout()), objConMain, SLOT(timer30Slot()));
    connect(objConMain, SIGNAL(closeMainWindow()), this, SLOT(slotCloseConsoleMain()));



}

consoleCreditDebit::~consoleCreditDebit()
{
    delete ui;
    delete objConMain;
    objConMain = nullptr;
    delete objTimerit;
    objTimerit = nullptr;
    delete objConSaldo;
    objConSaldo = nullptr;
    delete getManager;
    getManager = nullptr;
    delete asiakastiedotManager;
    asiakastiedotManager = nullptr;
    delete getManager1;
    getManager1 = nullptr;
}

void consoleCreditDebit::on_btnDebit_clicked()  //lähettää kortin id:n, tyyppivalinnan ja pysäyttää ikkunan sulkevan timerin, sekä hakee asiakastiedot
{
    qDebug() <<"debit button id" <<korttiID;
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
        connect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));
        valinta = "debit";
        emit signalID(korttiID);
        emit signalValinta(valinta);
        emit stopTimercredeb();



        disconnect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));

        QString site_urlAsiakastiedot="http://localhost:3000/asiakastiedot/"+korttiID; //Haetaan tietokannasta asiakastiedot kortin ID:n perusteella.
        QString credentialsAsiakastiedot="1234:4321";
        QNetworkRequest requestAsiakastiedot((site_urlAsiakastiedot));
        requestAsiakastiedot.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray dataAsiakastiedot = credentialsAsiakastiedot.toLocal8Bit().toBase64();
        QString headerDataAsiakastiedot = "Basic " + dataAsiakastiedot;
        requestAsiakastiedot.setRawHeader( "Authorization", headerDataAsiakastiedot.toLocal8Bit() );

        asiakastiedotManager = new QNetworkAccessManager(this);
        connect(asiakastiedotManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAsiakastiedotSlot(QNetworkReply*)));
        replyAsiakastiedot = asiakastiedotManager->get(requestAsiakastiedot);

    objConMain->show();
    counter = 0;
    objTimerit->start(1000);
    this->hide();

}

void consoleCreditDebit::getSaldoSlot(QNetworkReply*) //hakee ja lähettää asiakkaan tiedot saldo ikkunaan
{

        response_data=replysaldo->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();
        QString saldoYhdistelma;
        foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           saldoYhdistelma+=QString::number(json_obj["saldo"].toInt())+"€ Asiakas: "+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r"; //Määritetään QString saldon sisältämä tieto.
            qDebug()<<"saldoyhdistelma:"<<saldoYhdistelma;
        }
        connect(this, SIGNAL(sendSaldo(const QString &)), objConMain,SLOT(getYhdistelmaSlotSaldo(const QString &)));
        emit sendSaldo(saldoYhdistelma); //Lähetetään tietokannasta saatu data saldo-ikkunaan.
        //replysaldo->deleteLater();

}

void consoleCreditDebit::on_btnCredit_clicked()  //lähettää kortin id:n, tyyppivalinnan ja pysäyttää ikkunan sulkevan timerin, sekä hakee asiakastiedot
{
    QString site_url1="http://localhost:3000/luottoraja/"+korttiID; //Haetaan asiakkaan luottoraja tietokannasta kortin id:n perusteella.
        QString credentials1="1234:4321";
        QNetworkRequest request1((site_url1));
        request1.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray data1 = credentials1.toLocal8Bit().toBase64();
        QString headerData1 = "Basic " + data1;
        request1.setRawHeader( "Authorization", headerData1.toLocal8Bit() );

        getManager1 = new QNetworkAccessManager(this);
        connect(getManager1, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLuottorajaSlot(QNetworkReply*)));
        replyLuottoraja = getManager1->get(request1);
        connect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));
        valinta = "credit";
        emit signalID(korttiID);
        emit signalValinta(valinta);
        emit stopTimercredeb();



        disconnect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));

        QString site_urlAsiakastiedot="http://localhost:3000/asiakastiedot/"+korttiID; //Haetaan tietokannasta asiakastiedot kortin ID:n perusteella.
        QString credentialsAsiakastiedot="1234:4321";
        QNetworkRequest requestAsiakastiedot((site_urlAsiakastiedot));
        requestAsiakastiedot.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray dataAsiakastiedot = credentialsAsiakastiedot.toLocal8Bit().toBase64();
        QString headerDataAsiakastiedot = "Basic " + dataAsiakastiedot;
        requestAsiakastiedot.setRawHeader( "Authorization", headerDataAsiakastiedot.toLocal8Bit() );

        asiakastiedotManager = new QNetworkAccessManager(this);
        connect(asiakastiedotManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAsiakastiedotSlot(QNetworkReply*)));
        replyAsiakastiedot = asiakastiedotManager->get(requestAsiakastiedot);

    objConMain->show();
    counter = 0;
    objTimerit->start(1000);
    this->hide();
}

void consoleCreditDebit::getLuottorajaSlot(QNetworkReply*) // lähettää luottorajan seuraavaan ikkunaan
{
    response_data1=replyLuottoraja->readAll();
    QJsonDocument json_doc1 = QJsonDocument::fromJson(response_data1);
    QJsonArray json_array1 = json_doc1.array();
    QString luottorajaYhdistelma;
    foreach (const QJsonValue &value, json_array1) {
       QJsonObject json_obj1 = value.toObject();
      luottorajaYhdistelma+=QString::number(json_obj1["luottoraja"].toInt())+"€ luottoraja Asiakas: "+json_obj1["etunimi_asiakas"].toString()+" "+json_obj1["sukunimi_asiakas"].toString()+"\r";
    qDebug()<<"Luottorajayhdistelma:"<<luottorajaYhdistelma;
    }
    connect(this, SIGNAL(sendSaldo(const QString &)), objConMain,SLOT(getYhdistelmaSlotLuottoraja(const QString &)));
    emit sendSaldo(luottorajaYhdistelma);

}

void consoleCreditDebit::slotCardID(const QString &id) // vastaanottaa kortin id:n
{
    korttiID = id;
    qDebug() << id;
}

void consoleCreditDebit::getAsiakastiedotSlot(QNetworkReply *replyAsiakastiedot)
{
    response_dataAsiakastiedot=replyAsiakastiedot->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_dataAsiakastiedot);
    QJsonArray json_array = json_doc.array();
    QString asiakkaantiedot;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       asiakkaantiedot+=QString::fromLatin1(" Tervetuloa ")+json_obj["etunimi_asiakas"].toString()+" "+json_obj["sukunimi_asiakas"].toString()+"\r";
    connect(this,SIGNAL(sendAsiakastiedot(const QString &)), objConMain,SLOT(getYhdistelmaSlotAsiakastiedot(const QString &)));
}
    emit sendAsiakastiedot(asiakkaantiedot); //Lähetetään asiakastiedot consoleMainiin, jossa ne tulostuvat tekstikenttään.

}

void consoleCreditDebit::timerSlot() // counter ajastin ikkunalle
{
    qDebug() << counter;
    counter++;
    if(counter == 10) {
        counter = 0;
        emit stopTimercredeb();
        emit closeWindow();
    }
}

void consoleCreditDebit::startTimerSlot()
{
    objTimerit->start(1000);
}

void consoleCreditDebit::slotStopTimerMain()
{
    objTimerit->stop();
}

void consoleCreditDebit::slotCloseConsoleMain()
{
    objConMain->close();
}
void consoleCreditDebit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        objTimerit->stop();
        emit stopTimer();
        this->close();
        counter = 0;
    }
}
