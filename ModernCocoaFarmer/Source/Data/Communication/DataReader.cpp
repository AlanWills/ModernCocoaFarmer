#include "Data/Communication/DataReader.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Data/DataUtils.h"
#include "Data/DataSystem.h"
#include "CelesteStl/Templates/Variant.h"


namespace MCF::Data::Communication
{
  //------------------------------------------------------------------------------------------------
  using Data = Persistence::Data;
  using DataReaderSetters = celstl::VariantFunctions<Data, void, const DataSystem&, Communication::DataReader&>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct DataReaderSetter
  {
    static void execute(const DataSystem& dataSystem, Communication::DataReader& reader)
    {
      reader.setValue(dataSystem.get<T>(reader.getKey()));
    }
  };

  static DataReaderSetters s_dataReaderSetters = celstl::createVariantFunctions<DataReaderSetters, DataReaderSetter>();

  //------------------------------------------------------------------------------------------------
  REGISTER_COMPONENT(DataReader, 30);

  //------------------------------------------------------------------------------------------------
  const std::string DataReader::KEY_PORT_NAME = "key";
  const std::string DataReader::VALUE_PORT_NAME = "value";

  //------------------------------------------------------------------------------------------------
  DataReader::DataReader(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_keyPort(createInputPort<std::string>(KEY_PORT_NAME, [this](Persistence::Data&& newValue) { onKeyPortChanged(std::move(newValue)); })),
    m_valuePort(createOutputPort<bool>(VALUE_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void DataReader::update(const DataSystem& dataSystem)
  {
    if (getType() < s_dataReaderSetters.size())
    {
      s_dataReaderSetters.m_functions[getType()](dataSystem, *this);
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataReader::onKeyPortChanged(Persistence::Data&& newValue)
  {
    m_key = std::get<std::string>(newValue);
    getDataSystem().queueUpdate(*this);
  }
}