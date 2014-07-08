// Easy_License.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_LICENSE_H__
#define __EASY_LICENSE_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// License management
//
E_DLL0 void E_DLL1                    ESetCustomerCode      (const char* userCode);

// Following methods are OBSOLETE and should not be used for new developments
// Use Euresys License Mediator instead
E_DLL0 UINT32 E_DLL1                  EGetLicenseSet        ( UINT32 un32Subset = 0);
E_DLL0 BOOL E_DLL1                    ECheckLicense         ( enum E_EVISION_LICENSES eLicense);

namespace Euresys
{
  namespace eVision
  {
    namespace Licenses {
      namespace Location {
        enum Type {
          Auto,
          EureCard,
          SentinelDongle
        };
      };

      E_DLL0 void E_DLL1 SetOemKey(char key[8], Location::Type where= Location::Auto, int index= -1);
      E_DLL0 BOOL E_DLL1 CheckOemKey(char key[8], Location::Type where= Location::Auto, int index= -1);
    }
  }
}

#endif //__EASY_LICENSE_H__
