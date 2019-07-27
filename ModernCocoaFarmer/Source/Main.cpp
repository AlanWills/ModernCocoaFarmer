#include "Game/Game.h"
#include "Lua/ScriptCommands/MCFScriptCommands.h"
#include "UtilityHeaders/PlatformHeaders.h"

#include "curlpp/curl_easy.h"
#include "curlpp/curl_form.h"
#include "curlpp/curl_ios.h"
#include "curlpp/curl_exception.h"
#include "curlpp/curl_multi.h"

// Disables console window
#if WINDOWS && !defined(__CYGWIN__)
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif


void get_response(std::string url)
{
    while (true)
    {
      try
      {
        std::stringstream str;
        curl::curl_ios<std::stringstream> writer(str);
        curl::curl_easy easy(writer);
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

        easy.add<CURLOPT_URL>(url.data());
        easy.add<CURLOPT_VERBOSE>(true);
        easy.add<CURLOPT_HTTPHEADER>(headers);
        easy.add<CURLOPT_POSTFIELDS>("abcd");
        easy.add<CURLOPT_POSTFIELDSIZE>(5);
        easy.add<CURLOPT_PORT>(13000);
        easy.add<CURLOPT_CONNECTTIMEOUT>(10);
        easy.add<CURLOPT_TIMEOUT>(10);

        easy.perform();
      
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
      catch (curl::curl_easy_exception const& error)
      {
        auto errors = error.get_traceback();
        error.print_traceback();

        if (error.get_code() != CURLE_OPERATION_TIMEDOUT)
        {
          return;
        }
      }
  }
}

int main()
{
  using namespace std::string_literals;

  auto url = "http://localhost/";
  get_response(url);

  return 0;
}

// The MAIN function, from here we start the application and run the game loop
//int main()
//{
//  // Set up game specific script commands
//  MCF::Lua::MCFScriptCommands::initialize();
//
//  CelesteEngine::Game* game = new CelesteEngine::Game();
//  game->run();
//  
//  return 0;
//}