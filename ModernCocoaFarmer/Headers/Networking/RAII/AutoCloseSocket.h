#pragma once

#include "UtilityHeaders/NetworkHeaders.h"


namespace MCF
{
  namespace Networking
  {
    class AutoCloseSocket
    {
    public:
      AutoCloseSocket(SOCKET socket) :
        m_socket(socket)
      {
      }

      ~AutoCloseSocket()
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