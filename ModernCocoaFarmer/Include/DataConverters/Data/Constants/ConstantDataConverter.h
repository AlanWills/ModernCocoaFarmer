#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"


namespace MCF::DataConverters::Data::Constants
{
  template <typename T>
  class ConstantDataConverter : public DataNodeComponentDataConverter
  {
    public:
      ConstantDataConverter(const std::string& elementName);

      T getValue() const { return m_value.getValue(); }

      static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ValueAttribute<T>& m_value;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  const char* const ConstantDataConverter<T>::VALUE_ATTRIBUTE_NAME("value");

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ConstantDataConverter<T>::ConstantDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_value(createValueAttribute<T>(VALUE_ATTRIBUTE_NAME, T(), Celeste::DeserializationRequirement::kRequired))
  {
  }
}