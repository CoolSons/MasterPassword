#include "caddaccount.h"
#include "ui_caddaccount.h"
#include <QDebug>
#include "cmodel.h"
CAddAccount::CAddAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAddAccount)
{
    ui->setupUi(this);
    ui->textEdit->setFocus();
    ui->textEdit->selectAll();

}

CAddAccount::~CAddAccount()
{
    delete ui;
}

void CAddAccount::on_buttonBox_clicked(QAbstractButton *button) // правильно что через новую модель?
{

    if( button->text() == "OK")//"Cancel" "OK"
    {
        OkClicked = true;
    }
    else
    {
        OkClicked = false;
    }

}

QString CAddAccount::login()
{
    return ui->textEdit->toPlainText();
}

QString CAddAccount::password()
{
   return ui->textEdit_2->toPlainText();
}





