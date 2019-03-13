#ifndef MP_H
#define MP_H

#include <QMainWindow>

namespace Ui {
class mp;
}

class mp : public QMainWindow
{
    Q_OBJECT

public:
    explicit mp(QWidget *parent = 0);
    ~mp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mp *ui;
};

#endif // MP_H
