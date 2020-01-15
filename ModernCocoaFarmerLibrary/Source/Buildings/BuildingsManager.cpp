#include "Buildings/BuildingsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"


namespace MCF::Buildings
{
  REGISTER_SCRIPTABLE_OBJECT(BuildingsManager);

  //------------------------------------------------------------------------------------------------
  const char* const BuildingsManager::BUILDINGS_ELEMENT_NAME = "Buildings";
  const char* const BuildingsManager::BUILDING_ELEMENT_NAME = "Building";

  //------------------------------------------------------------------------------------------------
  BuildingsManager::BuildingsManager() :
    m_timeManager(nullptr),
    m_familyManager(nullptr),
    m_buildingsInformation(),
    m_onDayPassedHandle(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool BuildingsManager::doDeserialize(const tinyxml2::XMLElement* element)
  {

  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::setTimeManager(observer_ptr<Time::TimeManager> timeManager)
  {

  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::setFamilyManager(observer_ptr<Family::FamilyManager> familyManager)
  {

  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::sendChildToBuilding(BuildingInformation& buildingInformation, Family::Child& child)
  {

  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::onDayPassed(CelesteEngine::EventArgs& e)
  {

  }
}