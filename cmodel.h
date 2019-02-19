#ifndef CMODEL_H
#define CMODEL_H


#include "mainwindow.h"
#pragma once

class CModel
{
private:
    QJsonObject mainObject;
    QJsonDocument mainDoc;
    QString mainString;
    static CModel *model;
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

    static  CModel *GetModel() //returns this model |
    {
        if(!model)
            model = new CModel();
        return model;
    }

    const QJsonArray GetUrlsArr()
     {
         return this->GetDoc().object().value("array Of URLs").toArray();
     }

    QString GetLogin(const QJsonObject &account)
    {
        return  account.keys().join("");
    }

    QString GetPassword(const QJsonObject &account)
    {
        return account.value(GetLogin(account)).toString();
    }

     QJsonArray GetArrayOfUrls();

    QJsonArray GetAccountsOfSiteByIndex(const int &index);// сделать через exception? |

    int GetIndexOfSiteByName(const QString &site);// было QString site и работало
    void AddAccountToSite(const QString &site,const QString &login,const  QString &password);
    void DeleteSiteByIndex(const int i);
    void addSiteToModel(const QString &url, const QJsonArray &arrOfAccounts);//Переделатть с копией МОДЕЛИ
    void SaveModelToFile(const QJsonDocument &document, const QString &fileName);//сделать абстрактные функции



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


#endif // CMODEL_H
