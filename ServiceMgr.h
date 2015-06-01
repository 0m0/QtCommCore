#ifndef SERVICEMGR_H
#define SERVICEMGR_H

#include <QObject>
#include <QTcpServer>

class CommServer;

class ServiceMgr : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServiceMgr(CommServer *parent = 0);

signals:

public slots:

};

#endif // SERVICEMGR_H
