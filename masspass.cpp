#include "masspass.h"
#include "ui_masspass.h"
#include <QPushButton>
MassPass::MassPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MassPass)
{
    ui->setupUi(this);

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
    emit OkClicked();
}

void MassPass::on_pushButton_2_clicked()
{
    emit CancelClicked();
}

void MassPass::on_pushButton_3_clicked()
{
    emit showClicked();
}
