#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//1. сделать вcе по нормальному через this а не mainDoc,
//2. расставить статик и конст,
//3. нормально функции переименовать, написать к ним описание
//4. лишнее удалить,
//5. вынести в ашник по разделам,
//6. ограничить по индексам где надо,
//7. сделать по ссылкам чтобы летало вася
//8. проверить конструкторы,
//9. нормально назвать виджеты,
//10. разнести их тоже по разным ашникам

#include <QMainWindow>
#include <QtCore>
#include <cstdio>
#include <QString>
#include <QFileDialog>
#include <QStandardItem>
#include <QDebug>
#include <QTableWidget>
#include <QListWidgetItem>


QJsonDocument GetDocFromFilename(QString &filename);
QJsonDocument GetDocFromFile(QFile &file);
QJsonDocument StringToDocument(const QString& data);
QJsonObject StringToObject(const QString& in);
QString ObjectToString(const QJsonObject &_jsObj);
QJsonDocument ObjectToDocument(const QJsonObject& obj);
QString DocumentToString(const QJsonDocument &_jsObj);
QJsonObject DocumentToObject(const QJsonDocument &doc);
QJsonDocument ObjectToDocument(const QJsonObject& obj);

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT
    QJsonDocument   doc;
    QJsonArray arr;
    QJsonParseError  docError;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_listWidget_pressed(const QModelIndex &index);


    void on_QLineedit_returnPressed();

    void on_ButtonAddSite_clicked();

    void on_ButtonDeleteSite_clicked();

    void on_ButtonAddAcc_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
};





class CModel
{
    QJsonObject mainObject;
    QJsonDocument mainDoc;
    QString mainString;

public:

    void SetObj(const QJsonObject &aaaa)
    {
        mainObject = aaaa;
    }
    void SetStr(const QString &aaaa)
    {
        mainString = aaaa;
    }
    void SetDoc(const QJsonDocument &aaaa)
    {
        mainDoc = aaaa;
    }
    const QJsonObject GetObj()
    {
        return mainObject;
    }
    const QJsonDocument GetDoc()
    {
        return mainDoc;
    }
    const QString GetStr()
    {
        return mainString;
    }

    const QJsonArray GetArrayOfUrls() //returns ("Vk.com"), ("ok.ru")... |
    {
        QStringList list = {};
        for(int i = 0; i < mainDoc.object().value("array Of URLs").toArray().size(); i++)
        {
            list.append(mainDoc.object().value("array Of URLs").toArray().at(i).toObject().keys());
        }
        return QJsonArray::fromStringList(list);
    }


    void SetModel(const QJsonDocument &doc)
    {
        SetDoc(doc);
        SetObj(DocumentToObject(doc));
        SetStr(DocumentToString(doc));
    }
    void SetModel(const QJsonObject &obj)
    {
        SetObj(obj);
        SetStr(ObjectToString(obj));
        SetDoc(ObjectToDocument(obj));
    }
    void SetModel(const QString &str)
    {
        SetObj(StringToObject(str));
        SetStr(str);
        SetDoc(StringToDocument(str));
    }
    void SetModel(CModel &mod)
    {
        this->SetObj(mod.GetObj());
        this->SetStr(mod.GetStr());
        this->SetDoc(mod.GetDoc());
    }


    CModel GetModel() //returns this model |
    {
        return *this;
    }





   const QJsonArray GetUrlsArr()
    {
        return this->GetDoc().object().value("array Of URLs").toArray();

    }



    QJsonArray GetAccountsOfSiteByIndex(const int &index)// сделать через exception? |
    {
        QJsonArray urls = this->GetArrayOfUrls();

        if(index < 0 || urls.size() == 0 || index >= urls.size())
        {
            qWarning() << "in GetAccountsOfSiteByIndex(index) error index" << endl;
            //надо чтото еще сделать(закрыть прогу)
        }

        return mainDoc.object().value("array Of URLs").toArray().at(index).toObject().value(urls[index].toString()).toArray();

    }



    QString GetLogin(const QJsonObject &account)
    {
        return  account.keys().join("");
    }

    QString GetPassword(const QJsonObject &account)
    {
        return account.value(GetLogin(account)).toString();
    }

    void DeleteSiteByIndex(const int i) //удалить из setAccountsToTable
    {
        if(!mainDoc.object().value("array Of URLs").toArray().isEmpty())
        {
          QJsonArray demo =  this->GetUrlsArr();// новый массив демо норм работает
          demo.removeAt(i);
          QJsonObject main;
          main.toVariantMap();
          main["array Of URLs"] = demo;

          this->SetModel(main);
        }
    }


    void addSiteToModel(const QString &url, const QJsonArray &arrOfAccounts)//Переделатть с копией МОДЕЛИ
    {
        QJsonObject site;
        site.toVariantMap();
        site[url] = arrOfAccounts;
        QJsonArray test = mainObject.value("array Of URLs").toArray();
        test.append(site);
        QJsonObject main2;
        main2.toVariantMap();
        main2["array Of URLs"] = test;

        SetObj(main2);
        QJsonDocument d(main2);
        SetDoc(d);
        QString s = ObjectToString(main2);
        SetStr(s);

    }

    void SaveModelToFile(const QJsonDocument &document, const QString &fileName)//сделать абстрактные функции
    {

        QFile jsonFile(fileName);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(document.toJson());
        jsonFile.close();
    }


    CModel();
    CModel(const QJsonObject &obj)
    {
        SetObj(obj);
        QJsonDocument d(obj);
        SetDoc(d);
        QString s = ObjectToString(obj);
        SetStr(s);
    }
    CModel(const QJsonDocument &doc)
    {
        QJsonObject obj = DocumentToObject(doc);
        SetObj(obj);
        SetDoc(doc);
        QString s = DocumentToString(doc);
        SetStr(s);
    }
    CModel(const QString &str)
    {
        QJsonObject obj = StringToObject(str);
        SetObj(obj);
        QJsonDocument doc = StringToDocument(str);
        SetDoc(doc);
        SetStr(str);
    }

    CModel(QFile &file)
    {
        QJsonDocument doc = GetDocFromFile(file);
        SetDoc(doc);
        QJsonObject obj = DocumentToObject(doc);
        SetObj(obj);
        QString str = DocumentToString(doc);
        SetStr(str);
    }

    ~CModel()
    {

    }
};



#endif // MAINWINDOW_H
