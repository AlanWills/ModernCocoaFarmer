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
    void LuaScriptReceiver::startListening()
    {
      m_isListening = true;
      m_communicationThread.swap(std::thread(&LuaScriptReceiver::continuallyListenForLua, this));
    }

    //------------------------------------------------------------------------------------------------
    void LuaScriptReceiver::continuallyListenForLua() const
    {
      m_server.Connect(27015);
    }
  }
}