#include "Networking/NetworkUtils.h"

#include "curlpp/curl_easy.h"
#include "curlpp/curl_exception.h"

#include <future>


namespace MCF
{
  namespace Networking
  {
    //------------------------------------------------------------------------------------------------
    void sendRequest(const std::string& url, unsigned int port, const std::string& content)
    {
      try
      {
        std::stringstream str;
        curl::curl_ios<std::stringstream> writer(str);
        curl::curl_easy easy(writer);
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Expect:");  // Disables waiting for confirmation before sending data - this was causing communication problems, but may be necessary in the future
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

        easy.add<CURLOPT_URL>(url.data());
        easy.add<CURLOPT_VERBOSE>(true);
        easy.add<CURLOPT_HTTPHEADER>(headers);
        easy.add<CURLOPT_POSTFIELDS>(content.c_str());
        easy.add<CURLOPT_POSTFIELDSIZE>(content.size());
        easy.add<CURLOPT_PORT>(port);
        easy.add<CURLOPT_CONNECTTIMEOUT>(10);
        easy.add<CURLOPT_TIMEOUT>(10);

        easy.perform();
      }
      catch (curl::curl_easy_exception const& error)
      {
        auto errors = error.get_traceback();
        error.print_traceback();
        error.clear_traceback();
      }
    }
  }
}