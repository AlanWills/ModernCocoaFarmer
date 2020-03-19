#pragma once

#include "UtilityHeaders/NetworkHeaders.h"


namespace MCF
{
  namespace Networking
  {
    class AutoFreeAddressInfo
    {
      public:
        AutoFreeAddressInfo(addrinfo* addressInfo) :
          m_addressInfo(addressInfo)
        {
        }

        ~AutoFreeAddressInfo()
        {
          freeaddrinfo(m_addressInfo);
        }

        AutoFreeAddressInfo(const AutoFreeAddressInfo&) = delete;
        AutoFreeAddressInfo& operator=(const AutoFreeAddressInfo&) = delete;

      private:
        addrinfo* m_addressInfo;
    };
  }
}