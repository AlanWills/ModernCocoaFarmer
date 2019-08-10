#include "Networking/SocketServer.h"

#include "UtilityHeaders/NetworkingHeaders.h"
#include "Networking/RAII/AutoWSACleanup.h"
#include "Networking/RAII/AutoFreeAddressInfo.h"
#include "Networking/RAII/AutoCloseSocket.h"
#include "Debug/Debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>


namespace MCF
{
  namespace Networking
  {
    //------------------------------------------------------------------------------------------------
    SocketServer::SocketServer() :
      m_isReceiving(false),
      m_receiveThread(),
      m_isSending(false),
      m_sendQueueLock(),
      m_sendThread(),
      m_sendQueue(),
      m_clientSocket()
    {
    }

    //------------------------------------------------------------------------------------------------
    SocketServer::~SocketServer()
    {
      m_isReceiving = false;
      m_isSending = false;
      m_receiveThread.join();
      m_sendThread.join();

      disconnect();
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::connect(int port, const SocketServer::OnDataReceivedCallback& onDataReceivedCallback)
    {
      m_onDataReceivedCallback = onDataReceivedCallback;

      connect(port);
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::connect(int port)
    {
      AutoWSACleanup wsaCleanup;

      WSADATA wsaData;
      int iResult;

      SOCKET ListenSocket = INVALID_SOCKET;

      struct addrinfo* result = NULL;
      struct addrinfo hints;

      int iSendResult;

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
      m_clientSocket = accept(ListenSocket, NULL, NULL);
      if (m_clientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
      }

      m_isSending = true;
      m_sendThread.swap(std::thread(&SocketServer::continuouslySendData, this));
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::receiveAsync()
    {
      m_isReceiving = true;

      const int bufferLength = 512;
      char receiveBuffer[bufferLength];

      while (m_isReceiving)
      {
        int received = recv(m_clientSocket, receiveBuffer, bufferLength, 0);

        if (received > 0)
        {
          if (m_onDataReceivedCallback)
          {
            m_onDataReceivedCallback(receiveBuffer, received);
          }
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::sendAsync(const std::string& message)
    {
      std::lock_guard<std::mutex> sendQueueGuard(m_sendQueueLock);
      m_sendQueue.push(message);
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::continuouslySendData()
    {
      std::string message;

      while (m_isSending)
      {
        bool hasMessage = false;

        // Scope to remove guard as quickly as possible
        {
          std::lock_guard<std::mutex> sendQueueGuard(m_sendQueueLock);

          if (!m_sendQueue.empty())
          {
            message.assign(m_sendQueue.front());
            m_sendQueue.pop();
            hasMessage = true;
          }
        }

        if (hasMessage)
        {
          send(m_clientSocket, message.c_str(), message.size(), 0);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::disconnect()
    {
      // shutdown the connection since we're done
      int iResult = shutdown(m_clientSocket, SD_SEND);
      ASSERT(iResult != SOCKET_ERROR);

      closesocket(m_clientSocket);
    }
  }
}