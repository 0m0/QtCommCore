#ifndef BUFFSERVER_H
#define BUFFSERVER_H

#include <QtNetwork/QTcpServer>
#include <QHash>
#include <QList>
#include "RCBMsgParser.h"

#define MAX_BUFF_SIZE   100
#define MAX_NUM_RECORDS 1000
#define MAX_NUM_HEADERS 100

enum _DataTypes {
    E_BIT, E_BOOLEAN, E_TINYINT,
    E_INT, E_BIGINT, E_FLOAT,
    E_STRING, E_DATETIME
};

typedef struct {
    char *label;
    int index;
    int dataType;
    int isMutable;
} HeaderItem;

class CommServer : public QTcpServer
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
