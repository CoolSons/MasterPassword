
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "caddaccount.h"
#include "cmodel.h"
QString globPath = "D:\\document.json";
QJsonDocument doc = GetDocFromFilename(globPath);
static CModel model(doc);

void SetSettingsToTable(Ui::MainWindow *ui)
{
    ui->tableWidget->setColumnCount(2);
    QTableWidgetItem *login = new QTableWidgetItem();
    login->setText("Login");
    ui->tableWidget->setHorizontalHeaderItem(0, login);
    QTableWidgetItem *password = new QTableWidgetItem();
    password->setText("Password");
    ui->tableWidget->setHorizontalHeaderItem(1, password);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->QLineedit->selectAll();
}

void setAccountsToTable(Ui::MainWindow *ui)
{
    ui->listWidget->clear();
    QJsonArray arrOfSites = model.GetArrayOfUrls();
    for(int i =0; i<arrOfSites.size();i++)
    {
        ui->listWidget->addItem(arrOfSites[i].toString());
    }


}
void SetModelToWidget(Ui::MainWindow *ui)
{
    ui->listWidget->clear();
    ui->tableWidget->clear();
    setAccountsToTable(ui);
    //if(!model.GetArrayOfUrls().isEmpty())
         //ui->listWidget->
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetSettingsToTable(ui);
    SetModelToWidget(ui);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_pressed(const QModelIndex &index)
{

    //берем массив под индексом index "Vk.com": [ { "vkLogin": "PAssw1"},  { "vkLog2": "paasss2" }]
    // берем в цикле по очереди объекты сайтов(аккаунты)
    //для каждого аккаунта выводим логин и пароль
    ui->tableWidget->setRowCount(0);
    const int i = index.row();
    QJsonArray accNumberI = model.GetAccountsOfSiteByIndex(i);

    for(int i = 0; i< accNumberI.size(); i++)
    {
        ui->tableWidget->insertRow(0);
    }

    for(int j = 0; j < accNumberI.size(); j++)
        {

             ui->tableWidget->setItem(j, 0, new QTableWidgetItem(accNumberI[j].toObject().keys().join("")));
             ui->tableWidget->setItem(j, 1, new QTableWidgetItem(accNumberI[j].toObject().value(accNumberI[j].toObject().keys().join("")).toString()));
        }


}

void MainWindow::on_QLineedit_returnPressed()
{
    if(ui->QLineedit->text() != "")
    {
        ui->listWidget->addItem(ui->QLineedit->text());   //это кинуть в модель и лист наш сайт и пустой массив акков
        QJsonArray emptyJsonArr
        {};
       model.addSiteToModel(ui->QLineedit->text(), emptyJsonArr);
       model.SaveModelToFile(model.GetDoc(), globPath);
       ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        ui->QLineedit->clear();
   }
}



void MainWindow::on_ButtonDeleteSite_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *item, items)
    {
        int index = ui->listWidget->row(item);
        delete ui->listWidget->takeItem(index);
        model.DeleteSiteByIndex(index);
    }

     model.SaveModelToFile(model.GetDoc(), globPath);
}

void MainWindow::on_ButtonAddSite_clicked()
{
    if(ui->QLineedit->text() != "")
    {
        ui->listWidget->addItem(ui->QLineedit->text());   //это кинуть в модель и лист наш сайт и пустой массив акков
        QJsonArray emptyJsonArr
        {};
        model.addSiteToModel(ui->QLineedit->text(), emptyJsonArr);
        model.SaveModelToFile(model.GetDoc(), globPath);
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        ui->QLineedit->clear();
    }
}




void MainWindow::on_ButtonAddAcc_clicked()
{
    //только добавить в таблицу и встать туда, а потом отдельно уже переносить в таблицу
    int a = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(a);
    a++;
    ui->tableWidget->setItemSelected(ui->tableWidget->item(a-1,0), 1);

    int index=0;

    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *item, items)
    {
        index = ui->listWidget->row(item);
        CAddAccount addWindow;//исправиить насчет памяти
        addWindow.setModal(true);
        addWindow.exec();
        /*взять индекс выделеной
        добавить в модели у сайта аккаунт
        проверить рисуется ли
        если нет то нарисовать
        */
        //ui->tableWidget->setItem(0,0, new QTableWidgetItem(addWindow.GetLogin()));

    }




}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{

}
