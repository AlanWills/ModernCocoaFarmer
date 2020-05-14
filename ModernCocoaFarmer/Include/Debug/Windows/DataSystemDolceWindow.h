#pragma once

#include "MCFLibraryDllExport.h"
#include "Dolce/Windows/LuaDolceWindow.h"


namespace MCF::Persistence
{
  class DataSystem;
}

namespace MCF::Debug
{
  class DataSystemDolceWindow : public Dolce::DolceWindow
  {
    public:
      MCFLibraryDllExport DataSystemDolceWindow(Persistence::DataSystem& dataSystem);

      void render() override;

    private:
      using Inherited = Dolce::DolceWindow;

      Persistence::DataSystem& m_dataSystem;
  };
}