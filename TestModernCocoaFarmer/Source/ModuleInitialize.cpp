#include "Game/Game.h"
#include "Debug/Assert.h"
#include "Debug/Asserting/NullAsserter.h"
#include "OpenGL/GL.h"
#include "Lua/LuaState.h"
#include "Resources/TestResources.h"
#include "UtilityHeaders/UnitTestHeaders.h"


namespace TestMCF
{
  std::unique_ptr<Game> game(nullptr);

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestMCF_Initialize)
  {
    // Issues with unique_ptrs over dll boundaries so have to do this in the test project
    Assertion::setAsserter(new NullAsserter());

    CelesteTestUtils::TestResources::setResourcesDirectory(Path(Directory::getExecutingAppDirectory(), "Resources"));
    CelesteTestUtils::TestResources::initialize();

    game = std::make_unique<Game>();
    game->getResourceManager().setResourcesDirectory(TestResources::getResourcesDirectory());

    Lua::LuaState::appendToLuaPackagePath(Path(Resources::getResourcesDirectory(), "Scripts", "?.lua;"));

    getWindow().setViewportDimensions(100, 100);
  }

  //------------------------------------------------------------------------------------------------
  TEST_MODULE_CLEANUP(TestMCF_Cleanup)
  {
    Game::exit();
    GL::terminate();
  }
}