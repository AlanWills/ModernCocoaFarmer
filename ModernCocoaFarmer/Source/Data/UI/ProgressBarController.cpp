#include "Data/UI/ProgressBarController.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "UI/ProgressBar.h"


namespace MCF::Data::UI
{
  REGISTER_COMPONENT(ProgressBarController, 10);

  //------------------------------------------------------------------------------------------------
  const std::string ProgressBarController::PROGRESS_PORT_NAME("progress");

  //------------------------------------------------------------------------------------------------
  ProgressBarController::ProgressBarController(Celeste::GameObject& gameObject) :
    Inherited(gameObject),
    m_progressPort(createInputPort<float>(PROGRESS_PORT_NAME, [this](Persistence::Data&& newValue) { onProgressPortChanged(std::move(newValue)); }))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ProgressBarController::onProgressPortChanged(Persistence::Data&& newValue)
  {
    auto progressBar = getGameObject().findComponent<Celeste::UI::ProgressBar>();
    ASSERT_NOT_NULL(progressBar);

    if (progressBar != nullptr)
    {
      progressBar->setProgress(std::get<float>(newValue));
    }
  }
}