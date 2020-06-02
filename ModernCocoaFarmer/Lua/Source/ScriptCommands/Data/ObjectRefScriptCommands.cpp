#include "ScriptCommands/Data/ObjectRefScriptCommands.h"
#include "Data/ObjectRef.h"
#include "sol/sol.hpp"

using ObjectRef = MCF::Data::ObjectRef;


namespace sol
{
  template <>
  struct is_to_stringable<ObjectRef> : std::false_type {};
}

namespace MCF::Lua::Data::ObjectRefScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    template <typename T>
    T get(ObjectRef& objectRef, const char* const key)
    {
      return objectRef.get<T>(key, T());
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<ObjectRef>(
      "DataObjectHandle",
      // Get
      "getBool", sol::overload(&Internals::get<bool>, &ObjectRef::get<bool>),
      "getInt", sol::overload(&Internals::get<int>, &ObjectRef::get<int>),
      "getUnsignedInt", sol::overload(&Internals::get<unsigned int>, &ObjectRef::get<unsigned int>),
      "getFloat", sol::overload(&Internals::get<float>, &ObjectRef::get<float>),
      "getString", sol::overload(&Internals::get<std::string>, &ObjectRef::get<std::string>),
      // Set
      "setBool", &ObjectRef::set<bool>,
      "setInt", &ObjectRef::set<int>,
      "setUnsignedInt", &ObjectRef::set<unsigned int>,
      "setFloat", &ObjectRef::set<float>,
      "setString", &ObjectRef::set<std::string>);
  }
}