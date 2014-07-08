////////////////////////////////////////////////////////////////////////////////////////////////////
// LicenseMediator.h: LicenseMediator library header file for LicenseMediator 2.0.1
//
// LicenseMediator allows to set and retrieve information about Euresys licenses.
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __LICENSEMEDIATOR_H__
#define __LICENSEMEDIATOR_H__

#include <string>

#ifdef LICENSEMEDIATOR_NOT_USING_UNIDLL
#include "LicenseMediator_Enums.h"
#include "LicenseMediator_ExternC_Interface.h"
#else
#include "LicenseMediator_ExternC_DynamicLink.h"
#endif // LICENSEMEDIATOR_NOT_USING_UNIDLL


namespace Euresys
{
  namespace Utils 
  {
    struct NonCopyable 
    {
    protected:
      NonCopyable ( ) { }
      ~NonCopyable ( ) { }
    private:
      NonCopyable ( const NonCopyable& );
      const NonCopyable&  operator=   ( const NonCopyable& );
    };
  }

  namespace Properties
  {
    template<typename PropertyType > struct HolderTRO : private Euresys::Utils::NonCopyable
    {
      operator PropertyType ( ) const
      {
        return _value;
      }
      PropertyType  _value;
    private :
      HolderTRO<PropertyType >& operator=(const PropertyType& );
      HolderTRO<PropertyType>& operator=(const HolderTRO<PropertyType >&);
    };
  }

  class LicenseMediatorException
  {
  public:
    LicenseMediatorException(Euresys::LicenseMediatorError::Type error)
    {
      Error._value = error;
    }
    LicenseMediatorException& operator=(const LicenseMediatorException& other)
    {
      Error._value = other.Error._value;
      return *this;
    }
    LicenseMediatorException(const LicenseMediatorException& other)
    {
      Error._value = other.Error._value;
    }
    std::string What()
    {
      if (Error._value == LicenseMediatorError::MissingDLLCall)
      { // The DLL could not be on the system, so do not use a call to the DLL
        return "Missing DLL Call";
      }
      else
      {
        const char* retVal;
        global_GetErrorText_LicenseMediatorError_ConstString(static_cast<int>(Error._value), &retVal);
        return std::string(retVal);
      }
    }
    Euresys::Properties::HolderTRO<Euresys::LicenseMediatorError::Type> Error;
  };
}


inline void ThrowOnAnLMError(int error)
{
  if (static_cast<Euresys::LicenseMediatorError::Type>(error) != Euresys::LicenseMediatorError::Ok)
    throw Euresys::LicenseMediatorException(static_cast<Euresys::LicenseMediatorError::Type>(error));
}

