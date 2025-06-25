#include "network/Client.h"
#define WIN32_LEAN_AND_MEAN

#include "Log.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int macro::network::Client::run() {

     WSADATA wsaData;
     SOCKET SendingSocket;
     SOCKADDR_IN ReceiverAddr, SrcInfo;
     int Port = 8888;
     int BufLength = 1024;
     char SendBuf[DEFAULT_BUFLEN] = "coucou";
     int len;
     int TotalByteSent;

     // Initialize Winsock version 2.2

     if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0){

          printf("Client: WSAStartup failed with error %ld\n", WSAGetLastError());

          // Clean up
          WSACleanup();

          // Exit with error
          return -1;
     }
     else{
          printf("Client: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);
     }


     // Create a new socket to receive datagrams on.

     SendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

     if (SendingSocket == INVALID_SOCKET){

          // Print error message
          printf("Client: Error at socket(): %ld\n", WSAGetLastError());

          // Clean up
          WSACleanup();

          // Exit with error
          return -1;
     }
     else{
          printf("Client: socket() is OK!\n");
     }



     /*Set up a SOCKADDR_IN structure that will identify who we
     will send datagrams to.
     For demonstration purposes, let's assume our receiver's IP address is 127.0.0.1
     and waiting for datagrams on port 5150.*/

     ReceiverAddr.sin_family = AF_INET;

     ReceiverAddr.sin_port = htons(Port);

     ReceiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");



     // Send data packages to the receiver(Server).
     do{
            //Print user's input and a progress message
            printf("Client: Data to be sent: %s\n", SendBuf);
            printf("Client: Sending data...\n");

            //Send message to receiver(Server)
            TotalByteSent = sendto(SendingSocket, SendBuf, BufLength, 0, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr));
            //Print success message
            printf("Client: sendto() looks OK!\n");

            Sleep(1000);

      /*Program is asking user for messages and sending the to Server,until you will close it.
      (You can replace while(1) with a condition to stop asking/sending messages.)*/
     }while(1);



     // Print some info on the receiver(Server) side...

     // Allocate the required resources

     memset(&SrcInfo, 0, sizeof(SrcInfo));

     len = sizeof(SrcInfo);

     getsockname(SendingSocket, (SOCKADDR *)&SrcInfo, &len);

     printf("Client: Sending IP(s) used: %s\n", inet_ntoa(SrcInfo.sin_addr));

     printf("Client: Sending port used: %d\n", htons(SrcInfo.sin_port));



     // Print some info on the sender(Client) side...

     getpeername(SendingSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));

     printf("Client: Receiving IP used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));

     printf("Client: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));

     printf("Client: Total byte sent: %d\n", TotalByteSent);



   // When your application is finished receiving datagrams close the socket.

   printf("Client: Finished sending. Closing the sending socket...\n");

   if (closesocket(SendingSocket) != 0){

        printf("Client: closesocket() failed! Error code: %ld\n", WSAGetLastError());
   }
   else{
        printf("Server: closesocket() is OK\n");
   }



   // When your application is finished call WSACleanup.

   printf("Client: Cleaning up...\n");

   if(WSACleanup() != 0){
        printf("Client: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
   }

   else{
        printf("Client: WSACleanup() is OK\n");
   }
   return 0;
}
//
//     WSADATA wsaData;
//     SOCKET ConnectSocket = INVALID_SOCKET;
//     struct addrinfo *result = NULL,
//                     *ptr = NULL,
//                     hints;
//     const char *sendbuf = "this is a test";
//     char recvbuf[DEFAULT_BUFLEN];
//     int iResult;
//     int recvbuflen = DEFAULT_BUFLEN;
//
//     // Initialize Winsock
//     iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//     if (iResult != 0) {
//         PrintError("WSAStartup failed with error: %d", iResult);
//         return 1;
//     }
//
//     ZeroMemory( &hints, sizeof(hints) );
//     hints.ai_family = AF_INET;
//     hints.ai_socktype = SOCK_DGRAM;
//     hints.ai_protocol = IPPROTO_UDP;
//
//     // Resolve the server address and port
//     iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
//     if ( iResult != 0 ) {
//         PrintError("getaddrinfo failed with error: %d", iResult);
//         WSACleanup();
//         return 1;
//     }
//
//     // Attempt to connect to an address until one succeeds
//     for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
//
//         // Create a SOCKET for connecting to server
//         ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
//             ptr->ai_protocol);
//         if (ConnectSocket == INVALID_SOCKET) {
//             PrintError("socket failed with error: %ld", WSAGetLastError());
//             WSACleanup();
//             return 1;
//         }
//
//         // Connect to server.
//         iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//         if (iResult == SOCKET_ERROR) {
//             closesocket(ConnectSocket);
//             ConnectSocket = INVALID_SOCKET;
//             continue;
//         }
//         break;
//     }
//
//     freeaddrinfo(result);
//
//     if (ConnectSocket == INVALID_SOCKET) {
//         PrintError("Unable to connect to server!");
//         WSACleanup();
//         return 1;
//     }
//
//
//     int i = 0;
//     while (i < 5) {
//       // Send an initial buffer
//       iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
//       PrintError("Bytes Sent: %ld", iResult);
//       if (iResult == SOCKET_ERROR) {
//         PrintError("send failed with error: %d", WSAGetLastError());
//         closesocket(ConnectSocket);
//         WSACleanup();
//         return 1;
//       }
//       i++;
//       Sleep(1000);
//     }
//
//     // shutdown the connection since no more data will be sent
//     iResult = shutdown(ConnectSocket, SD_SEND);
//     if (iResult == SOCKET_ERROR) {
//         PrintError("shutdown failed with error: %d", WSAGetLastError());
//         closesocket(ConnectSocket);
//         WSACleanup();
//         return 1;
//     }
//
//     // Receive until the peer closes the connection
//     do {
//
//         iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
//         if ( iResult > 0 )
//             PrintError("Bytes received: %d", iResult);
//         else if ( iResult == 0 )
//             PrintError("Connection closed");
//         else
//             PrintError("recv failed with error: %d", WSAGetLastError());
//
//     } while( iResult > 0 );
//
//     // cleanup
//     closesocket(ConnectSocket);
//     WSACleanup();
//
//     return 0;
// } 
