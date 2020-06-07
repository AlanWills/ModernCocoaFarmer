#include "DataConverters/Data/Communication/PublicPortsDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Data/Communication/PublicPorts.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"


namespace MCF::DataConverters::Data::Communication
{
  REGISTER_COMPONENT_DATA_CONVERTER(PublicPortsDataConverter);

  //------------------------------------------------------------------------------------------------
  PublicPortsDataConverter::PublicPortsDataConverter() :
    Inherited(MCF::Data::Communication::PublicPorts::type_name())
  {
  }

  //------------------------------------------------------------------------------------------------
  void PublicPortsDataConverter::doSetValues(MCF::Data::Communication::PublicPorts& publicPorts) const
  {
    // Then create all input ports using output ports

    for (const auto& portDataConverter : getOutputPortDataConverters())
    {
      auto& outputPort = publicPorts.createOutputPort(portDataConverter->getPortName(), portDataConverter->getType());
      outputPort.setGuid(xg::Guid(portDataConverter->getGuid()));
    }

    for (const auto& portDataConverter : getInputPortDataConverters())
    {
      xg::Guid guid(portDataConverter->getGuid());
      MCF::Data::OutputPort* outputPort = publicPorts.findOutputPort(guid);
      ASSERT_NOT_NULL(outputPort);

      if (outputPort != nullptr)
      {
        auto& inputPort = publicPorts.createInputPort(portDataConverter->getPortName(), portDataConverter->getType(), *outputPort);
        inputPort.setGuid(guid);
      }
    }

    Inherited::doSetValues(publicPorts);
  }
}