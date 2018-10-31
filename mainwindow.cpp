
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(clicked(bool)), )
}


QJsonDocument GetDocFromFile()

{

    QFile file;
    QString globPath= QFileDialog::getOpenFileName(nullptr,"","D:\\Users\Root\Desktop\JsonBase","*.json");  // - чтобы спрашивать файл
    // globPath = "D:\\Users\Root\Desktop\JsonBase.json"; //   D:\Users\Root\Desktop\JsonBase.json
    file.setFileName(globPath);
    QJsonDocument docc;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly|QFile::Text)))
    {
        QJsonParseError docError;
        docc = QJsonDocument::fromJson(file.readAll(), &docError);
        qWarning() << "file is read"   << endl;
    }
    file.close();
    return docc;
}




QJsonArray GetAccounstArr(QJsonDocument &doc, QString url, QString type) //type means that it's site, not app or something
{
    // QString log = QJsonValue(doc.object().value("sites").toArray().at(0).toObject().value("accounts").toArray().at(0).toObject().value("Login")).toString();
    int index = 0;
    for(int i =0; i<doc.object().value(type).toArray().size(); i++)
    {
        if(doc.object().value("sites").toArray().at(i).toObject().value("url").toString() == url)
            index = i;
    }
    return doc.object().value(type).toArray().at(index).toObject().value("accounts").toArray();
}



void SetAllLogAndPasToTable(QJsonDocument &doc, QString type, QTableWidget &widget)
{
    widget.setColumnCount(2);

    QTableWidgetItem *login = new QTableWidgetItem();
    login->setText("Login");
    widget.setHorizontalHeaderItem(0, login);
    QTableWidgetItem *password = new QTableWidgetItem();
    password->setText("Password");
    widget.setHorizontalHeaderItem(1, password);


    QString login1;
    QString password1;
    for(int i = 0; i < doc.object().value(type).toArray().size(); i++)
    {
        for(int j = 0; j <doc.object().value(type).toArray().at(i).toObject().value("accounts").toArray().size(); j++)
        {
            widget.insertRow(j);
            login1 = doc.object().value(type).toArray().at(i).toObject().value("accounts").toArray().at(j).toObject().value("Login").toString(); // aaaa1
            password1 = doc.object().value(type).toArray().at(i).toObject().value("accounts").toArray().at(j).toObject().value("password").toString(); // ppppp
            widget.setItem(j, 0, new QTableWidgetItem(login1));
            widget.setItem(j, 1, new QTableWidgetItem(password1));
        }
    }

}


void SetSiteLogAndPasToTable(QJsonDocument &doc, QString type, QTableWidget &widget, QString site)
{
    widget.setColumnCount(2);

    QTableWidgetItem *login = new QTableWidgetItem();
    login->setText("Login");
    widget.setHorizontalHeaderItem(0, login);
    QTableWidgetItem *password = new QTableWidgetItem();
    password->setText("Password");
    widget.setHorizontalHeaderItem(1, password);


    QString login1;
    QString password1;
    for(int i = 0; i < doc.object().value(type).toArray().size(); i++)
    {
        for(int j = 0; j <doc.object().value(type).toArray().at(i).toObject().value("accounts").toArray().size(); j++)
        {

            if(doc.object().value(type).toArray().at(i).toObject().value("url").toString() == site)
            {
                widget.insertRow(j);
                login1 = doc.object().value(type).toArray().at(i).toObject().value("accounts").toArray().at(j).toObject().value("Login").toString(); // aaaa1
                password1 = doc.object().value(type).toArray().at(i).toObject().value("accounts").toArray().at(j).toObject().value("password").toString(); // ppppp
                widget.setItem(j, 0, new QTableWidgetItem(login1));
                widget.setItem(j, 1, new QTableWidgetItem(password1));
            }
        }
    }

}

void AddSiteToDocument(QJsonDocument &doc, QJsonObject &site)
{
    QJsonObject acc;
    acc.insert("Login", "yandexlogin");
    acc.insert("password", "yandexPass");

    QJsonArray ar;
    ar.push_back(acc);

    QJsonObject site_obj;                   // пробный объект-сайт который надо записать в док
    site_obj.insert("url", "yandex.ru");
    site_obj.insert("accounts", ar);

    //записать в документ(надо сделать)
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    doc = GetDocFromFile();
    if(docError.errorString().toInt() == QJsonParseError::NoError)
    {
        SetAllLogAndPasToTable(doc, "sites", *(ui->tableWidget_2));
        //SetSiteLogAndPasToTable(doc, "sites", *(ui->tableWidget_2), "http://vk.ru");
    }

    ui->textBrowser->setText("AAAASAN");

}

