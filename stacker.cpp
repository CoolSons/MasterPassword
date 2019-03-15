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
    mas = new MassPass;
    mai = new MainWindow;
    stack->addWidget(mas);
    stack->addWidget(mai);
    stack->setCurrentIndex(0);



    this->setCentralWidget(widget);
    this->setGeometry(700,400, int(mas->GetX()+260), int(mas->GetY()+145));

    connect(mas, SIGNAL(OkClicked()), this, SLOT(showMW()));
    connect(mas, SIGNAL(CancelClicked()), this, SLOT(close()));
    connect(mas, SIGNAL(OkClicked()), this, SLOT(setMwGeometry()));

  }

stacker::~stacker()
{
}
void stacker::showMW()
{
    stack->setCurrentIndex(1);
}

void stacker::setMwGeometry()
{
    this->setGeometry(500, 200, int(2*mai->GetW()+75), int(mai->GetH()+90));
    qWarning() <<  this->geometry().width() << " " << this->geometry().height();
}
