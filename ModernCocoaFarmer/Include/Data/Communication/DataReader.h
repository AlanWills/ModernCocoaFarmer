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

      size_t getType() const { return m_valuePort.getType(); }
      void setType(size_t type) { m_valuePort.setType(type); }

      template <typename T>
      void setType();

      template <typename T>
      void setValue(T value);

      void update(const DataSystem& dataSystem) override;

      static const std::string KEY_PORT_NAME;
      static const std::string VALUE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onKeyPortChanged(Persistence::Data&& newValue);

      InputPort& m_keyPort;
      OutputPort& m_valuePort;
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
    m_valuePort.setValue(value);
  }
}