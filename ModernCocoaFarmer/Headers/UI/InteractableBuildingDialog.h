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

        static const std::string INTERACTABLE_BUILDING_DIALOG;

      private:
        CelesteEngine::Handle<CelesteEngine::GameObject> m_gameObject;
    };
  }
}