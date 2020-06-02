#pragma once

#include "CelesteStl/Memory/ObserverPtr.h"
#include "crossguid/guid.hpp"

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

      const xg::Guid& getGuid() const { return m_guid; }
      void setGuid(const xg::Guid& guid) { m_guid = guid; }

    protected:
      Port(const std::string& name, size_t type) :
        m_name(name),
        m_type(type),
        m_guid(xg::newGuid())
      {
      }
      ~Port() = default;  // Prevent deletion through base pointer

    private:
      std::string m_name;
      size_t m_type;
      xg::Guid m_guid;
  };
}