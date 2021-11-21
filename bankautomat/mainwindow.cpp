#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objConPass = new consolePassword;
    objConMain = new consoleMain;
    connect(this, SIGNAL(signalKirjaudu()), this, SLOT(loginSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objConPass;
    objConPass = nullptr;

    delete objConMain;
    objConMain = nullptr;
}


void MainWindow::on_btnKirjaudu_clicked()
{
    emit signalKirjaudu();
}

void MainWindow::loginSlot()
{
    objConPass->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        this->close();
    }
}

void MainWindow::on_btnZero_clicked()
{
    ui->lineEditID->insert("0");
}


void MainWindow::on_btnOne_clicked()
{
    ui->lineEditID->insert("1");
}


void MainWindow::on_btnTwo_clicked()
{
    ui->lineEditID->insert("2");
}


void MainWindow::on_btnThree_clicked()
{
    ui->lineEditID->insert("3");
}


void MainWindow::on_btnFour_clicked()
{
    ui->lineEditID->insert("4");
}


void MainWindow::on_btnFive_clicked()
{
    ui->lineEditID->insert("5");
}


void MainWindow::on_btnSix_clicked()
{
    ui->lineEditID->insert("6");
}


void MainWindow::on_btnSeven_clicked()
{
    ui->lineEditID->insert("7");
}


void MainWindow::on_btnEight_clicked()
{
    ui->lineEditID->insert("8");
}


void MainWindow::on_btnNine_clicked()
{
    ui->lineEditID->insert("9");
}


void MainWindow::on_btnReset_clicked()
{
    ui->lineEditID->clear();
}


void MainWindow::on_btnOK_clicked()
{
    QJsonObject json;
    QString idkortti = ui->lineEditID->text();
    QString site_url="http://localhost:3000/login/"+idkortti;
    QString credentials="1234:4321";
    idkayttis = idkortti.toInt();
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    checkCardManager = new QNetworkAccessManager(this);
    connect(checkCardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(checkCardSlot(QNetworkReply*)));
    reply = checkCardManager->get(request);
}

void MainWindow::checkCardSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
      qDebug() << response_data;

      if(response_data == "true") {
          qDebug() << "Oikea tunnus ...avaa form";
          connect(this, SIGNAL(signalID(int)), objConPass, SLOT(connectingSlot(int)));
          emit signalID(idkayttis);
          objConPass->show();
      }
}




