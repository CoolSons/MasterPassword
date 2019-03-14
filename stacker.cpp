#include "stacker.h"
#include "ui_stacker.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>

stacker::stacker(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::stacker)
{
    ui->setupUi(this);
    widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    stack = new QStackedLayout;
    widget->setLayout(layout);
    layout->addLayout(stack);
    layout->setStretch(1, 2);


   // this->setCentralWidget(widget);
//    ui->centralwidget->setBaseSize(400,400);
//    ui->centralwidget->resize(400,400);
    MassPass *mas = new MassPass;
    MainWindow *mai = new MainWindow;
    stack->addWidget(mas);
    stack->addWidget(mai);
    stack->setCurrentIndex(0);

//    ui->centralwidget->setFixedHeight(mas->GetY());
    this->setCentralWidget(widget);
    connect(mas, SIGNAL(OkClicked()), this, SLOT(showMW()));
}

stacker::~stacker()
{
}
void stacker::showMW()
{
    stack->setCurrentIndex(1);
}
