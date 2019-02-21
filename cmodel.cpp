#include <QtCore>
#include <cstdio>
#include <QString>
#include <QFileDialog>
#include <QStandardItem>
#include <QDebug>
#include <QTableWidget>
#include <QListWidgetItem>
#include "cmodel.h"
CModel* CModel::model = 0;
   QJsonArray CModel::GetArrayOfUrls() //returns ("Vk.com"), ("ok.ru")... |
{
    QStringList list = {};
    for(int i = 0; i < mainDoc.object().value("array Of URLs").toArray().size(); i++)
    {
        list.append(mainDoc.object().value("array Of URLs").toArray().at(i).toObject().keys());
    }
    return QJsonArray::fromStringList(list);
}

void CModel::AddAccountToSite(const QString &site,const QString &login,const  QString &password)
{
    QJsonArray arrOfAccsOfSite = GetAccountsOfSiteByIndex(GetIndexOfSiteByName(site));//ok
    QJsonObject obj, siteObj, result;
    obj.insert(login, password);
    arrOfAccsOfSite.push_back(obj);//ok

    QJsonArray demo = GetUrlsArr();

    //demo = QJsonArray([{"Vk.com":[{"vkLogin1":"vkPas1"},{"vkLog2":"vkPas2"}]},{"ok.ru":[{"OKkogin1":"OKPASS1"},{"OKLog2":"OkLog2"}]},{"11111":[]},{"Write the Name/URL of the servise":[]},{"Write the Name/URL of the servise":[]}])
    //demo[GetIndexOfSiteByName(site)]  = QJsonValue(object, QJsonObject({"Vk.com":[{"vkLogin1":"vkPas1"},{"vkLog2":"vkPas2"}]}))

    //demo[GetIndexOfSiteByName(site)].toObject().value(site).toArray() = QJsonArray([{"vkLogin1":"vkPas1"},{"vkLog2":"vkPas2"}])
    //arrOfAccsOfSite  = QJsonArray([{"vkLogin1":"vkPas1"},{"vkLog2":"vkPas2"},{"aaaaaa":"bBbbb"}])
    siteObj.insert(this->GetArrayOfUrls()[GetIndexOfSiteByName(site)].toString(), arrOfAccsOfSite);//QJsonObject({"11111":[{"Set Login":"Set Password\n"}]})
    demo[GetIndexOfSiteByName(site)] = siteObj;//[{"Vk.com":[{"vkLogin1":"vkPas1"},{"vkLog2":"vkPas2"}]},{"ok.ru":[{"OKkogin1":"OKPASS1"},{"OKLog2":"OkLog2"}]},{"11111":[]},{"Write the Name/URL of the servise
    result.keys() = model->GetObj().keys();
    result.toVariantMap();
    result["array Of URLs"] = demo;
    model->SetModel(result);

}

 void CModel::DeleteSiteByIndex(const int i)
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
void CModel::addSiteToModel(const QString &url, const QJsonArray &arrOfAccounts)//Переделатть с копией МОДЕЛИ
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

void CModel::SaveModelToFile(const QJsonDocument &document, const QString &fileName)//сделать абстрактные функции
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document.toJson());
    jsonFile.close();
}

QJsonArray CModel::GetAccountsOfSiteByIndex(const int &index)// сделать через exception? |
{
    QJsonArray urls = this->GetArrayOfUrls();

    if(index < 0 || urls.size() == 0 || index >= urls.size())
    {
        qWarning() << "in GetAccountsOfSiteByIndex(index) error index" << endl;
        //надо чтото еще сделать(закрыть прогу)
    }

    return mainDoc.object().value("array Of URLs").toArray().at(index).toObject().value(urls[index].toString()).toArray();

}

int CModel::GetIndexOfSiteByName(const QString &site)// было QString site и работало
{
    for(int i = 0; i < mainDoc.object().value("array Of URLs").toArray().size(); i++)
    {
        if(site == mainDoc.object().value("array Of URLs").toArray().at(i).toObject().keys().at(0)) // не может ли быть ошибки?
        {
            return i;
        }
    }
    return 0;
}

