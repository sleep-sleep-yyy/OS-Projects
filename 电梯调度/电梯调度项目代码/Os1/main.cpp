#include "all_in_out.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    all_in_out w;
    w.show();
    return a.exec();
}
