#include "processstudent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProcessStudent w;
    w.show();

    return a.exec();
}
