#pragma once

#include "UtilityHeaders/NetworkingHeaders.h"

#include <functional>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>


namespace MCF
{
  namespace Networking
  {
    class SocketServer
    {
      public:
        using OnDataReceivedCallback = std::function<void(const char* receivedData, int numReceivedBytes)>;

        SocketServer();
        ~SocketServer();

        bool isConnecting() const { return m_connecting; }
        bool isConnected() const { return m_connected; }

        void connect(int port);
        void connectAsync(int port);

        void setOnDataReceived(const OnDataReceivedCallback& onDataReceived) { m_onDataReceivedCallback = onDataReceived; }

        void receiveAsync();
        void sendAsync(const std::string& message);

        void disconnect();

      private:
        void continuouslySendData();
        void continuouslyReceiveData();

        OnDataReceivedCallback m_onDataReceivedCallback;
        
        std::atomic<bool> m_connecting;
        std::atomic<bool> m_connected;
        std::thread m_connectingThread;

        std::atomic<bool> m_isReceiving;
        std::thread m_receiveThread;

        std::atomic<bool> m_isSending;
        std::mutex m_sendQueueLock;
        std::thread m_sendThread;
        std::queue<std::string> m_sendQueue;

        SOCKET m_clientSocket;
    };
  }
}