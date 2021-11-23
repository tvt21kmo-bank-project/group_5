#include "creditdebit.h"
#include "ui_creditdebit.h"

creditDebit::creditDebit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creditDebit)
{
    ui->setupUi(this);
}

creditDebit::~creditDebit()
{
    delete ui;
}

void creditDebit::on_btnCredit_clicked()
{

}


void creditDebit::on_btnDebit_clicked()
{

}

