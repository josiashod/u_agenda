#include "uagenda.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UAgenda w;
    w.show();
    return a.exec();
}
