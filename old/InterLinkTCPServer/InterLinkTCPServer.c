

#include "InterLinkTCPServer.h"

DWORD WINAPI CreateTCPServerBlocking(LPVOID lpvParam);
DWORD WINAPI DataAvailableTCP(LPVOID lpvParam);

static const char *Port;

BOOL CreateTCPServer(const char *port)
{
	HANDLE hThread = NULL;
	DWORD  dwThreadId = 0;
    
    Port = port;

	hThread = CreateThread(NULL, 0, CreateTCPServerBlocking, (LPVOID)NULL, 0, &dwThreadId);

	if (hThread == NULL)
	{
		printf("Create TCP Server Thread failed, error code %d.\n", GetLastError());
		return FALSE;
	}

	return TRUE;
}

DWORD WINAPI CreateTCPServerBlocking(LPVOID lpvParam)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return FALSE;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, Port, &hints, &result);
	if (iResult != 0) {
		printf("Getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return FALSE;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return FALSE;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("Bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return FALSE;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("Listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return FALSE;
	}

	HANDLE hThread = NULL;
	DWORD  dwThreadId = 0;

	//int iSendResult;
	CHAR* recvbuf;
	int recvbuflen = TCP_BufferSize;

	do {
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("Accept failed with error: %d\n", WSAGetLastError());
			//closesocket(ListenSocket);
			//WSACleanup();
			//return 0;
			continue;
		}

		//recvbuflen = TCP_BufferSize;
		recvbuf = (CHAR*)malloc(sizeof(CHAR)*recvbuflen);
		memset(recvbuf, '\0', recvbuflen);

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {

			if (iResult == 6 && strcmp(recvbuf, "<Exit>") == 0)
			{
				closesocket(ClientSocket);
				//iResult = shutdown(ClientSocket, SD_SEND);
				break;
			}
			else
				hThread = CreateThread(NULL, 0, DataAvailableTCP, (LPVOID)recvbuf, 0, &dwThreadId);

			//// Echo the buffer back to the sender
			//iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			//if (iSendResult == SOCKET_ERROR) {
			//	printf("send failed with error: %d\n", WSAGetLastError());
			//	closesocket(ClientSocket);
			//	WSACleanup();
			//	return 1;
			//}
			//printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else
			printf("Recv failed with error: %d\n", WSAGetLastError());

		closesocket(ClientSocket);

		//// shutdown the connection since we're done
		//iResult = shutdown(ClientSocket, SD_SEND);
		//if (iResult == SOCKET_ERROR) {
		//	printf("Shutdown failed with error: %d\n", WSAGetLastError());
		//	continue;
		//}

	} while (1);

	// No longer need server socket
	closesocket(ListenSocket);
	WSACleanup();

	return TRUE;
}

DWORD WINAPI DataAvailableTCP(LPVOID lpvParam)
{
	CHAR* Data = (CHAR*)lpvParam;
	
	handle_cmd_msg(Data);
	return 1;
}
