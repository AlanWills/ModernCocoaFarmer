#include "Debugging/SceneBroadcaster.h"
#include "Networking/NetworkUtils.h"

#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"

using namespace CelesteEngine;


namespace MCF
{
  namespace Debugging
  {
    //------------------------------------------------------------------------------------------------
    SceneBroadcaster::SceneBroadcaster() :
      m_isBroadcasting(false),
      m_communicationThread()
    {
    }

    //------------------------------------------------------------------------------------------------
    SceneBroadcaster::~SceneBroadcaster()
    {
      m_isBroadcasting = false;
      m_communicationThread.join();
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::startBroadcasting(const ScreenManager& screenManager)
    {
      m_isBroadcasting = true;
      m_communicationThread.swap(std::thread(&SceneBroadcaster::continuallySendData, this, std::ref(screenManager)));
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::continuallySendData(const ScreenManager& screenManager)
    {
      std::string str;
      str.reserve(4096);

      while (m_isBroadcasting)
      {
        str.clear();

        for (const Screen* screen : screenManager)
        {
          str.append(deinternString(screen->getName()));
          str.push_back('\n');

          for (const GameObject* gameObject : *screen)
          {
            str.append(deinternString(gameObject->getName()));
            str.push_back('\n');
          }
        }

        Networking::sendRequest("http://localhost/", 13000, str);
      }
    }
  }
}