namespace Euresys
{
  struct LicenseMediator
  {
    static void Refresh();
    static bool CheckLicenses(unsigned int licenses, MediumLocation::Type type, int index);
    static bool CheckLicenses(unsigned int licenses, MediumLocation::Type type);
    static bool CheckLicenses(unsigned int licenses);
    static bool CheckUserSecurityKey(const std::string& key, MediumLocation::Type type, int index);
    static bool CheckUserSecurityKey(const std::string& key, MediumLocation::Type type);
    static bool CheckUserSecurityKey(const std::string& key);
    static void SetUserSecurityKey(const std::string& key, MediumLocation::Type type, int index);
    static void SetUserSecurityKey(const std::string& key, MediumLocation::Type type);
    static void SetUserSecurityKey(const std::string& key);
    static unsigned int GetMediumCount(MediumLocation::Type type);
    static unsigned int GetMediumCount();
    static MediumLocation::Type GetMediumLocation(int index);
    static std::string GetMediumType(int index, Euresys::MediumLocation::Type type);
    static std::string GetMediumType(int index);
    static std::string GetUniqueID(int index, MediumLocation::Type type);
    static std::string GetUniqueID(int index);
    static std::string GetSerialNumber(int index, MediumLocation::Type type);
    static std::string GetSerialNumber(int index);
    static void EnterActivationCode(const std::string& activation, int index, MediumLocation::Type type);
    static void EnterActivationCode(const std::string& activation, int index);
    static unsigned int GetEuresysLicenseCount();
    static std::string GetLicenseName(unsigned int index);
    static License::Type GetLicenseID(unsigned int index);
  };


inline void LicenseMediator::Refresh()
{
  ThrowOnAnLMError(global_Refresh());
}

inline bool LicenseMediator::CheckLicenses(unsigned int licenses, MediumLocation::Type type, int index)
{
  int capt_type;
  capt_type = static_cast<int>(type);
  int capt_retVal;
  ThrowOnAnLMError(global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL(licenses, capt_type, index, &capt_retVal));
  bool retVal = true;
  if (capt_retVal == 0)
    retVal = false;
  return retVal;
}

inline bool LicenseMediator::CheckLicenses(unsigned int licenses, MediumLocation::Type type)
{
  int capt_type;
  capt_type = static_cast<int>(type);
  int capt_retVal;
  ThrowOnAnLMError(global_CheckLicenses_UINT32_MediumLocation_BOOL(licenses, capt_type, &capt_retVal));
  bool retVal = true;
  if (capt_retVal == 0)
    retVal = false;
  return retVal;
}

inline bool LicenseMediator::CheckLicenses(unsigned int licenses)
{
  int capt_retVal;
  ThrowOnAnLMError(global_CheckLicenses_UINT32_BOOL(licenses, &capt_retVal));
  bool retVal = true;
  if (capt_retVal == 0)
    retVal = false;
  return retVal;
}

inline bool LicenseMediator::CheckUserSecurityKey(const std::string& key, MediumLocation::Type type, int index)
{
  const char* capt_key = key.c_str();
  int capt_type = static_cast<int>(type);
  int capt_retVal;
  ThrowOnAnLMError(global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL(capt_key, capt_type, index, &capt_retVal));
  bool retVal = true;
  if (capt_retVal == 0)
    retVal = false;
  return retVal;
}

inline bool LicenseMediator::CheckUserSecurityKey(const std::string& key, MediumLocation::Type type)
{
  const char* capt_key = key.c_str();
  int capt_type = static_cast<int>(type);
  int capt_retVal;
  ThrowOnAnLMError(global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL(capt_key, capt_type, &capt_retVal));
  bool retVal = true;
  if (capt_retVal == 0)
    retVal = false;
  return retVal;
}

inline bool LicenseMediator::CheckUserSecurityKey(const std::string& key)
{
  const char* capt_key = key.c_str();
  int capt_retVal;
  ThrowOnAnLMError(global_CheckUserSecurityKey_ConstString_BOOL(capt_key, &capt_retVal));
  bool retVal = true;
  if (capt_retVal == 0)
    retVal = false;
  return retVal;
}

inline void LicenseMediator::SetUserSecurityKey(const std::string& key, MediumLocation::Type type, int index)
{
  const char* capt_key = key.c_str();
  int capt_type = static_cast<int>(type);
  ThrowOnAnLMError(global_SetUserSecurityKey_ConstString_MediumLocation_INT32(capt_key, capt_type, index));
}

inline void LicenseMediator::SetUserSecurityKey(const std::string& key, MediumLocation::Type type)
{
  const char* capt_key = key.c_str();
  int capt_type = static_cast<int>(type);
  ThrowOnAnLMError(global_SetUserSecurityKey_ConstString_MediumLocation(capt_key, capt_type));
}

inline void LicenseMediator::SetUserSecurityKey(const std::string& key)
{
  const char* capt_key = key.c_str();
  ThrowOnAnLMError(global_SetUserSecurityKey_ConstString(capt_key));
}

inline unsigned int LicenseMediator::GetMediumCount(MediumLocation::Type type)
{
  int capt_type = static_cast<int>(type);
  unsigned int retVal;
  ThrowOnAnLMError(global_GetMediumCount_MediumLocation_UINT32(capt_type, &retVal));
  return retVal;
}

inline unsigned int LicenseMediator::GetMediumCount()
{
  unsigned int retVal;
  ThrowOnAnLMError(global_GetMediumCount_UINT32(&retVal));
  return retVal;
}

inline MediumLocation::Type LicenseMediator::GetMediumLocation(int index)
{
  int retVal;
  ThrowOnAnLMError(global_GetMediumLocation_INT32_MediumLocation(index, &retVal));
  return static_cast<Euresys::MediumLocation::Type>(retVal);
}

inline std::string LicenseMediator::GetMediumType(int index, Euresys::MediumLocation::Type type)
{
  int capt_type = static_cast<int>(type);
  const char* capt_retVal;
  ThrowOnAnLMError(global_GetMediumType_INT32_MediumLocation_ConstString(index, capt_type, &capt_retVal));
  return std::string(capt_retVal);
}

inline std::string LicenseMediator::GetMediumType(int index)
{
  const char* capt_retVal;
  ThrowOnAnLMError(global_GetMediumType_INT32_ConstString(index, &capt_retVal));
  return std::string(capt_retVal);
}

inline std::string LicenseMediator::GetUniqueID(int index, MediumLocation::Type type)
{
  int capt_type = static_cast<int>(type);
  const char* retVal;
  ThrowOnAnLMError(global_GetUniqueID_INT32_MediumLocation_ConstString(index, capt_type, &retVal));
  return std::string(retVal);
}

inline std::string LicenseMediator::GetUniqueID(int index)
{
  const char* retVal;
  ThrowOnAnLMError(global_GetUniqueID_INT32_ConstString(index, &retVal));
  return std::string(retVal);
}

inline std::string LicenseMediator::GetSerialNumber(int index, MediumLocation::Type type)
{
  int capt_type = static_cast<int>(type);
  const char* retVal;
  ThrowOnAnLMError(global_GetSerialNumber_INT32_MediumLocation_ConstString(index, capt_type, &retVal));
  return std::string(retVal);
}

inline std::string LicenseMediator::GetSerialNumber(int index)
{
  const char* retVal;
  ThrowOnAnLMError(global_GetSerialNumber_INT32_ConstString(index, &retVal));
  return std::string(retVal);
}

inline void LicenseMediator::EnterActivationCode(const std::string& activation, int index, MediumLocation::Type type)
{
  const char* capt_activationCode = activation.c_str();
  int capt_type = static_cast<int>(type);
  ThrowOnAnLMError(global_EnterActivationCode_ConstString_INT32_MediumLocation(capt_activationCode, index, capt_type));
}

inline void LicenseMediator::EnterActivationCode(const std::string& activation, int index)
{
  const char* capt_activationCode = activation.c_str();
  ThrowOnAnLMError(global_EnterActivationCode_ConstString_INT32(capt_activationCode, index));
}

inline unsigned int LicenseMediator::GetEuresysLicenseCount()
{
  unsigned int retVal;
  ThrowOnAnLMError(global_GetEuresysLicenseCount_UINT32(&retVal));
  return retVal;
}

inline std::string LicenseMediator::GetLicenseName(unsigned int index)
{
  const char* retVal;
  ThrowOnAnLMError(global_GetLicenseName_UINT32_ConstString(index, &retVal));
  return std::string(retVal);
}

inline License::Type LicenseMediator::GetLicenseID(unsigned int index)
{
  int retVal;
  ThrowOnAnLMError(global_GetLicenseID_UINT32_License(index, &retVal));
  return static_cast<Euresys::License::Type>(retVal);
}

} // namespace Euresys
#endif //__LICENSEMEDIATOR_H__
