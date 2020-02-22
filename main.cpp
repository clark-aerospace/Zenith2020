#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Clark Aerospace");
    QCoreApplication::setApplicationName("Zenith");
    MainWindow w;
    w.show();
    return a.exec();
}
