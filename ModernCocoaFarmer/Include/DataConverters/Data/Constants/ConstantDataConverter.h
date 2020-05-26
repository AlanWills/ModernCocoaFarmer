#pragma once

#include "MCFLibraryDllExport.h"
#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "Persistence/Data.h"


namespace MCF::Data::Constants
{
  class Constant;
}

namespace MCF::DataConverters::Data::Constants
{
  class ConstantDataConverter : public DataNodeComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ConstantDataConverter, MCF::Data::Constants::Constant, MCFLibraryDllExport);

    public:
      size_t getType() const { return m_type.getValue(); }
      const Persistence::Data& getValue() const { return m_value; }

      static const char* const TYPE_ATTRIBUTE_NAME;
      static const char* const VALUE_ATTRIBUTE_NAME;

    protected:
      bool doConvertFromXML(const tinyxml2::XMLElement* element) override;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ValueAttribute<size_t>& m_type;
      Persistence::Data m_value;
  };
}