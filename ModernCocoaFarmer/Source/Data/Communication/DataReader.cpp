#include "Data/Communication/DataReader.h"
#include "Data/Ports/OutputPort.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Communication
{
  //------------------------------------------------------------------------------------------------
  REGISTER_COMPONENT(DataReader, 30);

  //------------------------------------------------------------------------------------------------
  const std::string DataReader::VALUE_PORT_NAME = "value";

  //------------------------------------------------------------------------------------------------
  DataReader::DataReader(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_value(&createOutputPort(VALUE_PORT_NAME, type<bool>()))
  {
  }
}