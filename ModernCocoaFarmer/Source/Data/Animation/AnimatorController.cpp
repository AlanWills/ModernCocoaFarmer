#include "Data/Animation/AnimatorController.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Animation/Animator.h"


namespace MCF::Data::Animation
{
  REGISTER_COMPONENT(AnimatorController, 10);

  //------------------------------------------------------------------------------------------------
  const std::string AnimatorController::PLAY_PORT_NAME("play");
  const std::string AnimatorController::STOP_PORT_NAME("stop");

  //------------------------------------------------------------------------------------------------
  AnimatorController::AnimatorController(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_playPort(createInputPort<bool>(PLAY_PORT_NAME, [this](Persistence::Data&& newValue) { onPlayPortChanged(std::move(newValue)); })),
    m_stopPort(createInputPort<bool>(STOP_PORT_NAME, [this](Persistence::Data&& newValue) { onStopPortChanged(std::move(newValue)); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void AnimatorController::onPlayPortChanged(Persistence::Data&& newValue)
  {
    ASSERT(getGameObject().hasComponent<Celeste::Animation::Animator>());

    if (std::get<bool>(newValue))
    {
      getGameObject().findComponent<Celeste::Animation::Animator>()->play();
    }
  }

  //------------------------------------------------------------------------------------------------
  void AnimatorController::onStopPortChanged(Persistence::Data&& newValue)
  {
    ASSERT(getGameObject().hasComponent<Celeste::Animation::Animator>());

    if (std::get<bool>(newValue))
    {
      getGameObject().findComponent<Celeste::Animation::Animator>()->stop();
    }
  }
}