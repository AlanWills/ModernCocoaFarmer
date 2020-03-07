#include "Debugging/SceneBroadcaster.h"
#include "Networking/NetworkUtils.h"
#include "Objects/GameObject.h"
#include "Scene/SceneManager.h"

using namespace Celeste;


namespace MCF::Debugging
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
    ASSERT(!m_server.isConnected());
    ASSERT(!m_server.isConnecting());
  }

  //------------------------------------------------------------------------------------------------
  void SceneBroadcaster::start()
  {
    m_server.connectAsync(13000);
  }

  //------------------------------------------------------------------------------------------------
  void SceneBroadcaster::update(const SceneManager& sceneManager)
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

    auto current = std::chrono::system_clock::now();

    // Reset the string
    m_message.clear();

    for (const GameObject& gameObject : sceneManager.getRootGameObjects())
    {
      // Start delimiter for content
      m_message.append("[[");

      // Add game object information
      serializeGameObject(gameObject, m_message);

      // End delimiter for content
      m_message.append("]]");
    }

    m_message.append(m_messageEndDelimiter);
    m_server.sendAsync(m_message);
  }

  //------------------------------------------------------------------------------------------------
  void SceneBroadcaster::serializeGameObject(const GameObject& gameObject, std::string& output) const
  {
    output.append(deinternString(gameObject.getName()));
    output.push_back(m_fieldDelimiter);

    observer_ptr<const Transform> transform = gameObject.getTransform();

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
    for (const GameObject* child : gameObject)
    {
      serializeGameObject(*child, output);
    }
  }

  //------------------------------------------------------------------------------------------------
  void SceneBroadcaster::stop()
  {
    m_server.disconnect();
  }
}