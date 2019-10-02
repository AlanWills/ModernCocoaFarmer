#pragma once


namespace MCF
{
  namespace Stats
  {
    class Modifier;
  }

  namespace Lua
  {
    namespace Stats
    {
      namespace ModifierScriptCommands
      {
        namespace Internals
        {
          bool isDeltaChange(MCF::Stats::Modifier& modifier);
          bool isPeriodicChange(MCF::Stats::Modifier& modifier);
        }

        void initialize();
      }
    }
  }
}