#include "Data/Ports/InputPort.h"
#include "Data/DataNodeComponent.h"


namespace MCF::Data
{
  //------------------------------------------------------------------------------------------------
  void InputPortBase::notifyNodeOnValueChange()
  {
    getNode().OnInputPortValueChanged(getName());
  }
}