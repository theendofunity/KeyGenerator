#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("LEMZ_T");

    MainWindow w;
    w.show();
    return a.exec();
}
