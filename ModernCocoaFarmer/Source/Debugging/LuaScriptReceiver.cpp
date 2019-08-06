#include "Debugging/LuaScriptReceiver.h"


namespace MCF
{
  namespace Debugging
  {
    //------------------------------------------------------------------------------------------------
    LuaScriptReceiver::LuaScriptReceiver() :
      m_isListening(false),
      m_communicationThread(),
      m_server()
    {
    }

    //------------------------------------------------------------------------------------------------
    LuaScriptReceiver::~LuaScriptReceiver()
    {
      m_isListening = false;
      m_communicationThread.join();
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::startListening() const
    {
      while (m_isListening)
      {

      }
    }
  }
}