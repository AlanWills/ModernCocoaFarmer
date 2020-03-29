#include "Lua/ScriptCommands/Persistence/DataObjectHandleScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "Persistence/DataObjectHandle.h"


namespace MCF::Lua::Persistence::DataObjectHandleScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    template <typename T>
    T get(MCF::Persistence::DataObjectHandle& dataMapHandle, const char* const key)
    {
      return dataMapHandle.get<T>(key, T());
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using DataObjectHandle = MCF::Persistence::DataObjectHandle;

    Celeste::Lua::registerUserType<DataObjectHandle>(
      "DataObjectHandle",
      // Is
      "isBool", &DataObjectHandle::is<bool>,
      "isInt", &DataObjectHandle::is<int>,
      "isUnsignedInt", &DataObjectHandle::is<unsigned int>,
      "isFloat", &DataObjectHandle::is<float>,
      "isString", &DataObjectHandle::is<std::string>,
      // Get
      "getBool", sol::overload(&Internals::get<bool>, &DataObjectHandle::get<bool>),
      "getInt", sol::overload(&Internals::get<int>, &DataObjectHandle::get<int>),
      "getUnsignedInt", sol::overload(&Internals::get<unsigned int>, &DataObjectHandle::get<unsigned int>),
      "getFloat", sol::overload(&Internals::get<float>, &DataObjectHandle::get<float>),
      "getString", sol::overload(&Internals::get<std::string>, &DataObjectHandle::get<std::string>),
      // Set
      "setBool", &DataObjectHandle::set<bool>,
      "setInt", &DataObjectHandle::set<int>,
      "setUnsignedInt", &DataObjectHandle::set<unsigned int>,
      "setFloat", &DataObjectHandle::set<float>,
      "setString", &DataObjectHandle::set<std::string>);
  }
}