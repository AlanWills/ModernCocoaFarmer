#pragma once

#include "Memory/Handle.h"

#include <string>
#include <vector>


namespace CelesteEngine
{
  class Screen;
  class GameObject;
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
        CelesteEngine::Handle<CelesteEngine::GameObject> m_interactableBuildingDialog;
        std::vector<CelesteEngine::Handle<CelesteEngine::GameObject>> m_buildings;

        static const std::string INTERACTABLE_BUILDINGS;
    };
  }
}