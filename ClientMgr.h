#ifndef CLIENTMGR_H
#define CLIENTMGR_H

#include <QObject>
#include <QTcpServer>

class CommServer;

class ClientMgr : public QTcpServer
{
    Q_OBJECT
public:
    explicit ClientMgr(CommServer *parent = 0);

signals:

public slots:

};

#endif // CLIENTMGR_H
