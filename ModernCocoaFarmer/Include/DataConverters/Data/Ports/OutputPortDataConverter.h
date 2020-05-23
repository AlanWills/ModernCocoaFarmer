#pragma once

#include "DataConverters/Data/Ports/PortDataConverter.h"
#include "Data/Ports/OutputPort.h"


namespace MCF::DataConverters::Data
{
  class OutputPortBaseDataConverter : public PortDataConverter
  {
    public:
      OutputPortBaseDataConverter(const std::string& name);

      const std::vector<std::string>& getConnectionNames() const { return m_connectionNames; }

      static const char* const CONNECTION_ELEMENT_NAME;

    protected:
      bool doConvertFromXML(const XMLElement* objectElement) override;

    private:
      using Inherited = PortDataConverter;

      std::vector<std::string> m_connectionNames;
  };
}