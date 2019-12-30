#include "Project.h"
#include "Stats/ChildModifier.h"
#include "Events/GameEvent.h"
#include "Buildings/BuildingInformation.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace CelesteEngine;
using namespace BindingsGenerator;


int main()
{
  ScriptableObject::create<MCF::Stats::ChildModifier>("Test");
  ScriptableObject::create<MCF::Events::GameEvent>("Test");
  ScriptableObject::create<MCF::Buildings::BuildingInformation>("Test");

  Path projectPath(Directory::getExecutingAppDirectory(), UPDIR_STRING, "ModernCocoaFarmerBindings");
  Project project(projectPath, "ModernCocoaFarmerBindings", "MCF");
  project.generateBindings();

  std::this_thread::sleep_for(std::chrono::seconds(2));

  return 0;
}