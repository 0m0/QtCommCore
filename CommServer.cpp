
#include <QCoreApplication>
#include <QFile>
#include "CommServer.h"
#include <QTime>

CommServer::CommServer(const QString &fileName, QObject *parent) :
    QTcpServer(parent)
{
    my_msgParser = new RCBMsgParser(this);

    QFile demo("C:\\Users\\RM-PC\\Documents\\msg.txt");
    demo.open(QIODevice::ReadOnly | QIODevice::Text);

    QString all = demo.readAll();

    QTime t;
    t.start();
    //for (int i = 0; i < 1000; i++) {
        my_msgParser->parse(all, RCBMsgParser::DefaultMode);
    //}
    qDebug() << t.elapsed();
    //qDebug() << "Parsing msg: " << my_msgParser->parse(all, RCBMsgParser::DefaultMode);;
}

bool CommServer::loadTable(const QString &fileName)
{
}
