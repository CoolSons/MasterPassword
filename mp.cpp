#include "mp.h"
#include "ui_mp.h"
#include "mainwindow.h"
mp::mp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mp)
{
    ui->setupUi(this);
}

mp::~mp()
{
    delete ui;
}

void mp::on_pushButton_clicked()
{
    MainWindow w;
    w.show();

}
