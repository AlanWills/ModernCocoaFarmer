#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/DataConverter.h"


namespace MCF::Data
{
  class Port;
}

namespace MCF::DataConverters::Data
{
  class PortDataConverter : public Celeste::DataConverter
  {
    public:
      PortDataConverter();

      const std::string& getPortName() const { return m_portName.getValue(); }
      const std::string& getGuid() const { return m_guid.getValue(); }
      const std::vector<std::string>& getConnectionNames() const { return m_connectionNames; }

      void setValues(MCF::Data::Port& port) const;

      MCFLibraryDllExport static const char* const PORT_NAME_ATTRIBUTE_NAME;
      MCFLibraryDllExport static const char* const GUID_ATTRIBUTE_NAME;
      MCFLibraryDllExport static const char* const CONNECTION_ELEMENT_NAME;

    protected:
      bool doConvertFromXML(const XMLElement* objectElement) override;

    private:
      using Inherited = Celeste::DataConverter;

      Celeste::XML::ReferenceAttribute<std::string>& m_portName;
      Celeste::XML::ReferenceAttribute<std::string>& m_guid;
      
      std::vector<std::string> m_connectionNames;
  };
}