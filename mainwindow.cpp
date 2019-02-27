        //Set methods as Mainwindowsed
    #include "mainwindow.h"
    #include "ui_mainwindow.h"
    #include "caddaccount.h"
    #include "cmodel.h"

    CModel *model = CModel::GetModel();

    void SetSettingsToTable(Ui::MainWindow *ui)
    {
        ui->tableWidget->setColumnCount(2);
        QTableWidgetItem *login = new QTableWidgetItem();
        login->setText("Login");
        ui->tableWidget->setHorizontalHeaderItem(0, login);
        QTableWidgetItem *password = new QTableWidgetItem();
        password->setText("Password");
        ui->tableWidget->setHorizontalHeaderItem(1, password);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->QLineedit->selectAll();
    }

    void setAccountsToListWidget(Ui::MainWindow *ui)
    {

        ui->listWidget->clear();
        QJsonArray arrOfSites = model->GetArrayOfUrls();

        for(int i =0; i < arrOfSites.size();i++)
        {
            ui->listWidget->addItem(arrOfSites[i].toString());
        }

    }


    void setSiteToTableWidget(Ui::MainWindow *ui, const int index)
    {
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);

        QJsonArray accNumberI = model->GetAccountsOfSiteByIndex(index);

        for(int i = 0; i< accNumberI.size(); i++)
        {
            ui->tableWidget->insertRow(0);
        }

        for(int j = 0; j < accNumberI.size(); j++)
            {
                 ui->tableWidget->setItem(j, 0, new QTableWidgetItem(accNumberI[j].toObject().keys().join("")));
                 ui->tableWidget->setItem(j, 1, new QTableWidgetItem(accNumberI[j].toObject().value(accNumberI[j].toObject().keys().join("")).toString()));
            }

    }



    void SetModelToWidget(Ui::MainWindow *ui)
    {
        ui->listWidget->clear();
        ui->tableWidget->clear();
        setAccountsToListWidget(ui);
        //if(!model->GetArrayOfUrls().isEmpty())
             //ui->listWidget->
    }

    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        SetSettingsToTable(ui);
        SetModelToWidget(ui);

    }


    MainWindow::~MainWindow()
    {
        delete ui;
    }


    void MainWindow::on_listWidget_pressed(const QModelIndex &index)
    {

        //берем массив под индексом index "Vk.com": [ { "vkLogin": "PAssw1"},  { "vkLog2": "paasss2" }]
        // берем в цикле по очереди объекты сайтов(аккаунты)
        //для каждого аккаунта выводим логин и пароль

        ui->tableWidget->setRowCount(0);
        const int i = index.row();
        QJsonArray accNumberI = model->GetAccountsOfSiteByIndex(i);

        for(int i = 0; i< accNumberI.size(); i++)
        {
            ui->tableWidget->insertRow(0);
        }

        for(int j = 0; j < accNumberI.size(); j++)
            {

                 ui->tableWidget->setItem(j, 0, new QTableWidgetItem(accNumberI[j].toObject().keys().join("")));
                 ui->tableWidget->setItem(j, 1, new QTableWidgetItem(accNumberI[j].toObject().value(accNumberI[j].toObject().keys().join("")).toString()));
            }


    }

    void MainWindow::on_QLineedit_returnPressed()
    {
        if(ui->QLineedit->text() != "")
        {
            ui->listWidget->addItem(ui->QLineedit->text());   //это кинуть в модель и лист наш сайт и пустой массив акков
            QJsonArray emptyJsonArr
            {};
           model->addSiteToModel(ui->QLineedit->text(), emptyJsonArr);
           model->SaveModelToFile(model->GetDoc(), model->globPath);
           ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
            ui->QLineedit->clear();
       }
    }



    void MainWindow::on_ButtonDeleteSite_clicked()
    {

        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
        foreach(QListWidgetItem *item, items)
        {
            int index = ui->listWidget->row(item);
            delete ui->listWidget->takeItem(index);
            model->DeleteSiteByIndex(index);
        }

         model->SaveModelToFile(model->GetDoc(), model->globPath);
        if(ui->listWidget->count() == 0)
        {ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);}
    }

    void MainWindow::on_ButtonAddSite_clicked()
    {
        bool haveAlreadySite = false;

        for(int i = 0; i < model->GetArrayOfUrls().size(); i++)
        {
            if(ui->QLineedit->text() == model->GetArrayOfUrls()[i].toString())
                haveAlreadySite = true;

        }
        qWarning() << endl << endl;
        if(ui->QLineedit->text() != "" && haveAlreadySite == false)
        {
            ui->listWidget->addItem(ui->QLineedit->text());   //это кинуть в модель и лист наш сайт и пустой массив акков
            QJsonArray emptyJsonArr
            {};
            model->addSiteToModel(ui->QLineedit->text(), emptyJsonArr);
            model->SaveModelToFile(model->GetDoc(), model->globPath);
            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
            ui->QLineedit->clear();
        }
        else
        {
            ui->QLineedit->setText("Set correct site please");
               ui->QLineedit->selectAll();
        }
    }




    void MainWindow::on_ButtonAddAcc_clicked()//это должно быть на ОК а не на add,
    {
        //только добавить в таблицу и встать туда, а потом отдельно уже переносить в таблицу

        int index=0;

        CAddAccount addWindow;
        QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
        foreach(QListWidgetItem *item, items)
        {
            index = ui->listWidget->row(item);
            //исправиить насчет памяти
            addWindow.setModal(true);
            addWindow.exec();
            if(addWindow.OkClicked == 1 && addWindow.login() !="" && addWindow.password() != "")
            {
                int a = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(a);
                a++;
                ui->tableWidget->setItemSelected(ui->tableWidget->item(a-1,0), 1);

            model->AddAccountToSite(    model->GetArrayOfUrls()[index].toString(), addWindow.login(), addWindow.password());
            model->SaveModelToFile(model->GetDoc(), model->globPath);
            setSiteToTableWidget(ui, index);
            }
        }



    }


    void MainWindow::on_ButtonDeleteAcc_clicked()
    {
        int tableIndex = 0;
        int listIndex = 0;
        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
        foreach(QTableWidgetItem *item, items)
        {
           tableIndex = ui->tableWidget->row(item);

        }

        QList<QListWidgetItem*> items2 = ui->listWidget->selectedItems();
        foreach(QListWidgetItem *item, items2)
        {
            listIndex = ui->listWidget->row(item);
        }
       // qWarning() << listIndex << tableIndex; //параметры окей

        if(!items.empty())
            model->DeleteAccountOfSite(model->GetArrayOfUrls()[listIndex].toString(), tableIndex);

        setSiteToTableWidget(ui, listIndex);
    }


    void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
    {
        ui->tableWidget->selectRow(index.row());

    }



    void MainWindow::on_listWidget_itemSelectionChanged()
    {
        int listIndex = 0;
        QList<QListWidgetItem*> items2 = ui->listWidget->selectedItems();
        foreach(QListWidgetItem *item, items2)
        {
            listIndex = ui->listWidget->row(item);
        }
        setSiteToTableWidget(ui, listIndex);
    }










