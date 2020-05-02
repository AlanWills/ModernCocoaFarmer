#include "ScriptCommands/Persistence/DataStoreScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "Persistence/DataStore.h"
#include "Persistence/DataObjectHandle.h"
#include "Persistence/DataArrayHandle.h"
#include "Resources/ResourceUtils.h"
#include "Assert/Assert.h"


namespace sol
{
  template <>
  struct is_to_stringable<MCF::Persistence::DataStore> : std::false_type {};
}

namespace MCF::Lua::Persistence::DataStoreScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::unique_ptr<MCF::Persistence::DataStore> create()
    {
      return std::make_unique<MCF::Persistence::DataStore>();
    }

    //------------------------------------------------------------------------------------------------
    MCF::Persistence::DataStore loadOrCreate(const std::string& filePath)
    {
      using namespace Celeste::Resources;
      using namespace MCF::Persistence;

      observer_ptr<Data> data = getResourceManager().load<Data>(filePath);
      if (data == nullptr || data->getDocumentRoot() == nullptr)
      {
        return DataStore();
      }

      return DataStore::deserialize(*data->getDocumentRoot());
    }

    //------------------------------------------------------------------------------------------------
    bool save(MCF::Persistence::DataStore& dataStore, const std::string& filePath)
    {
      using namespace Celeste;
      using namespace Celeste::Resources;
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

    //------------------------------------------------------------------------------------------------
    template <typename T>
    T get(MCF::Persistence::DataStore& dataStore, const char* const key)
    {
      return dataStore.get<T>(key, T());
    }

    //------------------------------------------------------------------------------------------------
    MCF::Persistence::DataObjectHandle getObject(MCF::Persistence::DataStore& dataStore, const char* const key)
    {
      return MCF::Persistence::DataObjectHandle(dataStore, key);
    }

    //------------------------------------------------------------------------------------------------
    MCF::Persistence::DataArrayHandle getArray(MCF::Persistence::DataStore& dataStore, const char* const key)
    {
      return MCF::Persistence::DataArrayHandle(dataStore, key);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using DataStore = MCF::Persistence::DataStore;

    Celeste::Lua::registerUserType<DataStore>(
      state,
      "DataStore",
      "loadOrCreate", sol::factories(&Internals::loadOrCreate),
      "create", &Internals::create,
      "save", &Internals::save,
      // Is
      "isBool", &DataStore::is<bool>,
      "isInt", &DataStore::is<int>,
      "isUnsignedInt", &DataStore::is<unsigned int>,
      "isFloat", &DataStore::is<float>,
      "isString", &DataStore::is<std::string>,
      // Get
      "getBool", sol::overload(&Internals::get<bool>, &DataStore::get<bool>),
      "getInt", sol::overload(&Internals::get<int>, &DataStore::get<int>),
      "getUnsignedInt", sol::overload(&Internals::get<unsigned int>, &DataStore::get<unsigned int>),
      "getFloat", sol::overload(&Internals::get<float>, &DataStore::get<float>),
      "getString", sol::overload(&Internals::get<std::string>, &DataStore::get<std::string>),
      "getObject", &Internals::getObject,
      "getArray", &Internals::getArray,
      // Set
      "setBool", &DataStore::set<bool>,
      "setInt", &DataStore::set<int>,
      "setUnsignedInt", &DataStore::set<unsigned int>,
      "setFloat", &DataStore::set<float>,
      "setString", &DataStore::set<std::string>);
  }
}