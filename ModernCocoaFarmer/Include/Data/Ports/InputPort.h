#pragma once

#include "Data/Ports/Port.h"
#include "Persistence/Data.h"
#include "glm/glm.hpp"

#include <functional>


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  class InputPort : public Port
  {
    public:
      using ValueChangedCallback = std::function<void(Persistence::Data&&)>;

      InputPort(const std::string& name, size_t type, ValueChangedCallback&& valueChangedCallback) :
        Port(name, type),
        m_valueChanged(std::move(valueChangedCallback))
      {
      }
      InputPort(const InputPort&) = delete;
      InputPort(InputPort&&) = default;
      ~InputPort() = default;

      InputPort& operator=(const InputPort&) = delete;
      InputPort& operator=(InputPort&&) = default;

      template <typename T>
      void setValue(T value) 
      {
        m_valueChanged(Persistence::Data(value));
      }

    private:
      ValueChangedCallback m_valueChanged;
  };
}