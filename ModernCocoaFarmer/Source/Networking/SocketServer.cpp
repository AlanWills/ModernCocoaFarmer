#include "Networking/SocketServer.h"

#include "UtilityHeaders/NetworkingHeaders.h"
#include "Networking/RAII/AutoWSACleanup.h"
#include "Networking/RAII/AutoFreeAddressInfo.h"
#include "Networking/RAII/AutoCloseSocket.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>

#define DEFAULT_BUFLEN 512


namespace MCF
{
  namespace Networking
  {
    //------------------------------------------------------------------------------------------------
    void SocketServer::Connect(int port)
    {
      AutoWSACleanup wsaCleanup;

      WSADATA wsaData;
      int iResult;

      SOCKET ListenSocket = INVALID_SOCKET;
      SOCKET ClientSocket = INVALID_SOCKET;

      struct addrinfo* result = NULL;
      struct addrinfo hints;

      int iSendResult;
      char recvbuf[DEFAULT_BUFLEN];
      int recvbuflen = DEFAULT_BUFLEN;

      // Initialize Winsock
      iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
      if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
      }

      ZeroMemory(&hints, sizeof(hints));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_TCP;
      hints.ai_flags = AI_PASSIVE;

      // Resolve the server address and port
      iResult = getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &result);
      if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
      }

      AutoFreeAddressInfo freeAddressInfo(result);

      // Create a SOCKET for connecting to server
      ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
      if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
      }

      AutoCloseSocket closeListenSocket(ListenSocket);

      // Setup the TCP listening socket
      iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
      if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
      }

      iResult = listen(ListenSocket, SOMAXCONN);
      if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
      }

      // Accept a client socket
      ClientSocket = accept(ListenSocket, NULL, NULL);
      if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
      }

      AutoCloseSocket closeClientSocket(ClientSocket);

      // Receive until the peer shuts down the connection
      do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
          printf("Bytes received: %d\n", iResult);

          std::string result;
          result.reserve(iResult);

          for (int i = 0; i < iResult; ++i)
          {
            result.push_back(recvbuf[i]);
          }
          printf("Message received: %s\n", result.c_str());

          // Echo the buffer back to the sender
          iSendResult = send(ClientSocket, recvbuf, iResult, 0);
          if (iSendResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
          }
          printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
          printf("Connection closing...\n");
        else {
          printf("recv failed with error: %d\n", WSAGetLastError());
        }

      } while (iResult > 0);

      // shutdown the connection since we're done
      iResult = shutdown(ClientSocket, SD_SEND);
      if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
      }
    }
  }
}