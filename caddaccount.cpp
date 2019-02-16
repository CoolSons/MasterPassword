#include "caddaccount.h"
#include "ui_caddaccount.h"
#include <QDebug>                           //Это норма?
#include "mainwindow.h"
CAddAccount::CAddAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddAccount)
{
    ui->setupUi(this);
}

CAddAccount::~CAddAccount()
{
    delete ui;
}

void CAddAccount::on_buttonBox_clicked(QAbstractButton *button) // правильно что через новую модель?
{
    login = ui->label->text();
    password = ui->label_2->text();

   }

