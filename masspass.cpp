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
    return ui->verticalLayout_2->geometry().width();
}
int MassPass::GetY()
{
    return ui->verticalLayout_2->geometry().height();
}
QRect MassPass::GetGeo()
{
    return ui->verticalLayout_2->geometry();
}


MassPass::~MassPass()
{
    delete ui;

}

void MassPass::on_pushButton_clicked()
{
    emit OkClicked();
}
