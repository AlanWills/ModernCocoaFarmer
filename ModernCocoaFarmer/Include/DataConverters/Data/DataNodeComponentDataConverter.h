#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "DataConverters/Data/Ports/PortDataConverter.h"


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

    protected:
      bool doConvertFromXML(const XMLElement* objectElement) override;
      void doSetValues(Celeste::Component& component) const override;
      void doSetValues(MCF::Data::DataNodeComponent& dataNodeComponent) const;

      const std::vector<std::unique_ptr<PortDataConverter>>& getInputPortDataConverters() const { return m_inputPortDataConverters; }
      const std::vector<std::unique_ptr<PortDataConverter>>& getOutputPortDataConverters() const { return m_outputPortDataConverters; }

    private:
      using Inherited = Celeste::ComponentDataConverter;

      std::vector<std::unique_ptr<PortDataConverter>> m_inputPortDataConverters;
      std::vector<std::unique_ptr<PortDataConverter>> m_outputPortDataConverters;
  };
}