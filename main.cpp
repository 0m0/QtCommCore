//#include <QCoreApplication>
//#include "CommServer.h"

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    CommServer server("C:\\Users\\RM-PC\\Documents\\demo.txt");

//    return a.exec();
//}

#include <QtCore/QDateTime>
#include <QtCore/QDebug>

int main()
{
    uint ut = 1431931514;
    QDateTime dt;
    dt.setTime_t(ut);
    dt.setMSecsSinceEpoch(14811136);
    qDebug() << dt.toString();
}
