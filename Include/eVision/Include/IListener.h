#ifndef __ILISTENER_H__
#define __ILISTENER_H__

#include "IBroadcaster.h"

namespace Euresys
{
  struct IBroadcaster;

  // The IBroadcaster interface.
  struct IListener
  {
    // The function used to prevent that the state of the sender has changed.
    virtual void Listen(IBroadcaster* sender) = 0;
  };
}

#endif //__ILISTENER_H__
