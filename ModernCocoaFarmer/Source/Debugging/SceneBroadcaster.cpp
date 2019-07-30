#include "Debugging/SceneBroadcaster.h"
#include "Networking/NetworkUtils.h"

#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"

#include "Objects/GameObject.h"

using namespace CelesteEngine;


namespace MCF
{
  namespace Debugging
  {
    char SceneBroadcaster::m_delimiter = ',';

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
    void SceneBroadcaster::continuallySendData(const ScreenManager& screenManager) const
    {
      std::queue<const GameObject*> gameObjects;

      std::string output;
      output.reserve(4096);

      while (m_isBroadcasting)
      {
        for (const Screen* screen : screenManager)
        {
          // Should be empty from previous screen because of complete traversal
          ASSERT(gameObjects.empty());

          // Reset the string
          output.clear();

          // Start delimiter for content
          output.append("[[");

          // Add screen name
          output.append(deinternString(screen->getName()));
          output.push_back(m_delimiter);

          // And number of root children
          output.append(std::to_string(screen->getScreenRoot()->getChildCount()));
          output.push_back(m_delimiter);

          Transform* root = const_cast<Transform*>(screen->getScreenRoot());

          // Then serialize each child using left side tree traversal
          for (size_t childIndex = 0, n = root->getChildCount(); childIndex < n; ++childIndex)
          {
            // Yeah this isn't great - we need api for getting const children
            serializeGameObject(const_cast<GameObject&>(*root->getChildTransform(childIndex)->getGameObject()), output);
          }

          // End delimiter for content
          output.append("]]");
          
          Networking::sendRequest("http://localhost/", 13000, output);

          // Only send one screen for now
          break;
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::serializeGameObject(GameObject& gameObject, std::string& output) const
    {
      output.append(deinternString(gameObject.getName()));
      output.push_back(m_delimiter);

      output.append(std::to_string(gameObject.getChildCount()));
      output.push_back(m_delimiter);

      // Then serialize each child using left side tree traversal
      for (size_t childIndex = 0, n = gameObject.getChildCount(); childIndex < n; ++childIndex)
      {
        serializeGameObject(*gameObject.getChildGameObject(childIndex), output);
      }
    }
  }
}