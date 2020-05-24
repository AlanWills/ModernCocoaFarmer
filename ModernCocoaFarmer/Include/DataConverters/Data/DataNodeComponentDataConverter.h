#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "DataConverters/Data/Ports/OutputPortDataConverter.h"


namespace MCF::Data
{
  class DataNodeComponent;
}

namespace MCF::DataConverters::Data
{
  class DataNodeComponentDataConverter : public Celeste::ComponentDataConverter
  {
    public:
      DataNodeComponentDataConverter(const std::string& elementName);

      const std::string& getGuid() const { return m_guid.getValue(); }

      MCFLibraryDllExport static const char* const GUID_ATTRIBUTE_NAME;

    protected:
      bool doConvertFromXML(const XMLElement* objectElement) override;
      void doSetValues(Celeste::Component& component) const override;
      void doSetValues(MCF::Data::DataNodeComponent& dataNodeComponent) const;

    private:
      using Inherited = Celeste::ComponentDataConverter;

      Celeste::XML::ReferenceAttribute<std::string>& m_guid;

      std::vector<std::unique_ptr<OutputPortDataConverter>> m_outputPortDataConverters;
  };
}