#ifndef __GENERICROIEXTENTBROADCASTINGVECTOR_H__
#define __GENERICROIEXTENTBROADCASTINGVECTOR_H__

#include "IBroadcaster.h"
#include "IListener.h"
#include "GenericRoiExtentWithBroadcast.h"

namespace Euresys
{
  class GenericRoiExtentBroadcastingVector : public IBroadcaster, public IListener
  {
    // Wrapping members
  public:
    int handle_;
    FinalizeCallback callback_;
  public:
    E_DLL0 CONSTRUCTOR E_DLL1 GenericRoiExtentBroadcastingVector(INT32 size = 0);
    E_DLL0 CONSTRUCTOR E_DLL1 GenericRoiExtentBroadcastingVector(const GenericRoiExtentBroadcastingVector& array);
    E_DLL0 DESTRUCTOR E_DLL1 ~GenericRoiExtentBroadcastingVector();
    E_DLL0 const eVision::GenericRoiExtentWithBroadcast& E_DLL1 ItemAt(INT32 i) const;
    E_DLL0 eVision::GenericRoiExtentWithBroadcast& E_DLL1 ItemAt(INT32 i);
    E_DLL0 void E_DLL1 Add(const eVision::GenericRoiExtent& item);
    E_DLL0 void E_DLL1 AddOnce(const eVision::GenericRoiExtent& item);
    E_DLL0 void E_DLL1 InsertItem(const eVision::GenericRoiExtent& item, INT32 i);
    E_DLL0 INT32 E_DLL1 NbItems() const;
    E_DLL0 INT32 E_DLL1 Find(const eVision::GenericRoiExtent& item) const;
    E_DLL0 bool E_DLL1 Contains(const eVision::GenericRoiExtent& item) const;
    E_DLL0 void E_DLL1 Clear();
    E_DLL0 void E_DLL1 Remove(const eVision::GenericRoiExtent& item);
    E_DLL0 void E_DLL1 Remove(INT32 i);
    E_DLL0 void E_DLL1 SetSize(INT32 size);
    E_DLL0 eVision::GenericRoiExtentWithBroadcast& E_DLL1 operator[] (INT32 i);
    E_DLL0 const eVision::GenericRoiExtentWithBroadcast& E_DLL1 operator[] (INT32 i) const;
    E_DLL0 GenericRoiExtentBroadcastingVector& E_DLL1 operator= (const GenericRoiExtentBroadcastingVector& array);
    E_DLL0 bool E_DLL1 operator== (const GenericRoiExtentBroadcastingVector& array) const;
    E_DLL0 bool E_DLL1 operator!= (const GenericRoiExtentBroadcastingVector& array) const;
    E_DLL0 GenericRoiExtentBroadcastingVector& E_DLL1 operator+= (const Euresys::eVision::GenericRoiExtent& genericRoiExtent);
    E_DLL0 GenericRoiExtentBroadcastingVector& E_DLL1 operator+= (const EGenericROI& genericRoi);
  public:
    // Implementation of IBroadcaster interface.
    E_DLL0 void E_DLL1 Broadcast();
    E_DLL0 void E_DLL1 AddListener(Euresys::IListener* listener);
    E_DLL0 void E_DLL1 RemoveListener(Euresys::IListener* listener);
    E_DLL0 const Euresys::eVision::Utils::Vector<Euresys::IListener*>& E_DLL1 GetListeners();
    // Implementation of IListener interface.
    E_DLL0 void E_DLL1 Listen(Euresys::IBroadcaster* sender);

  protected:
    void InternalCopyTo(const GenericRoiExtentBroadcastingVector& src);

  protected:
    Euresys::eVision::Utils::Vector<Euresys::eVision::GenericRoiExtentWithBroadcast*> vect_;
    Euresys::eVision::Utils::Vector<Euresys::IListener*> listOfListeners_;
  };
}

#endif //__GENERICROIEXTENTBROADCASTINGVECTOR_H__
