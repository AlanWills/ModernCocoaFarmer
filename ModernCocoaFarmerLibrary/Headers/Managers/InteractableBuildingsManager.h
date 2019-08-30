#pragma once

#include "Memory/Handle.h"

#include <string>
#include <vector>
#include <memory>


namespace CelesteEngine
{
  class Screen;
  class GameObject;
}

namespace MCF
{
  namespace UI
  {
    class InteractableBuildingDialog;
  }

  namespace Managers
  {
    class InteractableBuildingsManager
    {
      public:
        InteractableBuildingsManager();
        ~InteractableBuildingsManager();

        void initialize(const CelesteEngine::Handle<CelesteEngine::Screen>& screen);

      private:
        std::unique_ptr<UI::InteractableBuildingDialog> m_interactableBuildingDialog;
        std::vector<CelesteEngine::Handle<CelesteEngine::GameObject>> m_buildings;

        static const std::string INTERACTABLE_BUILDINGS_NAME;
    };
  }
}