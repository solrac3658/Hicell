#include "venta.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Venta w;
    w.show();

    return a.exec();
}
