#include "Data/Communication/DataReader.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Communication
{
  //------------------------------------------------------------------------------------------------
  REGISTER_COMPONENT(BoolDataReader, 30);
  REGISTER_COMPONENT(IntDataReader, 30);
  REGISTER_COMPONENT(UIntDataReader, 30);
  REGISTER_COMPONENT(FloatDataReader, 30);
  REGISTER_COMPONENT(StringDataReader, 30);

  //------------------------------------------------------------------------------------------------
  BoolDataReader::BoolDataReader(Celeste::GameObject& gameObject) :
    DataReader<bool>(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  IntDataReader::IntDataReader(Celeste::GameObject& gameObject) :
    DataReader<int>(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  UIntDataReader::UIntDataReader(Celeste::GameObject& gameObject) :
    DataReader<unsigned int>(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  FloatDataReader::FloatDataReader(Celeste::GameObject& gameObject) :
    DataReader<float>(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  StringDataReader::StringDataReader(Celeste::GameObject& gameObject) :
    DataReader<std::string>(gameObject)
  {
  }
}