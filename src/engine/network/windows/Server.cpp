#include "network/Server.h"
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
     SOCKET ReceivingSocket;
     SOCKADDR_IN ReceiverAddr;
     int Port = 8888;
     char ReceiveBuf[1024];
     int BufLength = 1024;
     SOCKADDR_IN SenderAddr;
     int SenderAddrSize = sizeof(SenderAddr);
     int ByteReceived = 5;

   // Initialize Winsock version 2.2

   if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0){

        printf("Server: WSAStartup failed with error: %ld\n", WSAGetLastError());

        return -1;
   }
   else{
        printf("Server: The Winsock DLL status is: %s.\n", wsaData.szSystemStatus);
   }

     // Create a new socket to receive datagrams on.

     ReceivingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

     if (ReceivingSocket == INVALID_SOCKET){

          //Print error message
          printf("Server: Error at socket(): %ld\n", WSAGetLastError());

          // Clean up
          WSACleanup();

          // Exit with error
          return -1;
     }
     else{
          printf("Server: socket() is OK!\n");
     }

     /*Set up a SOCKADDR_IN structure that will tell bind that
     we want to receive datagrams from all interfaces using port 5150.*/


     // The IPv4 family
     ReceiverAddr.sin_family = AF_INET;

     // Port no. (8888)
     ReceiverAddr.sin_port = htons(Port);

     // From all interface (0.0.0.0)
     ReceiverAddr.sin_addr.s_addr = htonl(INADDR_ANY);


     struct timeval read_timeout;
     read_timeout.tv_sec = 0;
     read_timeout.tv_usec = 16000;
#if _WIN32
    DWORD dw = (read_timeout.tv_sec * 1000) + ((read_timeout.tv_usec + 999) / 1000);
     setsockopt(ReceivingSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&dw, sizeof read_timeout);
#else
     setsockopt(ReceivingSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&read_timeout, sizeof read_timeout);
