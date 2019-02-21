#ifndef CADDACCOUNT_H
#define CADDACCOUNT_H

#include <QDialog>
#include <QAbstractButton>


class CAddAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CAddAccount(QWidget *parent = 0);


    ~CAddAccount();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    CAddAccount *ui;

};



#endif // CADDACCOUNT_H
