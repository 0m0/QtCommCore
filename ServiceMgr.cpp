
#include "CommServer.h"
#include "ServiceMgr.h"

ServiceMgr::ServiceMgr(CommServer *parent) :
    QTcpServer(parent)
{
}
