#include "Lua/ScriptCommands/Persistence/DataStoreScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Persistence/DataStore.h"
#include "Resources/ResourceUtils.h"
#include "Debug/Debug.h"


namespace MCF
{
  namespace Lua
  {
    namespace Persistence
    {
      namespace DataStoreScriptCommands
      {
        namespace Internals
        {
          //------------------------------------------------------------------------------------------------
          MCF::Persistence::DataStore loadOrCreate(const std::string& filePath)
          {
            using namespace CelesteEngine::Resources;
            using namespace MCF::Persistence;

            CelesteEngine::Handle<Data> data = getResourceManager()->load<Data>(filePath);
            if (data.is_null() || data->getDocumentRoot() == nullptr)
            {
              return DataStore();
            }

            return DataStore::deserialize(*data->getDocumentRoot());
          }

          //------------------------------------------------------------------------------------------------
          bool save(MCF::Persistence::DataStore& dataStore, const std::string& filePath)
          {
            using namespace CelesteEngine;
            using namespace CelesteEngine::Resources;
            using namespace MCF::Persistence;

            tinyxml2::XMLDocument document;
            tinyxml2::XMLElement* element = document.NewElement("DataStore");
            document.InsertEndChild(element);
            dataStore.serialize(*element);

            // Ensures that all parent directories are created too
            Path path(getResourcesDirectory(), filePath);
            File(path).create();

            return document.SaveFile(path.c_str()) == XML_SUCCESS;
          }
        }

        //------------------------------------------------------------------------------------------------
        void initialize()
        {
          using DataStore = MCF::Persistence::DataStore;

          CelesteEngine::Lua::registerUserType<DataStore>(
            "DataStore",
            "loadOrCreate", sol::factories(&Internals::loadOrCreate),
            "save", &Internals::save,
            "hasData", &DataStore::hasData,
            "getBool", &DataStore::getBool,
            "setBool", &DataStore::setBool);
        }
      }
    }
  }
}