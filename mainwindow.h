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

    void on_ButtonDeleteAcc_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_listWidget_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

};








#endif // MAINWINDOW_H
