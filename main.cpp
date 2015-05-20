#include <QCoreApplication>
#include "CommServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CommServer server("C:\\Users\\RM-PC\\Documents\\demo.txt");

    return a.exec();
}
