#pragma once

#include "DataConverters/Data/Ports/PortDataConverter.h"
#include "Data/Ports/InputPort.h"


namespace MCF::DataConverters::Data
{
  class InputPortBaseDataConverter : public PortDataConverter
  {
    public:
      InputPortBaseDataConverter(const std::string& name) : PortDataConverter(name) {}
      virtual ~InputPortBaseDataConverter() = default;

      virtual void setValues(MCF::Data::InputPortBase& inputPort) const = 0;
  };

  template <typename T>
  class InputPortDataConverter : public InputPortBaseDataConverter
  {
    public:
      InputPortDataConverter(const std::string& name);

      T getValue() const { return m_value.getValue(); }

      void setValues(MCF::Data::InputPortBase& inputPort) const override
      {
        static_cast<MCF::Data::InputPort<T>&>(inputPort).setValue(getValue());
      }

      static const char* const VALUE_ATTRIBUTE_NAME;

    private:
      using Inherited = InputPortBaseDataConverter;

      Celeste::XML::ValueAttribute<T>& m_value;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  const char* const InputPortDataConverter<T>::VALUE_ATTRIBUTE_NAME = "value";

  //------------------------------------------------------------------------------------------------
  template <typename T>
  InputPortDataConverter<T>::InputPortDataConverter(const std::string& name) :
    Inherited(name),
    m_value(createValueAttribute<T>(VALUE_ATTRIBUTE_NAME))
  {
  }
}