#include "mainwindow.h"
#include <QApplication>
#include <QErrorMessage>

QJsonDocument GetDocFromFilename(QString &filename)
{

    QFile file;
    //QString globPath= QFileDialog::getOpenFileName(nullptr,"","D:\\Users\Root\Desktop\JsonBase","*.json");  // - чтобы спрашивать файл
    // globPath = "D:\\Users\Root\Desktop\JsonBase.json"; //   D:\Users\Root\Desktop\JsonBase.json
    file.setFileName(filename);
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


QJsonDocument GetDocFromFile( QFile& file)
{
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

QString ObjectToString(const QJsonObject &_jsObj)
{
    QJsonDocument Doc(_jsObj);
    QByteArray ba = Doc.toJson();
    return QString(ba);

}

QJsonDocument ObjectToDocument(const QJsonObject& obj)//not tested
{
    return QJsonDocument(obj);
}

QString DocumentToString(const QJsonDocument &_jsObj)
{
    QByteArray ba = _jsObj.toJson();
    return QString(ba);
}

QJsonObject DocumentToObject(const QJsonDocument &doc){

    return doc.object();

}

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
