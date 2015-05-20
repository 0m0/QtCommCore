
#ifndef INTERLINK_SERVER
#define INTERLINK_SERVER

#undef UNICODE

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define TCP_BufferSize 65535

#define SEND SendDataSocket("127.0.0.1", "1515", telegramBuffer);

DWORD WINAPI CreateTCPServerBlocking(LPVOID lpvParam);
DWORD WINAPI DataAvailableTCP(LPVOID lpvParam);
BOOL CreateTCPServer(const char *port);

#endif // INTERLINK_SERVER
