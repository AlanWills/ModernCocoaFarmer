#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"

#include <unordered_map>


namespace MCF::Data
{
  class DataSystem;
}

namespace MCF::Data::Communication
{
  class DataObjectKey : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(DataObjectKey, DataSystem, MCFLibraryDllExport);

    public:
      void addSubKey(const std::string& subPath);

      static const std::string ROOT_KEY_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onRootKeyPortChanged(Persistence::Data&& newValue);

      InputPort& m_rootKeyPort;
      std::unordered_map<std::string, std::reference_wrapper<OutputPort>> m_subKeyPorts;
  };
}