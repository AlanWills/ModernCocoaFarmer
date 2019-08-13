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
    const char SceneBroadcaster::m_fieldDelimiter = ',';
    const char SceneBroadcaster::m_vectorDelimiter = '/';
    const char* SceneBroadcaster::m_messageEndDelimiter = "END";

    //------------------------------------------------------------------------------------------------
    SceneBroadcaster::SceneBroadcaster() :
      m_message()
    {
      m_message.reserve(4096);
    }

    //------------------------------------------------------------------------------------------------
    SceneBroadcaster::~SceneBroadcaster()
    {
      m_server.disconnect();
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::start(const ScreenManager& screenManager)
    {
      m_server.connectAsync(13000);
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::update(const ScreenManager& screenManager)
    {
      // This should be checking the socket is connected, not the server
      if (!m_server.isConnected())
      {
        if (!m_server.isConnecting())
        {
          m_server.disconnect();
          m_server.connectAsync(13000);
        }

        return;
      }

      std::queue<const GameObject*> gameObjects;

      // Reset the string
      m_message.clear();

      for (const Screen* screen : screenManager)
      {
        // Should be empty from previous screen because of complete traversal
        ASSERT(gameObjects.empty());

        // Start delimiter for content
        m_message.append("[[");

        // Add screen name
        m_message.append(deinternString(screen->getName()));
        m_message.push_back(m_fieldDelimiter);

        // And number of root children
        m_message.append(std::to_string(screen->getScreenRoot()->getChildCount()));
        m_message.push_back(m_fieldDelimiter);

        Transform* root = const_cast<Transform*>(screen->getScreenRoot());

        // Then serialize each child using left side tree traversal
        for (size_t childIndex = 0, n = root->getChildCount(); childIndex < n; ++childIndex)
        {
          // Yeah this isn't great - we need api for getting const children
          serializeGameObject(const_cast<GameObject&>(*root->getChildTransform(childIndex)->getGameObject()), m_message);
        }

        // End delimiter for content
        m_message.append("]]");
      }

      m_message.append(m_messageEndDelimiter);

      m_server.sendAsync(m_message);
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::continuallySendData(const ScreenManager& screenManager)
    {
      m_server.connect(13000);

      std::queue<const GameObject*> gameObjects;

      std::string output;
      output.reserve(4096);

      while (false)
      {
        // Reset the string
        output.clear();

        for (const Screen* screen : screenManager)
        {
          // Should be empty from previous screen because of complete traversal
          ASSERT(gameObjects.empty());

          // Start delimiter for content
          output.append("[[");

          // Add screen name
          output.append(deinternString(screen->getName()));
          output.push_back(m_fieldDelimiter);

          // And number of root children
          output.append(std::to_string(screen->getScreenRoot()->getChildCount()));
          output.push_back(m_fieldDelimiter);

          Transform* root = const_cast<Transform*>(screen->getScreenRoot());

          // Then serialize each child using left side tree traversal
          for (size_t childIndex = 0, n = root->getChildCount(); childIndex < n; ++childIndex)
          {
            // Yeah this isn't great - we need api for getting const children
            serializeGameObject(const_cast<GameObject&>(*root->getChildTransform(childIndex)->getGameObject()), output);
          }

          // End delimiter for content
          output.append("]]");
        }

        output.append(m_messageEndDelimiter);

        m_server.sendAsync(output);
      }
    }

    //------------------------------------------------------------------------------------------------
    void SceneBroadcaster::serializeGameObject(GameObject& gameObject, std::string& output) const
    {
      output.append(deinternString(gameObject.getName()));
      output.push_back(m_fieldDelimiter);

      Handle<Transform> transform = gameObject.getTransform();

      // Local Translation
      {
        const glm::vec3& localTranslation = transform->getTranslation();
        output.append(std::to_string(localTranslation.x));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(localTranslation.y));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(localTranslation.z));
        output.push_back(m_fieldDelimiter);
      }

      // Local Rotation
      {
        output.append(std::to_string(transform->getRotation()));
        output.push_back(m_fieldDelimiter);
      }

      // Local Scale 
      {
        const glm::vec3& localScale = transform->getScale();
        output.append(std::to_string(localScale.x));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(localScale.y));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(localScale.z));
        output.push_back(m_fieldDelimiter);
      }

      // World Translation
      {
        glm::vec3 worldTranslation = transform->getWorldTranslation();
        output.append(std::to_string(worldTranslation.x));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(worldTranslation.y));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(worldTranslation.z));
        output.push_back(m_fieldDelimiter);
      }

      // World Rotation
      {
        output.append(std::to_string(transform->getWorldRotation()));
        output.push_back(m_fieldDelimiter);
      }

      // World Scale 
      {
        const glm::vec3& worldScale = transform->getWorldScale();
        output.append(std::to_string(worldScale.x));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(worldScale.y));
        output.push_back(m_vectorDelimiter);
        output.append(std::to_string(worldScale.z));
        output.push_back(m_fieldDelimiter);
      }

      output.append(std::to_string(gameObject.getChildCount()));
      output.push_back(m_fieldDelimiter);

      // Then serialize each child using left side tree traversal
      for (size_t childIndex = 0, n = gameObject.getChildCount(); childIndex < n; ++childIndex)
      {
        serializeGameObject(*gameObject.getChildGameObject(childIndex), output);
      }
    }
  }
}