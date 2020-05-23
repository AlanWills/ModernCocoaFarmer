#pragma once

#include "CelesteStl/Memory/ObserverPtr.h"

#include <vector>
#include <string>


namespace MCF::Data
{
  class Port
  {
    public:
      Port(const std::string& name) : 
        m_name(name) 
      {
      }

      Port(const Port&) = delete;
      Port(Port&&) = default;
      
      virtual ~Port() = default;

      Port& operator=(const Port&) = delete;
      Port& operator=(Port&&) = default;

      virtual size_t getType() const = 0;

      const std::string& getName() const { return m_name; }

    private:
      std::string m_name;
  };
}