#pragma once

#include "CelesteStl/Memory/ObserverPtr.h"

#include <vector>
#include <string>


namespace MCF::Data
{
  class Port
  {
    public:
      Port(const Port&) = delete;
      Port(Port&&) = default;
      
      Port& operator=(const Port&) = delete;
      Port& operator=(Port&&) = default;

      const std::string& getName() const { return m_name; }
      void setName(const std::string& name) { m_name = name; }

      size_t getType() const { return m_type; }
      void setType(size_t type) { m_type = type; }

    protected:
      Port(const std::string& name, size_t type) :
        m_name(name),
        m_type(type)
      {
      }

    private:
      std::string m_name;
      size_t m_type;
  };
}