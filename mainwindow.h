#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <cstdio>
#include <QString>
#include <QFileDialog>
#include <QStandardItem>
#include <QDebug>
#include <QTableWidget>


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
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
};

class Account
{
    QString _log;
    QString _pas;
public:
    Account() {}
};

inline void aaa()
{

}


class CModel
{
    QJsonObject mainObject;
    QJsonDocument mainDoc;
    QString mainString;
public:
    QJsonDocument StringToDocument(const QString& data)
    {
        return QJsonDocument::fromJson(data.toUtf8());
    }
    QJsonObject StringToObject(const QString& in)
    {
        QJsonObject obj;
        QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
        // check validity of the document
        if(!doc.isNull())
        {
            if(doc.isObject())
            {
                obj = doc.object();
            }
            else
            {
                qDebug() << "Document is not an object" << endl;
            }
        }
        else
        {
            qDebug() << "Invalid JSON...\n" << in << endl;
        }
        return obj;
    }
    QString ObjectToString(QJsonObject _jsObj)
    {


        QJsonDocument Doc(_jsObj);
        QByteArray ba = Doc.toJson();
        return QString(ba);

    }
    QString DocumentToString(QJsonDocument _jsObj)
    {
        QByteArray ba = _jsObj.toJson();
        return QString(ba);
    }

CModel() {}


};



#endif // MAINWINDOW_H
