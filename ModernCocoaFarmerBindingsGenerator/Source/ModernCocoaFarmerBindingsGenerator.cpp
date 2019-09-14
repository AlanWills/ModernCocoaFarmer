#include "Project.h"
#include "Objects/Component.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace CelesteEngine;
using namespace BindingsGenerator;


int main()
{
  Path projectPath(Directory::getExecutingAppDirectory(), UPDIR_STRING, "ModernCocoaFarmerBindings");
  Project project(projectPath, "ModernCocoaFarmerBindings", "MCF");
  project.generateBindings();

  std::this_thread::sleep_for(std::chrono::seconds(2));

  return 0;
}