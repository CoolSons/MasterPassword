#include "masspass.h"
#include "ui_masspass.h"
#include <QPushButton>
MassPass::MassPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MassPass)
{
    ui->setupUi(this);

}



MassPass::~MassPass()
{
    delete ui;

}

void MassPass::on_pushButton_clicked()
{
    emit OkClicked();
}
