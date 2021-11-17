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
    delete objConMain;
    objConMain = nullptr;
}


void MainWindow::on_btnKirjaudu_clicked()
{
    emit signalKirjaudu();
    //objConMain->show();
}

void MainWindow::loginSlot()
{
    objConMain->show();
    //this->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        this->close();
    }
}

