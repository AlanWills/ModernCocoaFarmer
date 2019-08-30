#pragma once

#include "MCFLibraryDllExport.h"
#include "Memory/Handle.h"

#include <string>
#include <memory>


namespace CelesteEngine
{
  class Screen;

  namespace Resources
  {
    class Prefab;
  }
}

namespace MCF
{
  namespace Buildings
  {
    class Building;
  }

  namespace UI
  {
    class MCFLibraryDllExport InteractableBuildingDialog
    {
      public:
        InteractableBuildingDialog();

        void initialize();
        void show(
          const CelesteEngine::Handle<CelesteEngine::Screen>& screen, 
          const std::unique_ptr<Buildings::Building>& building);

        static const std::string m_dialogPrefabPath;
        static const std::string TITLE_TEXT_NAME;
        static const std::string DESCRIPTION_TEXT_NAME;
        static const std::string CLOSE_BUTTON_NAME;

      private:
        CelesteEngine::Handle<CelesteEngine::Resources::Prefab> m_dialogPrefab;
    };
  }
}