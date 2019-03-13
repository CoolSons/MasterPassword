#ifndef STACKER_H
#define STACKER_H

#include <QMainWindow>
#include "masspass.h"
#include "mainwindow.h"

namespace Ui {
class stacker;
}

class stacker : public QMainWindow
{
    Q_OBJECT

public:
    explicit stacker(QWidget *parent = 0);
    ~stacker();

private:
    Ui::stacker *ui;
};

#endif // STACKER_H
