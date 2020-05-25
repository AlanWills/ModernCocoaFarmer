#pragma once

#include "MCFLibraryDllExport.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data::Communication
{
  template <typename T>
  class ValueForwarder : public DataNodeComponent
  {
    public:
      ValueForwarder(Celeste::GameObject& gameObject);

      static const std::string VALUE_PORT_NAME;
      static const std::string TRIGGER_PORT_NAME;
      static const std::string OUTPUT_PORT_NAME;

    private:
      using Inherited = DataNodeComponent;

      void onValuePortChanged(const NewValue& newValue);
      void onTriggerPortChanged(const NewValue& newValue);

      InputPort& m_valuePort;
      InputPort& m_triggerPort;
      OutputPort& m_outputPort;

      T m_value;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  const std::string ValueForwarder<T>::TRIGGER_PORT_NAME("trigger");

  template <typename T>
  const std::string ValueForwarder<T>::VALUE_PORT_NAME("value");

  template <typename T>
  const std::string ValueForwarder<T>::OUTPUT_PORT_NAME("output");

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ValueForwarder<T>::ValueForwarder(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_valuePort(createInputPort<T>(VALUE_PORT_NAME, [this](const NewValue& newValue) { onValuePortChanged(newValue); })),
    m_triggerPort(createInputPort<bool>(TRIGGER_PORT_NAME, [this](const NewValue& newValue) { onTriggerPortChanged(newValue); })),
    m_outputPort(createOutputPort<T>(OUTPUT_PORT_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ValueForwarder<T>::onValuePortChanged(const NewValue& newValue)
  {
    m_value = newValue.get<T>();
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ValueForwarder<T>::onTriggerPortChanged(const NewValue& newValue)
  {
    if (newValue.get<bool>())
    {
      m_outputPort.setValue(m_value);
    }
  }
}

// Can we detemplatize this?
// Can we just store the NewValue?  Currently that points to a temp value on the stack though
// If we could we could just forward it on and get the port to take care of reading the right value using it's type
// If ports dealt with refs this might be ok, but when the data store dictionary moves objects around we're gonna have problems
// What if the port stores a Data optional rather than a void*?
// Then use the variant function trick to get the value at runtime using the type