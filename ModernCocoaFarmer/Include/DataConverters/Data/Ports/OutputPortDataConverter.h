#pragma once

#include "DataConverters/DataConverter.h"


namespace MCF::DataConverters::Data
{
  class OutputPortDataConverter : public Celeste::DataConverter
  {
    public:
      OutputPortDataConverter();

      const std::string& getPortName() const { return m_portName.getValue(); }
      const std::vector<std::string>& getConnectionNames() const { return m_connectionNames; }

      static const char* const PORT_NAME_ATTRIBUTE_NAME;
      static const char* const CONNECTION_ELEMENT_NAME;

    protected:
      bool doConvertFromXML(const XMLElement* objectElement) override;

    private:
      using Inherited = Celeste::DataConverter;

      Celeste::XML::ReferenceAttribute<std::string>& m_portName;
      std::vector<std::string> m_connectionNames;
  };
}