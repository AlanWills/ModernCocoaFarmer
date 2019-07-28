#pragma once

#include <string>


namespace MCF
{
  namespace Networking
  {
    void sendRequest(const std::string& url, unsigned int port, const std::string& content);
  }
}