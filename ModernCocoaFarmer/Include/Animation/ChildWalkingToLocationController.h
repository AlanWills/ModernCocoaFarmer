#pragma once

#include "MCFLibraryDllExport.h"
#include "Objects/Component.h"
#include "glm/glm.hpp"


namespace MCF::Animation
{
  class ChildWalkingToLocationController : public Celeste::Component
  {
    DECLARE_UNMANAGED_COMPONENT(ChildWalkingToLocationController, MCFLibraryDllExport);

    public:
      float getSpeed() const { return m_speed; }
      void setSpeed(float speed) { m_speed = speed; }

      const glm::vec3& getLocation() const { return m_location; }
      void setLocation(const glm::vec3& location) { m_location = location; }

      void update() override;

    private:
      using Inherited = Celeste::Component;

      float m_speed = 1;
      glm::vec3 m_location;
  };
}