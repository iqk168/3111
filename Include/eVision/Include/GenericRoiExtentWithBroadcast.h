#ifndef __GENERICROIEXTENTWITHBROADCAST_H__
#define __GENERICROIEXTENTWITHBROADCAST_H__

#include "IBroadcaster.h"
#include "IListener.h"
#include "Easy_EGenericROI.h"
#include "easy_properties_inl.h"

namespace Euresys
{
  namespace eVision
  {
    class GenericRoiExtentWithBroadcast : public IBroadcaster
    {
      // Wrapping members
    public:
      int handle_;
      FinalizeCallback callback_;

    private:
      INT32 orgX;
      INT32 orgY;
      INT32 width;
      INT32 height;
      // Vector of listeners.
      Euresys::eVision::Utils::Vector<IListener*> listOfListeners;

    protected:
      INT32 GetOrgX();
      INT32 GetOrgY();
      INT32 GetWidth();
      INT32 GetHeight();
      void SetOrgX(INT32 value);
      void SetOrgY(INT32 value);
      void SetWidth(INT32 value);
      void SetHeight(INT32 value);
      // Create static functions because different versions of VC6 have different sizes for pointers to member functions.
      static INT32 StaticGetOrgX(GenericRoiExtentWithBroadcast* impl);
      static INT32 StaticGetOrgY(GenericRoiExtentWithBroadcast* impl);
      static INT32 StaticGetWidth(GenericRoiExtentWithBroadcast* impl);
      static INT32 StaticGetHeight(GenericRoiExtentWithBroadcast* impl);
      static void StaticSetOrgX(GenericRoiExtentWithBroadcast* impl, INT32 value);
      static void StaticSetOrgY(GenericRoiExtentWithBroadcast* impl, INT32 value);
      static void StaticSetWidth(GenericRoiExtentWithBroadcast* impl, INT32 value);
      static void StaticSetHeight(GenericRoiExtentWithBroadcast* impl, INT32 value);
      void InitializeAdapters();
      void InternalCopyTo(const GenericRoiExtentWithBroadcast& src);

    public:
      Euresys::eVision::Utils::Properties::AdapterT<GenericRoiExtentWithBroadcast, INT32> OrgX;
      Euresys::eVision::Utils::Properties::AdapterT<GenericRoiExtentWithBroadcast, INT32> OrgY;
      Euresys::eVision::Utils::Properties::AdapterT<GenericRoiExtentWithBroadcast, INT32> Width;
      Euresys::eVision::Utils::Properties::AdapterT<GenericRoiExtentWithBroadcast, INT32> Height;

    public:
      E_DLL0 CONSTRUCTOR E_DLL1 GenericRoiExtentWithBroadcast();
      E_DLL0 CONSTRUCTOR E_DLL1 GenericRoiExtentWithBroadcast(const Euresys::eVision::GenericRoiExtent& genericRoiExtent);
      // Copy constructor.
      E_DLL0 CONSTRUCTOR E_DLL1 GenericRoiExtentWithBroadcast(const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast);
      // Assignation operator.
      E_DLL0 GenericRoiExtentWithBroadcast& E_DLL1 operator= (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast);
      E_DLL0 GenericRoiExtentWithBroadcast& E_DLL1 operator= (const GenericRoiExtent& genericRoiExtent);
      // Equality operator.
      E_DLL0 bool E_DLL1 operator== (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast) const;
      E_DLL0 bool E_DLL1 operator== (const GenericRoiExtent& genericRoiExtent) const;
      // Difference operator.
      E_DLL0 bool E_DLL1 operator!= (const GenericRoiExtentWithBroadcast& genericRoiExtentWithBroadcast) const;
      E_DLL0 bool E_DLL1 operator!= (const GenericRoiExtent& genericRoiExtent) const;
      // Cast operator
      operator GenericRoiExtent ( ) const
      {
        GenericRoiExtent genRoiExt;
        genRoiExt.OrgX = orgX;
        genRoiExt.OrgY = orgY;
        genRoiExt.Width = width;
        genRoiExt.Height = height;
        return genRoiExt;
      };
      // Implementation of IBroadcaster interface.
      E_DLL0 void E_DLL1 AddListener(IListener* listener);
      E_DLL0 void E_DLL1 RemoveListener(IListener* listener);
      E_DLL0 void E_DLL1 Broadcast();
      E_DLL0 const E_DLL1 Euresys::eVision::Utils::Vector<IListener*>& GetListeners();
    };
  }
}

#endif //__GENERICROIEXTENTWITHBROADCAST_H__
