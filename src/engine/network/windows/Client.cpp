#include "network/Client.h"
#include "Log.h"
#include "network/constants.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

int macro::network::Client::run() {
  WSADATA wsaData;
  SOCKET sendingSocket;
  SOCKADDR_IN receiverAddr, srcInfo;
  char sendBuf[MACRO_NETWORK_DEFAULT_BUFLEN] = "coucou";
  int len;
  int totalBytesSent;

  // Initialize Winsock version 2.2
  if( WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
    PrintError("Client: WSAStartup failed with error: ", WSAGetLastError());

    WSACleanup();
    return -1;
  }

  PrintLog("Client: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);

  // Create a new socket to receive datagrams on.
  sendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (sendingSocket == INVALID_SOCKET) {
    PrintError("Client: Error at socket(): ", WSAGetLastError());

    WSACleanup();
    return -1;
  }

  PrintLog("Client: socket() is OK!\n");

  receiverAddr.sin_family = AF_INET;
  receiverAddr.sin_port = htons(MACRO_NETWORK_DEFAULT_PORT);
  receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Send data packages to the receiver(Server).
  while (true) {
    //Print user's input and a progress message
    PrintLog("Client: Data to be sent: ", sendBuf);
    PrintLog("Client: Sending data...");

    //Send message to receiver(Server)
    totalBytesSent = sendto(sendingSocket, sendBuf, MACRO_NETWORK_DEFAULT_BUFLEN, 0, (SOCKADDR *)&receiverAddr, sizeof(receiverAddr));
    //Print success message
    PrintLog("Client: sendto() looks OK!");

    Sleep(1000);
  }

  // Allocate the required resources

  memset(&srcInfo, 0, sizeof(srcInfo));

  len = sizeof(srcInfo);

  getsockname(sendingSocket, (SOCKADDR *)&srcInfo, &len);
  PrintLog("Client: Sending IP(s) used: ", inet_ntoa(srcInfo.sin_addr));
  PrintLog("Client: Sending port used: ", htons(srcInfo.sin_port));

  // Print some info on the sender(Client) side...

  getpeername(sendingSocket, (SOCKADDR *)&receiverAddr, (int *)sizeof(receiverAddr));
  PrintLog("Client: Receiving IP used: ", inet_ntoa(receiverAddr.sin_addr));
  PrintLog("Client: Receiving port used: ", htons(receiverAddr.sin_port));
  PrintLog("Client: Total byte sent: ", totalBytesSent);

  // When your application is finished receiving datagrams close the socket.

  PrintLog("Client: Finished sending. Closing the sending socket...\n");

  if (closesocket(sendingSocket) != 0) {
    PrintError("Client: closesocket() failed! Error code: ", WSAGetLastError());
  }

  // When your application is finished call WSACleanup.

  PrintError("Client: Cleaning up...\n");

  if(WSACleanup() != 0) {
    PrintError("Client: WSACleanup() failed! Error code: ", WSAGetLastError());
  }

  return 0;
}
