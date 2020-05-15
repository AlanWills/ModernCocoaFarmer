#pragma once

#include "MCFLibraryDllExport.h"
#include "Dolce/Windows/LuaDolceWindow.h"
#include "CelesteStl/Memory/ObserverPtr.h"
#include "Persistence/DataSystem.h"

#include <map>


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

      struct DataSystemNode
      {
        DataSystemNode() :
          DataSystemNode("", nullptr, nullptr)
        {
        }

        DataSystemNode(
          const std::string& relativeKey, 
          observer_ptr<DataSystemNode> parent, 
          observer_ptr<Persistence::DataStore::Data> data) :
          m_relativeKey(relativeKey),
          m_parent(parent),
          m_data(data)
        {
        }

        std::string m_relativeKey;
        observer_ptr<DataSystemNode> m_parent;
        observer_ptr<Persistence::DataStore::Data> m_data;
        std::map<std::string, DataSystemNode> m_children;
      };

      void renderNode(DataSystemNode& dataSystemNode);
      std::string getFullKey(const DataSystemDolceWindow::DataSystemNode& dataSystemNode);

      Persistence::DataSystem& m_dataSystem;
      std::string m_searchString;
      DataSystemNode m_dataSystemRoot;
  };
}