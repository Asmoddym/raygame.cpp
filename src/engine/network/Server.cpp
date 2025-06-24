#include "Server.h"
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "Log.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

int getStatus(const SOCKET s, int flag);

int macro::network::Server::run() {
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        PrintError("WSAStartup failed with error: %d", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        PrintError("getaddrinfo failed with error: %d", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        PrintError("socket failed with error: %ld", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    unsigned long argp = 1;
    iResult = setsockopt(ListenSocket,
        SOL_SOCKET,
        /*
        SO_REUSEADDR: 4 Allows the socket to be bound to an address that is already in use. For more information, see bind. Not applicable on ATM sockets.
        */
        SO_REUSEADDR,
        (char*)&argp, sizeof(argp));
    if (iResult != 0)
    {
        printf("setsockopt() error %d\n", result);
        return EXIT_FAILURE;
    }
if (ioctlsocket(ListenSocket,
        FIONBIO,
        &argp) == SOCKET_ERROR)
    {
        printf("ioctlsocket() error %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        PrintError("bind failed with error: %d", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        PrintError("listen failed with error: %d", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    while ((iResult = getStatus(ListenSocket, 0x1)) != SOCKET_ERROR) {
      PrintWarning("status: ", iResult);
      if (iResult == 1) {
        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
          PrintError("accept failed with error: %d", WSAGetLastError());
          closesocket(ListenSocket);
          WSACleanup();
          return 1;
        }

        int count = 0;
        // No longer need server socket
        // closesocket(ListenSocket);

        iResult = 1;
        // Receive until the peer shuts down the connection
        while (iResult > 0 && count < 3) {
          Sleep(2000);
          PrintError("checking...");
          unsigned long howMuchInBuffer = 0;
          ioctlsocket(ClientSocket, FIONREAD,
              &howMuchInBuffer);

          PrintError("how much: ", howMuchInBuffer);

          if (howMuchInBuffer > 0) {
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            PrintError("coucou");
            if (iResult > 0) {
              PrintError("Bytes received: %d", iResult);

              // Echo the buffer back to the sender
              iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
              if (iSendResult == SOCKET_ERROR) {
                PrintError("send failed with error: %d", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
              }
              PrintError("Bytes sent: %d", iSendResult);
            }
            else if (iResult == 0)
              PrintError("Connection closing...");
            else  {
              PrintError("recv failed with error: %d", WSAGetLastError());
              closesocket(ClientSocket);
              WSACleanup();
              return 1;
            }
          } else { count++; PrintError("No data..."); }
        }

        // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
          PrintError("shutdown failed with error: %d", WSAGetLastError());
          closesocket(ClientSocket);
          WSACleanup();
          return 1;
        }

        // cleanup
        closesocket(ClientSocket);
        PrintError("Closed!");
      }

    }

    WSACleanup();

    return 0;
}

// status: 0x1 for read, 0x2 for write, 0x4 for exception
int getStatus(const SOCKET a_socket, int status)
{
    // zero seconds, zero milliseconds. max time select call allowd to block
    static timeval instantSpeedPlease = { 0, 0 };
    fd_set a = { 1, {a_socket} };
    fd_set * read = ((status & 0x1) != 0) ? &a : NULL;
    fd_set * write = ((status & 0x2) != 0) ? &a : NULL;
    fd_set * except = ((status & 0x4) != 0) ? &a : NULL;
    /*
    select returns the number of ready socket handles in the fd_set structure, zero if the time limit expired, or SOCKET_ERROR if an error occurred. WSAGetLastError can be used to retrieve a specific error code.
    */
    int result = select(0, read, write, except, &instantSpeedPlease);
    if (result == SOCKET_ERROR)
    {
        result = WSAGetLastError();
    }
    if (result < 0 || result > 3)
    {
        printf("select(read) error %d\n", result);
        return SOCKET_ERROR;
    }
    return result;
}
