#include "Data/Constants/Constant.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Constants
{
  REGISTER_COMPONENT(Constant, 40);

  //------------------------------------------------------------------------------------------------
  const std::string Constant::VALUE_PORT_NAME = "value";

  //------------------------------------------------------------------------------------------------
  Constant::Constant(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_valuePort(createOutputPort<bool>(VALUE_PORT_NAME)),
    m_value()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Constant::update()
  {
    m_valuePort.setValue(m_value);
  }

  //------------------------------------------------------------------------------------------------
  void Constant::setValue(const Persistence::Data& newValue)
  {
    m_value = newValue;
    m_valuePort.setType(newValue.index());
    m_valuePort.setValue(newValue);
  }
}