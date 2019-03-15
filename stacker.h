#ifndef STACKER_H
#define STACKER_H

#include <QMainWindow>
#include "masspass.h"
#include "mainwindow.h"
#include <QtWidgets/QStackedLayout>

namespace Ui {
class stacker;
}

class stacker : public QMainWindow
{
    Q_OBJECT

public:
    explicit stacker(QWidget *parent = 0);
    QStackedLayout *stack ;
    QWidget *widget;
    MassPass *mas ;
    MainWindow *mai ;
    ~stacker();
public slots:
    void showMW();
    void setMwGeometry();
private:
    Ui::stacker *ui;
};

#endif // STACKER_H
