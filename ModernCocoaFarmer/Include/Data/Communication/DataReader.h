#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"
#include "Data/Ports/OutputPort.h"


namespace MCF::System
{
  class DataSystem;
}

namespace MCF::Data::Communication
{
  class DataReader : public DataNodeComponent
  {
    DECLARE_MANAGED_COMPONENT(DataReader, DataSystem, MCFLibraryDllExport)

    public:
      const std::string& getKey() const { return m_key; }
      void setKey(const std::string& key) { m_key = key; }

      size_t getType() const { return m_value->getType(); }
      void setType(size_t type) { m_value->setType(type); }

      template <typename T>
      void setType();

      template <typename T>
      void setValue(T newValue);

      static const std::string VALUE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      observer_ptr<OutputPort> m_value;
      std::string m_key;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void DataReader::setType()
  {
    setType(type<T>());
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void DataReader::setValue(T newValue)
  {
    m_value->setValue(newValue);
  }
}