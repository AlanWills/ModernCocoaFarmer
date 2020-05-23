#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"

namespace MCF::System
{
  class DataSystem;
}

namespace MCF::Data::Communication
{
  template <typename T>
  class DataReader : public DataNodeComponent
  {
    public:
      DataReader(Celeste::GameObject& gameObject);

      const std::string& getKey() const { return m_key; }
      void setKey(const std::string& key) { m_key = key; }

      void setValue(T newValue);

    private:
      using Inherited = DataNodeComponent;

      OutputPort<T>& m_value;
      std::string m_key;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  DataReader<T>::DataReader(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_value(createOutputPort<T>("value"))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void DataReader<T>::setValue(T newValue)
  {
    m_value.setValue(newValue);
  }

  //------------------------------------------------------------------------------------------------
  class BoolDataReader : public DataReader<bool> { DECLARE_MANAGED_COMPONENT(BoolDataReader, DataSystem, MCFLibraryDllExport) };

  //------------------------------------------------------------------------------------------------
  class IntDataReader : public DataReader<int> { DECLARE_MANAGED_COMPONENT(IntDataReader, DataSystem, MCFLibraryDllExport) };

  //------------------------------------------------------------------------------------------------
  class UIntDataReader : public DataReader<unsigned int> { DECLARE_MANAGED_COMPONENT(UIntDataReader, DataSystem, MCFLibraryDllExport) };

  //------------------------------------------------------------------------------------------------
  class FloatDataReader : public DataReader<float> { DECLARE_MANAGED_COMPONENT(FloatDataReader, DataSystem, MCFLibraryDllExport) };

  //------------------------------------------------------------------------------------------------
  class StringDataReader : public DataReader<std::string> { DECLARE_MANAGED_COMPONENT(StringDataReader, DataSystem, MCFLibraryDllExport) };
}