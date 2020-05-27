#include "Animation/ChildWalkingToLocationController.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Animation
{
  REGISTER_COMPONENT(ChildWalkingToLocationController, 6);

  //------------------------------------------------------------------------------------------------
  ChildWalkingToLocationController::ChildWalkingToLocationController(Celeste::GameObject& gameObject) :
    Inherited(gameObject)
  {
  }

  //------------------------------------------------------------------------------------------------
  void ChildWalkingToLocationController::update(float elapsedGameTime)
  {
    Inherited::update(elapsedGameTime);

    glm::vec3 delta = m_location - getTransform()->getWorldTranslation();
    float distanceLeft = glm::length(delta);
    glm::vec3 normalizedDelta = delta / distanceLeft;

    if (distanceLeft < (m_speed * elapsedGameTime))
    {
      delete &getGameObject();
    }
    else
    {
      // Set the game object facing the right way
      glm::vec3 worldScale = getTransform()->getWorldScale();
      worldScale.x = (delta.x >= 0 ? 1 : -1) * std::abs(worldScale.x);
      getTransform()->setWorldScale(worldScale);

      // Move the game object towards the location
      getTransform()->setWorldTranslation(getTransform()->getWorldTranslation() + m_speed * elapsedGameTime * normalizedDelta);
    }
  }
}