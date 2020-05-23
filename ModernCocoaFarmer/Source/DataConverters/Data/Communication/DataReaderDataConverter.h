#pragma once

#include "DataConverters/Data/DataNodeComponentDataConverter.h"
#include "Data/Communication/DataReader.h"


namespace MCF::DataConverters::Data::Communication
{
  template <typename T>
  class DataReaderDataConverter : public DataNodeComponentDataConverter
  {
    public:
      DataReaderDataConverter(const std::string& elementName);

      const std::string& getKey() const { return m_key.getValue(); }

      static const char* const KEY_ATTRIBUTE_NAME;

    protected:
      void doSetValues(MCF::Data::Communication::DataReader<T>& dataReader) const;

    private:
      using Inherited = DataNodeComponentDataConverter;

      Celeste::XML::ReferenceAttribute<std::string>& m_key;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  const char* const DataReaderDataConverter<T>::KEY_ATTRIBUTE_NAME = "key";

  //------------------------------------------------------------------------------------------------
  template <typename T>
  DataReaderDataConverter<T>::DataReaderDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_key(createReferenceAttribute<std::string>(KEY_ATTRIBUTE_NAME, "", Celeste::DeserializationRequirement::kRequired))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void DataReaderDataConverter<T>::doSetValues(MCF::Data::Communication::DataReader<T>& dataReader) const
  {
    Inherited::doSetValues(dataReader);

    dataReader.setKey(getKey());
  }
}