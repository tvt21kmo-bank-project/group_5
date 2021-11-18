#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signalKirjaudu()), this, SLOT(loginSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objConPass;
    objConPass = nullptr;
}


void MainWindow::on_btnKirjaudu_clicked()
{
    emit signalKirjaudu();
}

void MainWindow::loginSlot()
{
    objConPass->show();
    //this->close();
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

}

