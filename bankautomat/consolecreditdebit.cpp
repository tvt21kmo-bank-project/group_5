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
    connect(objConMain, SIGNAL(stopTimerMain()), this, SLOT(slotStopTimerMain()));
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
}

void consoleCreditDebit::on_btnDebit_clicked()  //lähettää kortin id:n, tyyppivalinnan ja pysäyttää ikkunan sulkevan timerin, sekä hakee asiakastiedot
{
    qDebug() <<"debit button id" <<korttiID;
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
    connect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));
    valinta = "debit";
    emit signalID(korttiID);
    emit signalValinta(valinta);
    emit stopTimercredeb();
    disconnect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));

    objConMain->show();
    counter = 0;
    objTimerit->start(1000);
    this->hide();
}

void consoleCreditDebit::on_btnCredit_clicked()  //lähettää kortin id:n, tyyppivalinnan ja pysäyttää ikkunan sulkevan timerin, sekä hakee asiakastiedot
{
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
    connect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));
    valinta = "credit";
    emit signalID(korttiID);
    emit signalValinta(valinta);
    emit stopTimercredeb();
    disconnect(this,SIGNAL(signalValinta(const QString &)),objConMain,SLOT(slotTyyppiValinta(const QString &)));

    objConMain->show();
    counter = 0;
    objTimerit->start(1000);
    this->hide();
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

    replyAsiakastiedot->deleteLater();
    asiakastiedotManager->deleteLater();

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
