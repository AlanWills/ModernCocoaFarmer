#include "Buildings/BuildingsManager.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Buildings/Building.h"
#include "Time/TimeManager.h"
#include "Money/MoneyManager.h"
#include "Events/EventArgs.h"


namespace MCF::Buildings
{
  REGISTER_SCRIPTABLE_OBJECT(BuildingsManager);

  //------------------------------------------------------------------------------------------------
  const char* const BuildingsManager::BUILDINGS_ELEMENT_NAME = "Buildings";
  const char* const BuildingsManager::BUILDING_ELEMENT_NAME = "Building";

  //------------------------------------------------------------------------------------------------
  BuildingsManager::BuildingsManager() :
    m_timeManager(nullptr),
    m_buildings(),
    m_onDayPassedHandle(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool BuildingsManager::doDeserialize(const tinyxml2::XMLElement* element)
  {
    if (!hasChildElement(element, BUILDINGS_ELEMENT_NAME))
    {
      return true;
    }

    std::vector<std::string> buildingPrefabs;
    XMLValueError result = getChildElementDataAsVector(element, BUILDINGS_ELEMENT_NAME, BUILDING_ELEMENT_NAME, buildingPrefabs);
    
    if (result == XMLValueError::kError)
    {
      ASSERT_FAIL();
      return false;
    }

    for (const std::string& buildingPrefab : buildingPrefabs)
    {
      std::unique_ptr<Building> building = ScriptableObject::load<Building>(buildingPrefab);
      ASSERT(building != nullptr);

      if (building != nullptr)
      {
        m_buildings.emplace(building->getName(), std::move(building));
      }
    }

    return true;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<Building> BuildingsManager::getBuilding(const std::string& buildingName)
  {
    auto buildingIt = m_buildings.find(buildingName);
    return buildingIt != m_buildings.end() ? buildingIt->second.get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::setTimeManager(observer_ptr<Time::TimeManager> timeManager)
  {
    if (m_timeManager != nullptr)
    {
      m_timeManager->getOnDayPassedEvent().unsubscribe(m_onDayPassedHandle);
    }

    m_timeManager = timeManager;

    if (m_timeManager != nullptr)
    {
      m_onDayPassedHandle = m_timeManager->getOnDayPassedEvent().subscribe([this](CelesteEngine::EventArgs&) { onDayPassed(); });
    }
  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::sendChildToBuilding(Building& building, Family::Child& child)
  {
    building.sendChild(child);
  }

  //------------------------------------------------------------------------------------------------
  void BuildingsManager::onDayPassed()
  {
    for (const auto& stringBuildingPair : m_buildings)
    {
      stringBuildingPair.second->updateCurrentChildren();
    }
  }
}