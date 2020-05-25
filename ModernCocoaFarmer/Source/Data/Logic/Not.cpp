#include "Data/Logic/Not.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Logic
{
  REGISTER_COMPONENT(Not, 20);

  //------------------------------------------------------------------------------------------------
  const std::string Not::INPUT_PORT_NAME("input");
  const std::string Not::OUTPUT_PORT_NAME("output");

  //------------------------------------------------------------------------------------------------
  Not::Not(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_inputPort(createInputPort<bool>(INPUT_PORT_NAME, [this](const NewValue& newValue) { onInputChanged(newValue); })),
    m_outputPort(createOutputPort<bool>(OUTPUT_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void Not::onInputChanged(const NewValue& newValue)
  {
    m_outputPort.setValue(!newValue.get<bool>());
  }
}