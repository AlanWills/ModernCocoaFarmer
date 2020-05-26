#include "DataConverters/Data/Constants/ConstantDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Constants/Constant.h"
#include "CelesteStl/Templates/Variant.h"
#include "XML/tinyxml2_ext.h"


namespace MCF::DataConverters::Data::Constants
{
  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct Deserialization
  {
    static bool execute(const tinyxml2::XMLElement* element, Persistence::Data& data)
    {
      T value;
      if (Celeste::XML::getAttributeData(element, ConstantDataConverter::VALUE_ATTRIBUTE_NAME, value) == Celeste::XML::XMLValueError::kSuccess)
      {
        data.emplace<T>(std::move(value));
        return true;
      }

      return false;
    }
  };

  using DeserializationFunctions = celstl::VariantFunctions<Persistence::Data, bool, const tinyxml2::XMLElement*, Persistence::Data&>;
  static DeserializationFunctions s_deserializationFunctions = celstl::createVariantFunctions<DeserializationFunctions, Deserialization>();

  REGISTER_COMPONENT_DATA_CONVERTER(ConstantDataConverter);

  //------------------------------------------------------------------------------------------------
  const char* const ConstantDataConverter::TYPE_ATTRIBUTE_NAME("type");
  const char* const ConstantDataConverter::VALUE_ATTRIBUTE_NAME("value");

  //------------------------------------------------------------------------------------------------
  ConstantDataConverter::ConstantDataConverter() :
    Inherited(MCF::Data::Constants::Constant::type_name()),
    m_type(createValueAttribute<size_t>(TYPE_ATTRIBUTE_NAME, size_t(), Celeste::DeserializationRequirement::kRequired)),
    m_value()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool ConstantDataConverter::doConvertFromXML(const tinyxml2::XMLElement* element)
  {
    if (!Inherited::doConvertFromXML(element))
    {
      ASSERT_FAIL();
      return false;
    }

    if (getType() >= s_deserializationFunctions.size())
    {
      ASSERT_FAIL();
      return false;
    }

    if (!s_deserializationFunctions.m_functions[getType()](element, m_value))
    {
      ASSERT_FAIL();
      return false;
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  void ConstantDataConverter::doSetValues(MCF::Data::Constants::Constant& constant) const
  {
    Inherited::doSetValues(constant);

    constant.setValue(m_value);
  }
}