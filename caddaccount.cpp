#include "caddaccount.h"
#include "ui_caddaccount.h"
#include <QDebug>
#include "cmodel.h"
MainWindow *mainwindow = MainWindow::GetMainWindow();
CAddAccount::CAddAccount(QWidget *parent) : QDialog(parent),   ui(new Ui::CAddAccount)
{
    ui->setupUi(this);
}

CAddAccount::~CAddAccount()
{
    delete ui;
}

void CAddAccount::on_buttonBox_clicked(QAbstractButton *button) // правильно что через новую модель?
{
    //CModel::GetModel()->AddAccountToSite(,ui->label->text(),ui->label_2->text() );

    //qWarning() << CModel::GetModel()->GetDoc();
   }

