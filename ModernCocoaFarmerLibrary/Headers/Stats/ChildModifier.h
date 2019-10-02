#pragma once

#include "Stats/Modifier.h"


namespace MCF
{
  namespace Stats
  {
    class ChildModifier : public Modifier
    {
      DECLARE_SCRIPTABLE_OBJECT(ChildModifier);

      public:
        bool getAppliesToAllChildren() const { return m_appliesToAllChildren.getValue(); }

        static const std::string APPLIES_TO_ALL_CHILDREN_FIELD_NAME;

      private:
        CelesteEngine::ValueField<bool>& m_appliesToAllChildren;
    };
  }
}