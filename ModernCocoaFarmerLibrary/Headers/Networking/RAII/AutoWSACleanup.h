#pragma once

#include <winsock2.h>


namespace MCF
{
  namespace Networking
  {
    class AutoWSACleanup
    {
      public:
        AutoWSACleanup() { }

        ~AutoWSACleanup()
        {
          WSACleanup();
        }

        AutoWSACleanup(const AutoWSACleanup&) = delete;
        AutoWSACleanup& operator=(const AutoWSACleanup&) = delete;
    };
  }
}
