#pragma once

#include "DataConverters/DataConverter.h"


namespace MCF::Events::Conditions
{
  class Condition;
}

namespace MCF::DataConverters::Events::Conditions
{
  class ConditionDataConverter : public CelesteEngine::DataConverter
  {
    public:
      ConditionDataConverter(const std::string& elementName = "Condition");

      const std::string& getPath() const { return m_path.getValue(); }
      
      std::unique_ptr<MCF::Events::Conditions::Condition> instantiate() const;

      static const char* const CONDITION_PATH_ATTRIBUTE_NAME;

    protected:
      virtual bool doConvertFromXML(const XMLElement* objectElement) { return true; }

    private:
      using Inherited = CelesteEngine::DataConverter;

      CelesteEngine::XML::ReferenceAttribute<std::string>& m_path;
  };
}