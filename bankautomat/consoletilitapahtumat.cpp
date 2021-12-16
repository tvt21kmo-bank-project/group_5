#include "consoletilitapahtumat.h"
#include "ui_consoletilitapahtumat.h"

consoleTilitapahtumat::consoleTilitapahtumat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleTilitapahtumat)
{
    ui->setupUi(this);
    counter = 0;
    listarajaus = 0;
}

consoleTilitapahtumat::~consoleTilitapahtumat()
{
    delete ui;

   }

void consoleTilitapahtumat::getDataSlot(const QString &tilitapahtumat)
{
    tapahtumat = tilitapahtumat; //Käytössä koko oliossa
    //qDebug()<<"Asiakkaan tilitapahtumat" << tapahtumat;
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
    counter = 0;
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
    counter = 0;
    if(listarajaus > 0) {
        listarajaus -= 10;
    } else {
        listarajaus = 0;
    }
    QJsonObject objJson;
    objJson.insert("id",korttiID);
    objJson.insert("alkuraja",listarajaus);

    QString site_url="http://localhost:3000/tilitapahtumat/list_tilitapahtumat";
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(listTapahtumatSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(objJson).toJson());
}

void consoleTilitapahtumat::listTapahtumatSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tapahtumat;
    foreach (const QJsonValue &value, json_array) {
       QJsonObject json_obj = value.toObject();
       tapahtumat+=QString::number(json_obj["summa"].toInt())+"€"+","+json_obj["tapahtuma"].toString()+","+json_obj["date"].toString()+","+json_obj["etunimi_asiakas"].toString()+","+json_obj["sukunimi_asiakas"].toString()+","+"\r";
       QString omistaja;
       omistaja = tapahtumat.section(',',3,4); //pilkotaan merkkijonosta omistaja
       omistaja.replace(QString(","), QString(" ")); //vaihdetaan pilkut välilyönneiksi
       tapahtumat.replace(QString (","), QString(" "));
       tapahtumat.remove(omistaja);
       ui->textEditTapahtumat->setText(tapahtumat);
    }
    if (response_data == "[]") {
        listarajaus -= 10;
    }
    qDebug() << "listan rajaus" << listarajaus;
    disconnect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(listTapahtumatSlot(QNetworkReply*)));

    reply->deleteLater();
    postManager->deleteLater();
}



void consoleTilitapahtumat::on_btnNext10_clicked()
{
    counter = 0;
    if(listarajaus >= 0) {
        listarajaus += 10;
    } else {
        listarajaus = 0;
    }
    QJsonObject objJson;
    objJson.insert("id",korttiID);
    objJson.insert("alkuraja",listarajaus);

    QString site_url="http://localhost:3000/tilitapahtumat/list_tilitapahtumat";
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(listTapahtumatSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(objJson).toJson());
}

void consoleTilitapahtumat::slotKorttiId(const QString &kortti)
{
    korttiID = kortti;
    qDebug() << "kortinID " << korttiID;
}

