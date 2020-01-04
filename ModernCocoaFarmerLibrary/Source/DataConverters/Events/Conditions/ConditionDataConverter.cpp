#include "DataConverters/Events/Conditions/ConditionDataConverter.h"


namespace MCF::DataConverters::Events::Conditions
{
  const char* const ConditionDataConverter::CONDITION_PATH_ATTRIBUTE_NAME = "path";

  //------------------------------------------------------------------------------------------------
  ConditionDataConverter::ConditionDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_path(*createReferenceAttribute<std::string>(CONDITION_PATH_ATTRIBUTE_NAME))
  {

  }
}