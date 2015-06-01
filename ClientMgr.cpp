
#include "CommServer.h"
#include "ClientMgr.h"

ClientMgr::ClientMgr(CommServer *parent) :
    QTcpServer(parent)
{
}
