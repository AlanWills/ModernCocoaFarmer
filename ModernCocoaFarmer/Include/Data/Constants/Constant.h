#pragma once

#include "Data/DataNodeComponent.h"

// Data Converter can tell DataSystem to update a component
// Will need class & DC for each constant type, but that can't be helped
// Value Forwarder will need to be templated too - there's no way to store the constant value otherwise


namespace MCF::Data::Constants
{
  template <typename T>
  class Constant : public DataNodeComponent
  {
    public:
      Constant(Celeste::GameObject& gameObject);

      T getValue() const { return m_value; }
      void setValue(T newValue);

      void update(float elapsedGameTime) override;

      static const std::string VALUE_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      OutputPort& m_valuePort;
      T m_value;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  const std::string Constant<T>::VALUE_PORT_NAME = "value";

  //------------------------------------------------------------------------------------------------
  template <typename T>
  Constant<T>::Constant(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_valuePort(createOutputPort<T>(VALUE_PORT_NAME)),
    m_value()
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void Constant<T>::update(float /*elapsedGameTime*/)
  {
    m_valuePort.setValue(m_value);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void Constant<T>::setValue(T newValue)
  {
    m_value = newValue;
    m_valuePort.setValue(newValue);
  }
}