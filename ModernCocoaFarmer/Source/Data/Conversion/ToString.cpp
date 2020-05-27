#include "Data/Conversion/ToString.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "CelesteStl/Templates/Variant.h"
#include "Utils/ToString.h"


namespace MCF::Data::Conversion
{
  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct ToStringFunctor
  {
    static std::string execute(Persistence::Data&& data)
    {
      return Celeste::to_string<T>(std::get<T>(data));
    }
  };

  //------------------------------------------------------------------------------------------------
  template <>
  struct ToStringFunctor<glm::vec3>
  {
    static std::string execute(Persistence::Data&& /*data*/)
    {
      LOG("vec3 is not a supported type for ToString.");
      ASSERT_FAIL();
      return "";
    }
  };

  using ToStringFunctions = celstl::VariantFunctions<Persistence::Data, std::string, Persistence::Data&&>;
  static ToStringFunctions s_toStringFunctions = celstl::createVariantFunctions<ToStringFunctions, ToStringFunctor>();

  REGISTER_COMPONENT(ToString, 40);

  //------------------------------------------------------------------------------------------------
  const std::string ToString::VALUE_PORT_NAME = "value";
  const std::string ToString::OUTPUT_PORT_NAME = "output";

  //------------------------------------------------------------------------------------------------
  ToString::ToString(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_valuePort(createInputPort<bool>(VALUE_PORT_NAME, [this](Persistence::Data&& newValue) { onInputPortChanged(std::move(newValue)); })),
    m_outputPort(createOutputPort<std::string>(OUTPUT_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ToString::onInputPortChanged(Persistence::Data&& newValue)
  {
    ASSERT(newValue.index() < s_toStringFunctions.size());
    if (newValue.index() < s_toStringFunctions.size())
    {
      m_outputPort.setValue(s_toStringFunctions.m_functions[newValue.index()](std::move(newValue)));
    }
  }
}