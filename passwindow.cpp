#include "passwindow.h"
#include "ui_passwindow.h"
#include "mainwindow.h"
PassWindow::PassWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassWindow)
{
    ui->setupUi(this);

    }

PassWindow::~PassWindow()
{
    delete ui;
}

void PassWindow::on_pushButton_clicked()
{

    MainWindow w;
    w.show();

}

void PassWindow::on_pushButton_clicked(bool checked)
{

}
