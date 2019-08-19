#pragma once

#include "Memory/Handle.h"

#include <string>


namespace CelesteEngine
{
  class Screen;
  class GameObject;
}

namespace MCF
{
  namespace UI
  {
    class InteractableBuildingDialog
    {
      public:
        void initialize(const CelesteEngine::Handle<CelesteEngine::Screen>& screen);

      private:
        CelesteEngine::Handle<CelesteEngine::GameObject> m_gameObject;

        static const std::string INTERACTABLE_BUILDING_DIALOG;
    };
  }
}