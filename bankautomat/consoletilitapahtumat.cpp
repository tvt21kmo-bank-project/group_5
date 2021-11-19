#include "consoletilitapahtumat.h"
#include "ui_consoletilitapahtumat.h"

consoleTilitapahtumat::consoleTilitapahtumat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consoleTilitapahtumat)
{
    ui->setupUi(this);
}

consoleTilitapahtumat::~consoleTilitapahtumat()
{
    delete ui;
}
