#pragma once

#include "Memory/Handle.h"


namespace CelesteEngine
{
  class GameObject;
  class Screen;
}

namespace MCF
{
  namespace UI
  {
    CelesteEngine::Handle<CelesteEngine::GameObject> showInteractableBuildingDialog(const CelesteEngine::Handle<CelesteEngine::Screen>& screen);
  }
}