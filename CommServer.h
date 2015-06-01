#ifndef BUFFSERVER_H
#define BUFFSERVER_H

#include <QtNetwork/QTcpSocket>
#include <QHash>
#include <QList>
#include "RCBMsgParser.h"

#define MAX_BUFF_SIZE   100
#define MAX_NUM_RECORDS 1000
#define MAX_NUM_HEADERS 100

class CommServer : public QTcpSocket
{
    Q_OBJECT
public:
    explicit CommServer(const QString &fileName, QObject *parent = 0);

signals:

public slots:

private:
    RCBMsgParser *my_msgParser;
    bool loadTable(const QString &fileName);
    QList<QHash<HeaderItem *, QString> > my_table;
};

#endif // BUFFSERVER_H