#endif

   // Associate the address information with the socket using bind.

   // At this point you can receive datagrams on your bound socket.

   if (bind(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR){

        // Print error message
        printf("Server: Error! bind() failed!\n");

        // Close the socket
        closesocket(ReceivingSocket);

        // Do the clean up
        WSACleanup();

        // and exit with error
        return -1;
     }
     else{
        printf("Server: bind() is OK!\n");
     }


   // Print some info on the receiver(Server) side...
   getsockname(ReceivingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));


   printf("Server: Receiving IP(s) used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));

   printf("Server: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));

   printf("Server: I\'m ready to receive data packages. Waiting...\n\n");



   // At this point you can receive datagrams on your bound socket.
   while (1){ // Server is receiving data until you will close it.(You can replace while(1) with a condition to stop receiving.)

        ByteReceived = recvfrom(ReceivingSocket, ReceiveBuf, BufLength, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);

        if (ByteReceived > 0){ //If there are data
            //Print information for received data
            printf("Server: Total Bytes received: %d\n", ByteReceived);
            printf("Server: The data is: %s\n", ReceiveBuf);
            for (int i = 0;  i< BufLength; i++) { printf("%d", ReceiveBuf[i]); }
            printf("\n");
        }
        else if (ByteReceived <= 0){ //If the buffer is empty
                                     if (WSAGetLastError() != WSAETIMEDOUT) {

            //Print error message
            printf("Server: Connection closed with error code: %ld\n", WSAGetLastError());
                                     } else { printf("Waiting for something...\n"); }
        }
        else{ //If error
            //Print error message
            printf("Server: recvfrom() failed with error code: %d\n", WSAGetLastError());
        }
   }


   // Print some info on the sender(Client) side...
   getpeername(ReceivingSocket, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
   printf("Server: Sending IP used: %s\n", inet_ntoa(SenderAddr.sin_addr));
   printf("Server: Sending port used: %d\n", htons(SenderAddr.sin_port));


   // When your application is finished receiving datagrams close the socket.
   printf("Server: Finished receiving. Closing the listening socket...\n");
   if (closesocket(ReceivingSocket) != 0){
        printf("Server: closesocket() failed! Error code: %ld\n", WSAGetLastError());
   }
   else{
        printf("Server: closesocket() is OK\n");
   }


   // When your application is finished call WSACleanup.
   printf("Server: Cleaning up...\n");

   if(WSACleanup() != 0){
        printf("Server: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
   }
   else{
        printf("Server: WSACleanup() is OK\n");
   }
}

//
//
//
//
//     WSADATA wsaData;
//     int iResult;
//
//     SOCKET ListenSocket = INVALID_SOCKET;
//     SOCKET ClientSocket = INVALID_SOCKET;
//
//     struct addrinfo *result = NULL;
//     struct addrinfo hints;
//
//     int iSendResult;
//     char recvbuf[DEFAULT_BUFLEN];
//     int recvbuflen = DEFAULT_BUFLEN;
//
//     // Initialize Winsock
//     iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//     if (iResult != 0) {
//         PrintError("WSAStartup failed with error: %d", iResult);
//         return 1;
//     }
//
//     ZeroMemory(&hints, sizeof(hints));
//     hints.ai_family = AF_INET;
//     hints.ai_socktype = SOCK_DGRAM;
//     hints.ai_protocol = IPPROTO_UDP;
//     // hints.ai_flags = AI_PASSIVE;
//
//     // Resolve the server address and port
//     iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//     if ( iResult != 0 ) {
//         PrintError("getaddrinfo failed with error: %d", iResult);
//         WSACleanup();
//         return 1;
//     }
//
//     // Create a SOCKET for the server to listen for client connections.
//     ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//     if (ListenSocket == INVALID_SOCKET) {
//         PrintError("socket failed with error: %ld", WSAGetLastError());
//         freeaddrinfo(result);
//         WSACleanup();
//         return 1;
//     }
//     unsigned long argp = 1;
//     iResult = setsockopt(ListenSocket,
//         SOL_SOCKET,
//         /*
//         SO_REUSEADDR: 4 Allows the socket to be bound to an address that is already in use. For more information, see bind. Not applicable on ATM sockets.
//         */
//         SO_REUSEADDR,
//         (char*)&argp, sizeof(argp));
//     if (iResult != 0)
//     {
//         printf("setsockopt() error %d\n", result);
//         return EXIT_FAILURE;
//     }
// if (ioctlsocket(ListenSocket,
//         FIONBIO,
//         &argp) == SOCKET_ERROR)
//     {
//         printf("ioctlsocket() error %d\n", WSAGetLastError());
//         return EXIT_FAILURE;
//     }
//
//     // Setup the UDP listening socket
//     iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//     if (iResult == SOCKET_ERROR) {
//         PrintError("bind failed with error: %d", WSAGetLastError());
//         freeaddrinfo(result);
//         closesocket(ListenSocket);
//         WSACleanup();
//         return 1;
//     }
//
//     freeaddrinfo(result);
//
//     // iResult = listen(ListenSocket, SOMAXCONN);
//     // if (iResult == SOCKET_ERROR) {
//     //     PrintError("listen failed with error: %d", WSAGetLastError());
//     //     closesocket(ListenSocket);
//     //     WSACleanup();
//     //     return 1;
//     // }
//
//     while ((iResult = getStatus(ListenSocket, 0x1)) != SOCKET_ERROR) {
//       PrintWarning("status: ", iResult);
//       if (iResult == 1) {
//
//         iResult = recvfrom(ListenSocket, recvbuf, 512, 0, );
//
//
//         // Accept a client socket
//         ClientSocket = accept(ListenSocket, NULL, NULL);
//         if (ClientSocket == INVALID_SOCKET) {
//           PrintError("accept failed with error: %d", WSAGetLastError());
//           closesocket(ListenSocket);
//           WSACleanup();
//           return 1;
//         }
//
//         int count = 0;
//         // No longer need server socket
//         // closesocket(ListenSocket);
//
//         iResult = 1;
//         // Receive until the peer shuts down the connection
//         while (iResult > 0 && count < 3) {
//           Sleep(16);
//           PrintError("checking...");
//           unsigned long howMuchInBuffer = 0;
//           ioctlsocket(ClientSocket, FIONREAD,
//               &howMuchInBuffer);
//
//           PrintError("how much: ", howMuchInBuffer);
//
//           if (howMuchInBuffer > 0) {
//             iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
//             PrintError("coucou");
//             if (iResult > 0) {
//               recvbuf[iResult] = 0;
//               PrintError("Bytes received: %d", iResult, recvbuf);
//
//               // Echo the buffer back to the sender
//               iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
//               if (iSendResult == SOCKET_ERROR) {
//                 PrintError("send failed with error: %d", WSAGetLastError());
//                 closesocket(ClientSocket);
//                 WSACleanup();
//                 return 1;
//               }
//               PrintError("Bytes sent: %d", iSendResult);
//             }
//             else if (iResult == 0)
//               PrintError("Connection closing...");
//             else  {
//               PrintError("recv failed with error: %d", WSAGetLastError());
//               closesocket(ClientSocket);
//               WSACleanup();
//               return 1;
//             }
//           } else { count++; PrintError("No data..."); }
//         }
//
//         // shutdown the connection since we're done
//         iResult = shutdown(ClientSocket, SD_SEND);
//         if (iResult == SOCKET_ERROR) {
//           PrintError("shutdown failed with error: %d", WSAGetLastError());
//           closesocket(ClientSocket);
//           WSACleanup();
//           return 1;
//         }
//
//         // cleanup
//         closesocket(ClientSocket);
//         PrintError("Closed!");
//       }
//
//     }
//
//     WSACleanup();
//
//     return 0;
// }
//
// // status: 0x1 for read, 0x2 for write, 0x4 for exception
// int getStatus(const SOCKET a_socket, int status)
// {
//     // zero seconds, zero milliseconds. max time select call allowd to block
//     static timeval instantSpeedPlease = { 0, 16000 };
//     fd_set a = { 1, {a_socket} };
//     fd_set * read = ((status & 0x1) != 0) ? &a : NULL;
//     fd_set * write = ((status & 0x2) != 0) ? &a : NULL;
//     fd_set * except = ((status & 0x4) != 0) ? &a : NULL;
//     /*
//     select returns the number of ready socket handles in the fd_set structure, zero if the time limit expired, or SOCKET_ERROR if an error occurred. WSAGetLastError can be used to retrieve a specific error code.
//     */
//     int result = select(0, read, write, except, &instantSpeedPlease);
//     if (result == SOCKET_ERROR)
//     {
//         result = WSAGetLastError();
//     }
//     if (result < 0 || result > 3)
//     {
//         printf("select(read) error %d\n", result);
//         return SOCKET_ERROR;
//     }
//     return result;
// }
