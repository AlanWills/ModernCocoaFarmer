#pragma once

#include "UtilityHeaders/NetworkingHeaders.h"


namespace MCF
{
  namespace Networking
  {
    class AutoCloseSocket
    {
      public:
        Socket(SOCKET socket) :
          m_socket(socket)
        {
        }

        ~Socket()
        {
          closesocket(m_socket);
        }

        AutoCloseSocket(const AutoCloseSocket&) = delete;
        AutoCloseSocket& operator=(const AutoCloseSocket&) = delete;

      private:
        SOCKET m_socket;
    };
  }
}