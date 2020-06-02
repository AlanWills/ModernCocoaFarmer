#include "Data/Objects/ActivityController.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace MCF::Data::Objects
{
  REGISTER_COMPONENT(ActivityController, 20);

  //------------------------------------------------------------------------------------------------
  const std::string ActivityController::IS_ACTIVE_PORT_NAME("is_active");

  //------------------------------------------------------------------------------------------------
  ActivityController::ActivityController(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_isActivePort(createInputPort<bool>(IS_ACTIVE_PORT_NAME, [this](Persistence::Data&& newValue) { onIsActivePortChanged(std::move(newValue)); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ActivityController::onIsActivePortChanged(Persistence::Data&& newValue)
  {
    getGameObject().setActive(std::get<bool>(newValue));
  }
}