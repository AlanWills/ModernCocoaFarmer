#pragma once

#include "Objects/Component.h"

namespace MCF::Data
{
  template <typename T>
  class DataReader : public Celeste::Component
  {
    public:
      const std::string& getKey() const { return m_key; }
      void setKey(const std::string& key) { m_key = key; }

    private:
      std::string m_key;
  };
}