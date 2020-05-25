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
    m_valuePort(createInputPort<bool>(VALUE_PORT_NAME, [this](const NewValue& newValue) { onValuePortChanged(newValue); })),
    m_triggerPort(createInputPort<bool>(TRIGGER_PORT_NAME, [this](const NewValue& newValue) { onTriggerPortChanged(newValue); })),
    m_outputPort(createOutputPort<bool>(OUTPUT_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ValueForwarder::onValuePortChanged(const NewValue& newValue)
  {
    m_value = newValue.get();
  }

  //------------------------------------------------------------------------------------------------
  void ValueForwarder::onTriggerPortChanged(const NewValue& newValue)
  {
    if (newValue.get<bool>())
    {
      m_outputPort.setValue(m_value);
    }
  }
}