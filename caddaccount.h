#ifndef CADDACCOUNT_H
#define CADDACCOUNT_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class CAddAccount;
}

class CAddAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CAddAccount(QWidget *parent = 0);

    QString GetLogin()
    {
        return login;
    }

    QString GetPassword()
    {
        return password;
    }
    ~CAddAccount();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::CAddAccount *ui;
    QString login;
    QString password;
};



#endif // CADDACCOUNT_H
