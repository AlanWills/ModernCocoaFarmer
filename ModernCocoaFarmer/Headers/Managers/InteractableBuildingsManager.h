#pragma once

#include "Objects/GameObject.h"


namespace CelesteEngine
{
  class Screen;
}

namespace MCF
{
  namespace Managers
  {
    class InteractableBuildingsManager
    {
      public:
        InteractableBuildingsManager();

        void initialize(const CelesteEngine::Handle<CelesteEngine::Screen>& screen);

      private:
        std::vector<CelesteEngine::Handle<CelesteEngine::GameObject>> m_buildings;
    };
  }
}