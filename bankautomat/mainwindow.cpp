#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objConPass = new consolePassword;
    objConMain = new consoleMain;
    objTimer = new QTimer;
    objTekstiTimer = new QTimer;
    connect(this, SIGNAL(signalLogin(const QString &)), objConPass, SLOT(connectingSlot(const QString &)));
    connect(objConPass, SIGNAL(closeWindow()), this, SLOT(closeConsolePassSlot()));
    connect(objConPass,SIGNAL(stopTimerPass()), this, SLOT(stopTimerSlot()));
    connect(objConPass, SIGNAL(sendTeksti(const QString &)), this, SLOT(slotTekstiIlmoitus(const QString &)));
    connect(objTimer, SIGNAL(timeout()), objConPass, SLOT(timerSlot()));
    connect(objTekstiTimer, SIGNAL(timeout()), this, SLOT(pyyhiTeksti()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objConPass;
    objConPass = nullptr;

    delete objConMain;
    objConMain = nullptr;

    delete objTimer;
    objTimer = nullptr;

    delete objTekstiTimer;
    objTekstiTimer = nullptr;

    delete checkCardManager;
    checkCardManager = nullptr;

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        this->close();
        objTimer->stop();
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


void MainWindow::on_btnOK_clicked() // hakee tietokannasta kortin id:n
{

    QJsonObject json;
    QString idkortti = ui->lineEditID->text();
    ui->lineEditID->clear();
    QString site_url="http://localhost:3000/korttilukittu/"+idkortti;
    QString credentials="1234:4321";
    IDcard = idkortti;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );

    checkCardManager = new QNetworkAccessManager(this);
    connect(checkCardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(checkCardSlot(QNetworkReply*)));
    reply = checkCardManager->get(request);
    objTimer->start(1000); //password kentän timerin aloitus

}

void MainWindow::closeConsolePassSlot()
{
    objConPass->close();
}

void MainWindow::stopTimerSlot()
{
    objTimer->stop();
}

void MainWindow::startTimerSlot()
{
    objTimer->start(1000);
}

void MainWindow::slotTekstiIlmoitus(const QString &arg)
{
    ui->lineEditKortinTila->setText(arg);
    objTekstiTimer->start(3000);
}

void MainWindow::pyyhiTeksti()
{
    ui->lineEditKortinTila->clear();
    objTekstiTimer->stop();
}

void MainWindow::checkCardSlot(QNetworkReply *reply)   //tarkistaa kortin id:n
{
    QByteArray response_data=reply->readAll();
      qDebug() << response_data;

    if(response_data == "3") {
        ui->lineEditKortinTila->setText("Kortti lukittu.");
        objTimer->stop();
    } else if(response_data == "0" or response_data == "1" or response_data == "2") {
          qDebug() << "Oikea tunnus ...avaa form";
          strCounterPIN = response_data;
          counterPIN = strCounterPIN.toInt();
          connect(this, SIGNAL(signalKortinLukitus(int)), objConPass, SLOT(slotPinLukitus(int)));
          ui->lineEditKortinTila->setText("Oikea tunnus.");
          emit signalLogin(IDcard);
          emit signalKortinLukitus(counterPIN);
          disconnect(this, SIGNAL(signalKortinLukitus(int)), objConPass, SLOT(slotPinLukitus(int)));
          ui->lineEditID->clear(); //Tyhjennetään ID-kenttä ja avataan PIN-kenttä
          objConPass->show();
    }
     else if(response_data == "Does not exist") {
          ui->lineEditKortinTila->setText("Korttia ei löydy.");
          objTimer->stop(); //pysäytetään timeri jos väärä korttinumero
    } else {
        qDebug() << "Virheellinen kortti";
        objTimer->stop();
    }
}




