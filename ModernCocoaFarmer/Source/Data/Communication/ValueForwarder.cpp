#include "Data/Communication/ValueForwarder.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Communication
{
  REGISTER_COMPONENT(ValueForwarder, 30);

  //------------------------------------------------------------------------------------------------
  const std::string ValueForwarder::TRIGGER_PORT_NAME("trigger");
  const std::string ValueForwarder::VALUE_PORT_NAME("value");
  const std::string ValueForwarder::OUTPUT_PORT_NAME("output");

  //------------------------------------------------------------------------------------------------
  ValueForwarder::ValueForwarder(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_valuePort(createInputPort<bool>(VALUE_PORT_NAME, [this](Persistence::Data&& newValue) { onValuePortChanged(std::move(newValue)); })),
    m_triggerPort(createInputPort<bool>(TRIGGER_PORT_NAME, [this](Persistence::Data&& newValue) { onTriggerPortChanged(std::move(newValue)); })),
    m_outputPort(createOutputPort<bool>(OUTPUT_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ValueForwarder::onValuePortChanged(Persistence::Data&& newValue)
  {
    m_value = std::move(newValue);
  }

  //------------------------------------------------------------------------------------------------
  void ValueForwarder::onTriggerPortChanged(Persistence::Data&& newValue)
  {
    if (std::get<bool>(newValue))
    {
      m_outputPort.setValue(m_value);
    }
  }
}