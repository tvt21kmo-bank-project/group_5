#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // connect(this, SIGNAL(signalKirjaudu()), this, SLOT(loginSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objConPass;
    objConPass = nullptr;
    delete checkCardManager;
    checkCardManager = nullptr;
}


void MainWindow::on_btnKirjaudu_clicked()
{
    //emit signalKirjaudu();
}

void MainWindow::checkCardSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
     QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
     QJsonArray json_array = json_doc.array();
     QString idcard;
     foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        idcard+=QString::number(json_obj["idkortti"].toInt());}
     /*QString filename = "D:\\card.txt"; //save account id to file
     qDebug()<<idcard;
     QFile file(filename);
            if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
                stream << idcard;}
            file.close(); */
    if (response_data.size() > 0){
        connect(this, SIGNAL(signalLogin(const QString &)), objConPass, SIGNAL(connectingSlot(idcard)));
        emit signalLogin(idcard);
        objConPass->showFullScreen();
        qDebug()<<"ID correct -> open pin-form";}

    else {
        qDebug() << "No such card!";
    }
    reply->deleteLater();
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
    QString site_url="http://localhost:3000/kortti/"+ui->lineEditID->text();
    QString credentials="1234:4321";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray data = credentials.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader( "Authorization", headerData.toLocal8Bit() );
    checkCardManager = new QNetworkAccessManager(this);
    connect(checkCardManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(checkCardSlot(QNetworkReply*)));
    reply = checkCardManager->get(request);
}
