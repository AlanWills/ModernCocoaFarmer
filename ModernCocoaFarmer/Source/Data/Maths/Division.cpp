#include "Data/Maths/Division.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Maths
{
  REGISTER_COMPONENT(Division, 15);

  //------------------------------------------------------------------------------------------------
  const std::string Division::X_PORT_NAME("x");
  const std::string Division::Y_PORT_NAME("y");
  const std::string Division::VALUE_PORT_NAME("value");

  //------------------------------------------------------------------------------------------------
  Division::Division(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_xPort(createInputPort<float>(X_PORT_NAME, [this](Persistence::Data&& newValue) { onXPortChanged(std::move(newValue)); })),
    m_yPort(createInputPort<float>(Y_PORT_NAME, [this](Persistence::Data&& newValue) { onYPortChanged(std::move(newValue)); })),
    m_valuePort(createOutputPort<float>(VALUE_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void Division::onXPortChanged(Persistence::Data&& newValue)
  {
    m_x = std::get<float>(newValue);

    if (m_y != 0)
    {
      m_valuePort.setValue(m_x / m_y);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Division::onYPortChanged(Persistence::Data&& newValue)
  {
    m_y = std::get<float>(newValue);

    if (m_y != 0)
    {
      m_valuePort.setValue(m_x / m_y);
    }
  }
}