#ifndef CMASTERPASS_H
#define CMASTERPASS_H

#include <QDialog>

#include "mainwindow.h"
namespace Ui {
class CMasterPass;
}

class CMasterPass : public QDialog
{
    Q_OBJECT

public:
    explicit CMasterPass(QWidget *parent = 0);
    bool cancel = false;

    ~CMasterPass();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CMasterPass *ui;

};

#endif // CMASTERPASS_H
