#ifndef MASSPASS_H
#define MASSPASS_H

#include <QWidget>

namespace Ui {
class MassPass;
}

class MassPass : public QWidget
{
    Q_OBJECT

public:
    explicit MassPass(QWidget *parent = 0);

    ~MassPass();
int GetX();
int GetY();
QRect GetGeo();

private slots:
    void on_pushButton_clicked();
signals:
    OkClicked();
private:
    Ui::MassPass *ui;
};

#endif // MASSPASS_H
