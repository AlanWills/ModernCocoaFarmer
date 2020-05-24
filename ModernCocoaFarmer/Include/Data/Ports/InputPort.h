#pragma once

#include "Data/Ports/Port.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  template <typename T>
  struct item_return { using type = T; };

  //------------------------------------------------------------------------------------------------
  template <>
  struct item_return<std::string> { using type = const std::string&; };

  //------------------------------------------------------------------------------------------------
  struct NewValue
  {
    public:
      NewValue(void* value) : m_value(value) {}

      template <typename T>
      typename item_return<T>::type get() const { return *reinterpret_cast<T*>(m_value); }

    private:
      void* m_value;
  };

  //------------------------------------------------------------------------------------------------
  class InputPort : public Port
  {
    public:
      using ValueChangedCallback = std::function<void(const NewValue&)>;

      InputPort(const std::string& name, size_t type, ValueChangedCallback functionPtr) :
        Port(name, type),
        m_caller(functionPtr)
      {
      }

      template <typename T>
      void setValue(T value) 
      {
        m_caller(NewValue(&value));
      }

    private:
      ValueChangedCallback m_caller;
  };
}