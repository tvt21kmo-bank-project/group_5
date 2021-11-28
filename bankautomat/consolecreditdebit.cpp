#include "consolecreditdebit.h"
#include "ui_consolecreditdebit.h"

consoleCreditDebit::consoleCreditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleCreditDebit)
{
    ui->setupUi(this);
    objConMain = new consoleMain;
    objConSaldo = new consoleSaldo;
    connect(this,SIGNAL(signalID(const QString &)), objConMain,SLOT(getyhdistelmaIDSlot(const QString &)));


}

consoleCreditDebit::~consoleCreditDebit()
{
    delete ui;
    delete objConMain;
    objConMain = nullptr;
}

void consoleCreditDebit::on_btnDebit_clicked()
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
    this->close();

}

void consoleCreditDebit::getSaldoSlot(QNetworkReply*)
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

void consoleCreditDebit::on_btnCredit_clicked()
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
    this->close();
}

void consoleCreditDebit::getLuottorajaSlot(QNetworkReply*)
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

void consoleCreditDebit::slotCardID(const QString &id)
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

