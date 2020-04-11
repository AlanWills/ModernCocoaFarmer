#pragma once

#include "Networking/SocketServer.h"

#include <thread>
#include <atomic>
#include <string>


namespace Celeste
{
  class SceneManager;
  class GameObject;
}

namespace MCF::Debugging
{
  class SceneBroadcaster
  {
    public:
      SceneBroadcaster();
      SceneBroadcaster(const SceneBroadcaster&) = delete;
      SceneBroadcaster(SceneBroadcaster&&) = default;
      ~SceneBroadcaster();

      SceneBroadcaster& operator=(const SceneBroadcaster&) = delete;

      void start();
      void update(const Celeste::SceneManager& sceneManager);
      void stop();

    private:
      void serializeGameObject(const Celeste::GameObject& gameObject, std::string& output) const;

      Networking::SocketServer m_server;
      std::string m_message;

      static const char m_fieldDelimiter;
      static const char m_vectorDelimiter;
      static const char* m_messageEndDelimiter;
  };
}