#include "consolepassword.h"
#include "ui_consolepassword.h"

consolePassword::consolePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consolePassword)
{
    ui->setupUi(this);
    objConMain = new consoleMain;
    connect(this, SIGNAL(signalKirjaudu()), this, SLOT(loginSlot()));
}

consolePassword::~consolePassword()
{
    delete ui;
    delete objConMain;
    objConMain = nullptr;
    delete loginManager;
    loginManager = nullptr;
}

void consolePassword::connectingSlot(const QString &idcard)
{
    cardID = idcard;
    qDebug() << "asiakkaan ID" << cardID;
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
        objConMain->showFullScreen();
     } else {
         qDebug() << "Väärä PIN";
     }
     reply->deleteLater();
}

