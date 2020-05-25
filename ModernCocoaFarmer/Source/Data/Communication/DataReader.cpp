#include "Data/Communication/DataReader.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "CelesteStl/Templates/Variant.h"


namespace MCF::Data::Communication
{
  //------------------------------------------------------------------------------------------------
  using Data = Persistence::Data;
  using DataReaderSetters = celstl::VariantFunctions<Data, void, DataSystem&, Communication::DataReader&>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct DataReaderSetter
  {
    static void execute(DataSystem& dataSystem, Communication::DataReader& reader)
    {
      reader.setValue(dataSystem.get<T>(reader.getKey()));
    }
  };

  static DataReaderSetters s_dataReaderSetters = celstl::createVariantFunctions<DataReaderSetters, DataReaderSetter>();

  //------------------------------------------------------------------------------------------------
  REGISTER_COMPONENT(DataReader, 30);

  //------------------------------------------------------------------------------------------------
  const std::string DataReader::VALUE_PORT_NAME = "value";

  //------------------------------------------------------------------------------------------------
  DataReader::DataReader(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_value(createOutputPort<bool>(VALUE_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void DataReader::update(float /*elapsedGameTime*/)
  {
    if (getType() < s_dataReaderSetters.size())
    {
      s_dataReaderSetters.m_functions[getType()](getDataSystem(), *this);
    }
  }
}