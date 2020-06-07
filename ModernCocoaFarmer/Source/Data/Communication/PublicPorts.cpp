#include "Data/Communication/PublicPorts.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Communication
{
  REGISTER_COMPONENT(PublicPorts, 20);

  //------------------------------------------------------------------------------------------------
  PublicPorts::PublicPorts(Celeste::GameObject& gameObject) :
    Inherited(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  InputPort& PublicPorts::createInputPort(const std::string& name, size_t type, OutputPort& outputPort)
  {
    return Inherited::createInputPort(name, type, [&outputPort](Persistence::Data&& newValue) { outputPort.setValue(std::move(newValue)); });
  }

  //------------------------------------------------------------------------------------------------
  OutputPort& PublicPorts::createOutputPort(const std::string& name, size_t type)
  {
    return Inherited::createOutputPort(name, type);
  }
}