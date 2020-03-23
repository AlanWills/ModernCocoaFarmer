#include "Networking/NetworkUtils.h"
#include "Debug/Log.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <string>
#include <sstream>
#include <iostream>


namespace MCF::Networking
{
  //------------------------------------------------------------------------------------------------
  void sendRequest(const std::string& url, unsigned int port, const std::string& content)
  {
    curlpp::Cleanup myCleanup;

    try
    {
      //headers = curl_slist_append(headers, "Expect:");  // Disables waiting for confirmation before sending data - this was causing communication problems, but may be necessary in the future
      //headers = curl_slist_append(headers, "Content-Type: application/octet-stream");
      //easy.add<CURLOPT_HTTPHEADER>(headers);
      
      curlpp::Easy myRequest;

      myRequest.setOpt(curlpp::options::Url(url));
      myRequest.setOpt(curlpp::options::Verbose(true));
      myRequest.setOpt(curlpp::options::Verbose(true));
      myRequest.setOpt(curlpp::options::PostFieldSize(static_cast<long>(content.size())));
      myRequest.setOpt(curlpp::options::PostFields(content));
      myRequest.setOpt(curlpp::options::Port(port));
      myRequest.setOpt(curlpp::options::ConnectTimeout(10));
      myRequest.setOpt(curlpp::options::Timeout(10));

      myRequest.perform();

      //std::ostringstream os;
      //os << myRequest;
    }
    catch (curlpp::RuntimeError& e)
    {
      LOG(e.what());
    }
    catch (curlpp::LogicError& e)
    {
      LOG(e.what());
    }
  }
}