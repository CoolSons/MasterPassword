#define _GLIBCXX_USE_CXX11_ABI 0
#include "masspass.h"
#include "ui_masspass.h"
#include <QPushButton>
#include "sha512.h"
#include <iostream>
#include <string>
#include <algorithm>

MassPass::MassPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MassPass)
{
    ui->setupUi(this);
    SHA256* yourInstanceName = new SHA256();
    ui->lineEdit->setText(QString::fromStdString(yourInstanceName->hash("ABCDEFGHIJKLMN")));
    QString a = ui->lineEdit->text();

}
int MassPass::GetX()
{
    return ui->horizontalLayout->geometry().width();
}
int MassPass::GetY()
{
    return ui->horizontalLayout->geometry().height();
}
QRect MassPass::GetGeo()
{
    return ui->horizontalLayout->geometry();
}


MassPass::~MassPass()
{
    delete ui;

}

void MassPass::on_pushButton_clicked()
{
    //if parol is pravilniy
    emit OkClicked();
}

void MassPass::on_pushButton_2_clicked()
{
    emit CancelClicked();
}


