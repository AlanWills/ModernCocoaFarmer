#pragma once

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
      PortDataConverter(const std::string& name);

      const std::string& getPortName() const { return m_portName.getValue(); }

      static const char* const PORT_NAME_ATTRIBUTE_NAME;

    private:
      using Inherited = Celeste::DataConverter;

      Celeste::XML::ReferenceAttribute<std::string>& m_portName;
  };
}