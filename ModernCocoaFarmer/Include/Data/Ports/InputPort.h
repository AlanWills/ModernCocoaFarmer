#pragma once

#include "Data/Ports/Port.h"
#include "Persistence/Data.h"
#include "glm/glm.hpp"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  struct NewValue
  {
    public:
      template <typename T>
      NewValue(T&& value) : m_value(value) {}

      const Persistence::Data& get() const { return m_value; }

      template <typename T>
      typename Persistence::data_return<T>::type get() const { return std::get<T>(m_value); }

    private:
      Persistence::Data m_value;
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
        m_caller(std::move(value));
      }

    private:
      ValueChangedCallback m_caller;
  };
}