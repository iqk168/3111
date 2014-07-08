#ifndef __IBROADCASTER_H__
#define __IBROADCASTER_H__

#include "IListener.h"
#include "eVision_Vector_inl.h"


namespace Euresys
{
  struct IListener;

  // The IListener interface.
  struct IBroadcaster
  {
    // Method to broadcast information when a modification occurred.
    virtual void Broadcast() = 0;
    // Function to add a listener.
    virtual void AddListener(IListener* listener) = 0;
    // Function to remove a listener.
    virtual void RemoveListener(IListener* listener) = 0;
    // Returns the vector of IListener.
    virtual const Euresys::eVision::Utils::Vector<IListener*>& GetListeners() = 0;
  };
}

#endif //__IBROADCASTER_H__
