#include "consolecreditdebit.h"
#include "ui_consolecreditdebit.h"

consoleCreditDebit::consoleCreditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleCreditDebit)
{
    ui->setupUi(this);
}

consoleCreditDebit::~consoleCreditDebit()
{
    delete ui;
}

void consoleCreditDebit::on_btnDebit_clicked()
{

}


void consoleCreditDebit::on_btnCredit_clicked()
{

}

void consoleCreditDebit::slotCardID(const QString &id)
{
    korttiID = id;
    qDebug() << id;
}


