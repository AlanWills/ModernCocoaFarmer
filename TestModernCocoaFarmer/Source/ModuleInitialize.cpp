#include "Game/Game.h"
#include "Debug/Assert.h"
#include "Debug/Asserting/NullAsserter.h"
#include "OpenGL/GL.h"
#include "Lua/LuaState.h"
#include "Resources/TestResources.h"
#include "UtilityHeaders/UnitTestHeaders.h"


namespace TestCelesteEngine
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestCelesteEnginePlus_Initialize)
  {
    // Issues with unique_ptrs over dll boundaries so have to do this in the test project
    Assertion::setAsserter(new NullAsserter());

    CelesteEngineTestUtils::TestResources::setResourcesDirectory(Path(Directory::getExecutingAppDirectory(), "Resources"));
    CelesteEngineTestUtils::TestResources::initialize();

    Game* game = new Game();
    game->getResourceManager()->setResourcesDirectory(TestResources::getResourcesDirectory());
    game->getAudioManager()->initialize();
    game->getScreenManager()->initialize();
    game->getPhysicsManager()->initialize();
    game->getInputManager()->initialize();
    game->getResourceManager()->initialize();

    Lua::LuaState::appendToLuaPackagePath(Path(Resources::getResourcesDirectory(), "Scripts", "?.lua;"));

    getWindow()->setViewportDimensions(100, 100);
  }

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_CLEANUP(TestCelesteEnginePlus_Cleanup)
  {
    // Issues with unique_ptrs over dll boundaries so have to do this in the test project
    Game::current()->getScreenManager()->die();
    Game::current()->getInputManager()->die();
    Game::current()->getPhysicsManager()->die();
    Game::current()->getAudioManager()->die();
    Game::current()->getResourceManager()->die();
    Game::current()->exit();

    GL::terminate();
  }
}