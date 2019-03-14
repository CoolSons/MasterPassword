#include "stacker.h"
#include <QApplication>
#include "jsonfunctions.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    stacker w;

    w.show();

    return a.exec();
}
