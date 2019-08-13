#include "Networking/SocketServer.h"

#include "UtilityHeaders/NetworkingHeaders.h"
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
      m_connected(false),
      m_connectingThread(),
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
      SOCKET ListenSocket = INVALID_SOCKET;

      struct addrinfo* result = NULL;
      struct addrinfo hints;

      ZeroMemory(&hints, sizeof(hints));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_TCP;
      hints.ai_flags = AI_PASSIVE;

      // Resolve the server address and port
      int iResult = getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &result);
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

      m_connected = true;
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::connectAsync(int port)
    {
      void(SocketServer::*connectFunc)(int) = &SocketServer::connect;
      m_connectingThread.swap(std::thread(connectFunc, this, port));
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::connectAsync(int port, const OnDataReceivedCallback& onDataReceivedCallback)
    {
      m_onDataReceivedCallback = onDataReceivedCallback;

      connectAsync(port);
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::receiveAsync()
    {
      if (!m_connected)
      {
        ASSERT_FAIL();
        return;
      }
       
      m_isReceiving = true;
      m_receiveThread.swap(std::thread(&SocketServer::continuouslyReceiveData, this));
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::continuouslyReceiveData()
    {
      // In the future need to handle messages bigger than 512 bytes
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
      if (!m_connected)
      {
        ASSERT_FAIL();
        return;
      }

      if (!m_isSending)
      {
        m_isSending = true;
        m_sendThread.swap(std::thread(&SocketServer::continuouslySendData, this));
      }

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
      if (m_connected)
      {
        // shutdown the connection since we're done
        int iResult = shutdown(m_clientSocket, SD_SEND);
        ASSERT(iResult != SOCKET_ERROR);

        closesocket(m_clientSocket);
      }

      m_connected = false;
      m_isReceiving = false;
      m_isSending = false;

      if (m_connectingThread.joinable())
      {
        m_connectingThread.join();
      }

      if (m_receiveThread.joinable())
      {
        m_receiveThread.join();
      }

      if (m_sendThread.joinable())
      {
        m_sendThread.join();
      }
    }
  }
}