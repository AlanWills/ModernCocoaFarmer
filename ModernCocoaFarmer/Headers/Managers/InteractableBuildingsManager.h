#pragma once

#include "Objects/GameObject.h"

#include <string>


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
        Handle<GameObject> m_interactableBuildingDialog;
        std::vector<CelesteEngine::Handle<CelesteEngine::GameObject>> m_buildings;

        static const std::string INTERACTABE_BUILDINGS;
    };
  }
}