#include "stacker.h"
#include "ui_stacker.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>

stacker::stacker(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    layout->addLayout(stack);

   // layout->setStretch(1, 2);

    setCentralWidget(widget);
    MassPass *mas = new MassPass;
    MainWindow *mai = new MainWindow;
    stack->addWidget(mas);
    stack->addWidget(mai);
    stack->setCurrentIndex(0);
    connect(mas, SIGNAL(OkClicked()), this, SLOT(hide()));
}

stacker::~stacker()
{
}
