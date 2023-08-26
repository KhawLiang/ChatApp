#include "mainwindow.h"
#include "server.h"
#include "client.h"
#include "home.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    home hPg;

    hPg.show();

    return a.exec();
}
