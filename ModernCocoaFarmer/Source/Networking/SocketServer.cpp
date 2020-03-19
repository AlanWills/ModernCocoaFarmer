#include "Networking/SocketServer.h"

#include "Networking/RAII/AutoFreeAddressInfo.h"
#include "Networking/RAII/AutoCloseSocket.h"
#include "Debug/Assert.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>


namespace MCF
{
  namespace Networking
  {
    //------------------------------------------------------------------------------------------------
    SocketServer::SocketServer() :
      m_connecting(false),
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
    void SocketServer::connectImpl(u_short port, const OnConnectedCallback& onConnected)
    {
      if (m_connecting)
      {
        return;
      }

      m_connecting = true;

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

      sockaddr_in clientService;
      clientService.sin_family = AF_INET;
      InetPton(AF_INET, (PCSTR)"127.0.0.1", &clientService.sin_addr.s_addr);
      clientService.sin_port = htons(port);

      // Setup the TCP listening socket
      iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
      if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
      }

      iResult = listen(ListenSocket, SOMAXCONN);
      if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
      }

      while (!m_connected && m_connecting)
      {
        timeval timeout = { 1, 0 };
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(ListenSocket, &fds);

        select(static_cast<int>(ListenSocket + 1), &fds, NULL, NULL, &timeout);

        if (FD_ISSET(ListenSocket, &fds))
        {
          m_clientSocket = accept(ListenSocket, NULL, NULL);
          ASSERT(m_clientSocket != INVALID_SOCKET);

          m_connected = true;
          m_connecting = false;

          if (onConnected)
          {
            onConnected();
          }
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::connectAsync(u_short port, const OnConnectedCallback& onConnected)
    {
      if (m_connecting)
      {
        return;
      }
      
      std::thread newConnectingThread(&SocketServer::connectImpl, this, port, onConnected);
      m_connectingThread.swap(newConnectingThread);
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

      std::thread newReceiveThread(&SocketServer::continuouslyReceiveData, this);
      m_receiveThread.swap(newReceiveThread);
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
        else
        {
          // Client has disconnected
          m_connected = false;
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

        std::thread newSendThread(&SocketServer::continuouslySendData, this);
        m_sendThread.swap(newSendThread);
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
          if (send(m_clientSocket, message.c_str(), static_cast<int>(message.size()), 0) == SOCKET_ERROR)
          {
            m_connected = false;
          }
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void SocketServer::disconnect()
    {
      if (m_connected)
      {
        // shutdown the connection since we're done
        shutdown(m_clientSocket, SD_SEND);
        closesocket(m_clientSocket);

        m_clientSocket = INVALID_SOCKET;
      }

      m_connecting = false;
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