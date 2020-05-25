#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"
#include "Data/Ports/OutputPort.h"


namespace MCF::Data
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

      size_t getType() const { return m_value.getType(); }
      void setType(size_t type) { m_value.setType(type); }

      template <typename T>
      void setType();

      template <typename T>
      void setValue(T value);

      void update(float elapsedGameTime) override;

      static const std::string VALUE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      OutputPort& m_value;
      std::string m_key;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void DataReader::setType()
  {
    setType(PortType<T>::value());
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void DataReader::setValue(T value)
  {
    m_value.setValue(value);
  }
}