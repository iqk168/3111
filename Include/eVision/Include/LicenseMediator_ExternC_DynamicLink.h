#ifndef __LICENSEMEDIATOR_EXTERNC_DYNAMICLINK_H__
#define __LICENSEMEDIATOR_EXTERNC_DYNAMICLINK_H__


#include <string>

#ifndef __GNUC__
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#else
#define HMODULE void*
#include <dlfcn.h>
#include <limits.h>

#define MAX_PATH PATH_MAX

#endif //__GNUC__

#include "LicenseMediator_Enums.h"

enum
{
  kUniDllLoader_BuildObject,
  kUniDllLoader_GetFuncPtr,
  kUniDllLoader_DeleteObjet,
};

enum
{
  kUniDllLoader_Func_global_Refresh                                                         = 0,
  kUniDllLoader_Func_global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL                  = 1,
  kUniDllLoader_Func_global_CheckLicenses_UINT32_MediumLocation_BOOL                        = 2,
  kUniDllLoader_Func_global_CheckLicenses_UINT32_BOOL                                       = 3,
  kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL      = 4,
  kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL            = 5,
  kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_BOOL                           = 6,
  kUniDllLoader_Func_global_SetUserSecurityKey_ConstString_MediumLocation_INT32             = 7,
  kUniDllLoader_Func_global_SetUserSecurityKey_ConstString_MediumLocation                   = 8,
  kUniDllLoader_Func_global_SetUserSecurityKey_ConstString                                  = 9,
  kUniDllLoader_Func_global_GetMediumCount_MediumLocation_UINT32                            = 10,
  kUniDllLoader_Func_global_GetMediumCount_UINT32                                           = 11,
  kUniDllLoader_Func_global_GetMediumLocation_INT32_MediumLocation                          = 12,
  kUniDllLoader_Func_global_GetMediumType_INT32_MediumLocation_ConstString                  = 13,
  kUniDllLoader_Func_global_GetMediumType_INT32_ConstString                                 = 14,
  kUniDllLoader_Func_global_GetUniqueID_INT32_MediumLocation_ConstString                    = 15,
  kUniDllLoader_Func_global_GetUniqueID_INT32_ConstString                                   = 16,
  kUniDllLoader_Func_global_GetSerialNumber_INT32_MediumLocation_ConstString                = 17,
  kUniDllLoader_Func_global_GetSerialNumber_INT32_ConstString                               = 18,
  kUniDllLoader_Func_global_EnterActivationCode_ConstString_INT32_MediumLocation            = 19,
  kUniDllLoader_Func_global_EnterActivationCode_ConstString_INT32                           = 20,
  kUniDllLoader_Func_global_GetEuresysLicenseCount_UINT32                                   = 21,
  kUniDllLoader_Func_global_GetLicenseName_UINT32_ConstString                               = 22,
  kUniDllLoader_Func_global_GetLicenseID_UINT32_License                                     = 23,
  kUniDllLoader_Func_global_GetErrorText_LicenseMediatorError_ConstString                   = 24,
  kUniDllLoader_Func_global_Version_ConstString                                             = 25,
  kUniDllLoader_Func_global_Version2_ConstString_ConstString                                = 26,
  kUniDllLoader_Func_global_Version3_ConstString_UINT32_ConstString                         = 27,
  kUniDllLoader_FuncCount                                                                   = 28
};


typedef int (*kUniDllLoader_FuncType_global_Refresh)();
typedef int (*kUniDllLoader_FuncType_global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL)(unsigned int licenses, int type, int index, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_CheckLicenses_UINT32_MediumLocation_BOOL)(unsigned int licenses, int type, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_CheckLicenses_UINT32_BOOL)(unsigned int licenses, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL)(const char* key, int type, int index, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL)(const char* key, int type, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_BOOL)(const char* key, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_GetMediumCount_MediumLocation_UINT32)(int type, unsigned int* retVal);
typedef int (*kUniDllLoader_FuncType_global_GetMediumCount_UINT32)(unsigned int* retVal);
typedef int (*kUniDllLoader_FuncType_global_GetMediumLocation_INT32_MediumLocation)(int index, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_GetMediumType_INT32_MediumLocation_ConstString)(int index, int type, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_GetMediumType_INT32_ConstString)(int index, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_GetUniqueID_INT32_MediumLocation_ConstString)(int index, int type, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_GetUniqueID_INT32_ConstString)(int index, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_GetSerialNumber_INT32_MediumLocation_ConstString)(int index, int type, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_GetSerialNumber_INT32_ConstString)(int index, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_EnterActivationCode_ConstString_INT32_MediumLocation)(const char* activationCode, int index, int type);
typedef int (*kUniDllLoader_FuncType_global_EnterActivationCode_ConstString_INT32)(const char* activationCode, int index);
typedef int (*kUniDllLoader_FuncType_global_GetErrorText_LicenseMediatorError_ConstString)(int errorType, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString_MediumLocation_INT32)(const char* key, int type, int index);
typedef int (*kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString_MediumLocation)(const char* key, int type);
typedef int (*kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString)(const char* key);
typedef int (*kUniDllLoader_FuncType_global_GetEuresysLicenseCount_UINT32)(unsigned int* retVal);
typedef int (*kUniDllLoader_FuncType_global_GetLicenseName_UINT32_ConstString)(unsigned int index, const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_GetLicenseID_UINT32_License)(unsigned int index, int* retVal);
typedef int (*kUniDllLoader_FuncType_global_Version_ConstString)(const char** retVal);
typedef int (*kUniDllLoader_FuncType_global_Version2_ConstString_ConstString)(const unsigned char* nbr, const unsigned char** retVal);
typedef int (*kUniDllLoader_FuncType_global_Version3_ConstString_UINT32_ConstString)(const unsigned char* nbr, int len, const unsigned char** retVal);

#ifndef __GNUC__
typedef BOOL (__stdcall *Ptr_PathRemoveFileSpecW)(LPWSTR pszPath);
#endif //__GNUC__

struct UniDll_InitClass
{
  UniDll_InitClass(int n )
  {
    Dispatcher(kUniDllLoader_BuildObject, n);
  };

  ~UniDll_InitClass( )
  {
    Dispatcher(kUniDllLoader_DeleteObjet, 0);
  };

  static void DisplayLMErrorMessage(const char* message)
  {
#ifndef __GNUC__
    ::MessageBox(NULL, message, _T("License Mediator"), MB_OK | MB_ICONWARNING);
#else
    printf("Warning : %s.\n", message);
#endif
  }

  static void* Dispatcher(int action, int param)
  {
    static void* funcA[kUniDllLoader_FuncCount];
    static HMODULE hDll = 0;
    static int accRC = 0;
    void* rv = NULL;
    void** _funcA = funcA;
    HMODULE* _hDll = &hDll;
    int _accRC = accRC;

    switch( action )
    {
    case kUniDllLoader_BuildObject :
      {
        if (accRC != 0)
        {
          accRC++;
          return rv;
        }
        accRC++;

#ifndef __GNUC__
#pragma warning( push )
#pragma warning(disable : 4312)
        void* curModuleHandle = reinterpret_cast<void*>(param);
#pragma warning( pop )
        wchar_t curModulePath[_MAX_PATH];
        DWORD curModulePathLength = ::GetModuleFileNameW(reinterpret_cast<HMODULE>(curModuleHandle), curModulePath, _MAX_PATH);
        if(curModulePathLength == 0)
          HandleWindowsError(L"Cannot retrieve module file name");
        hDll = ::LoadLibraryW(L"shlwapi.dll");
        if (hDll == NULL)
          HandleWindowsError(L"shlwapi.dll");
        Ptr_PathRemoveFileSpecW ptr_PathRemoveFileSpecW = (Ptr_PathRemoveFileSpecW) ::GetProcAddress(hDll, "PathRemoveFileSpecW");
        if (ptr_PathRemoveFileSpecW == NULL)
        {
          HandleWindowsError(L"shlwapi.dll");
          break;
        }
        (*ptr_PathRemoveFileSpecW)(curModulePath);
        wcscat(curModulePath, L"\\LicenseMediator.dll");
        hDll = ::LoadLibraryW(curModulePath);
        if (hDll == NULL)
        {
          hDll = ::LoadLibraryW(L"LicenseMediator.dll");
          if (hDll == NULL)
            HandleWindowsError(L"LicenseMediator.dll");
        }
#define LicenseMediator_GetProcFromDLL GetProcAddress
#else
        hDll = dlopen("libLicenseMediator.so", RTLD_NOW);
        if (hDll == NULL)
          printf("%s\n", dlerror());
#define LicenseMediator_GetProcFromDLL dlsym
#endif //__GNUC__

        funcA[kUniDllLoader_Func_global_Refresh                                                     ] = LicenseMediator_GetProcFromDLL(hDll, "global_Refresh");
        funcA[kUniDllLoader_Func_global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL              ] = LicenseMediator_GetProcFromDLL(hDll, "global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL");
        funcA[kUniDllLoader_Func_global_CheckLicenses_UINT32_MediumLocation_BOOL                    ] = LicenseMediator_GetProcFromDLL(hDll, "global_CheckLicenses_UINT32_MediumLocation_BOOL");
        funcA[kUniDllLoader_Func_global_CheckLicenses_UINT32_BOOL                                   ] = LicenseMediator_GetProcFromDLL(hDll, "global_CheckLicenses_UINT32_BOOL");
        funcA[kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL  ] = LicenseMediator_GetProcFromDLL(hDll, "global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL");
        funcA[kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL        ] = LicenseMediator_GetProcFromDLL(hDll, "global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL");
        funcA[kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_BOOL                       ] = LicenseMediator_GetProcFromDLL(hDll, "global_CheckUserSecurityKey_ConstString_BOOL");
        funcA[kUniDllLoader_Func_global_SetUserSecurityKey_ConstString_MediumLocation_INT32         ] = LicenseMediator_GetProcFromDLL(hDll, "global_SetUserSecurityKey_ConstString_MediumLocation_INT32");
        funcA[kUniDllLoader_Func_global_SetUserSecurityKey_ConstString_MediumLocation               ] = LicenseMediator_GetProcFromDLL(hDll, "global_SetUserSecurityKey_ConstString_MediumLocation");
        funcA[kUniDllLoader_Func_global_SetUserSecurityKey_ConstString                              ] = LicenseMediator_GetProcFromDLL(hDll, "global_SetUserSecurityKey_ConstString");
        funcA[kUniDllLoader_Func_global_GetMediumCount_MediumLocation_UINT32                        ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetMediumCount_MediumLocation_UINT32");
        funcA[kUniDllLoader_Func_global_GetMediumCount_UINT32                                       ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetMediumCount_UINT32");
        funcA[kUniDllLoader_Func_global_GetMediumLocation_INT32_MediumLocation                      ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetMediumLocation_INT32_MediumLocation");
        funcA[kUniDllLoader_Func_global_GetMediumType_INT32_MediumLocation_ConstString              ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetMediumType_INT32_MediumLocation_ConstString");
        funcA[kUniDllLoader_Func_global_GetMediumType_INT32_ConstString                             ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetMediumType_INT32_ConstString");
        funcA[kUniDllLoader_Func_global_GetUniqueID_INT32_MediumLocation_ConstString                ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetUniqueID_INT32_MediumLocation_ConstString");
        funcA[kUniDllLoader_Func_global_GetUniqueID_INT32_ConstString                               ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetUniqueID_INT32_ConstString");
        funcA[kUniDllLoader_Func_global_GetSerialNumber_INT32_MediumLocation_ConstString            ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetSerialNumber_INT32_MediumLocation_ConstString");
        funcA[kUniDllLoader_Func_global_GetSerialNumber_INT32_ConstString                           ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetSerialNumber_INT32_ConstString");
        funcA[kUniDllLoader_Func_global_EnterActivationCode_ConstString_INT32_MediumLocation        ] = LicenseMediator_GetProcFromDLL(hDll, "global_EnterActivationCode_ConstString_INT32_MediumLocation");
        funcA[kUniDllLoader_Func_global_EnterActivationCode_ConstString_INT32                       ] = LicenseMediator_GetProcFromDLL(hDll, "global_EnterActivationCode_ConstString_INT32");
        funcA[kUniDllLoader_Func_global_GetEuresysLicenseCount_UINT32                               ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetEuresysLicenseCount_UINT32");
        funcA[kUniDllLoader_Func_global_GetLicenseName_UINT32_ConstString                           ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetLicenseName_UINT32_ConstString");
        funcA[kUniDllLoader_Func_global_GetLicenseID_UINT32_License                                 ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetLicenseID_UINT32_License");
        funcA[kUniDllLoader_Func_global_GetErrorText_LicenseMediatorError_ConstString               ] = LicenseMediator_GetProcFromDLL(hDll, "global_GetErrorText_LicenseMediatorError_ConstString");
        funcA[kUniDllLoader_Func_global_Version_ConstString                                         ] = LicenseMediator_GetProcFromDLL(hDll, "global_Version_ConstString");
        funcA[kUniDllLoader_Func_global_Version2_ConstString_ConstString                            ] = LicenseMediator_GetProcFromDLL(hDll, "global_Version2_ConstString_ConstString");
        funcA[kUniDllLoader_Func_global_Version3_ConstString_UINT32_ConstString                     ] = LicenseMediator_GetProcFromDLL(hDll, "global_Version3_ConstString_UINT32_ConstString");


        if (funcA[kUniDllLoader_Func_global_Version_ConstString] == NULL || funcA[kUniDllLoader_Func_global_Version2_ConstString_ConstString] == NULL || funcA[kUniDllLoader_Func_global_Version3_ConstString_UINT32_ConstString] == NULL)
        {
          for (int i=0;i<kUniDllLoader_FuncCount;i++)
            funcA[i]=NULL;
          return NULL;
        }
        const char* versionNumber;
        ((kUniDllLoader_FuncType_global_Version_ConstString)funcA[kUniDllLoader_Func_global_Version_ConstString])(&versionNumber);
        if (strcmp(versionNumber, "2.0.0.0") != 0)
          DisplayLMErrorMessage(_T("The version of the DLL doesn't match the version of the header."));
        unsigned char* version2 = reinterpret_cast<unsigned char*>(malloc(21*sizeof(unsigned char)));
        unsigned char v2_nbr[] = { 0x70, 0xed, 0x32, 0xc6, 0x08, 0x93, 0xfd, 0x00, 0xfe, 0x2b, 0xc1, 0x48, 0xf8, 0xa1, 0x57, 0x7b, 0x4f, 0x3d, 0x15, 0xa5  };                              
        ((kUniDllLoader_FuncType_global_Version2_ConstString_ConstString)funcA[kUniDllLoader_Func_global_Version2_ConstString_ConstString])(v2_nbr, const_cast<const unsigned char**>(&version2));
        char filename[MAX_PATH];

#ifndef __GNUC__
        if (GetModuleFileName(hDll, &(*filename), MAX_PATH) == 0)
        {
          DisplayLMErrorMessage(_T("The version of the DLL doesn't match the version of the header."));
          for (int i=0;i<kUniDllLoader_FuncCount;i++)
            funcA[i]=NULL;
          free(version2);
          return NULL;
        }
#else
/*
        FILE *fp_eVision_conf = ::fopen("/etc/eVision.conf", "r");
        if (fp_eVision_conf == NULL)
        {
          // If /etc/eVision.conf is not found, search in /usr/lib
          strcpy(filename, "/usr/lib/libLicenseMediator.so");
        }
        else
        {
          while (!feof(fp_eVision_conf))
          {
            fgets(buffer, sizeof(buffer), fp_eVision_conf);
            if (strstr(buffer, "EVISION_DLL_DIR=") != NULL)
            {
              break;
            }
          }

        }
        fclose(fp_eVision_conf);
*/
        //realpath("libLicenseMediator.so", filename);
        //printf("sizeof(filename)=%d\n", sizeof(filename));
        //printf("Real path=%s\n", filename);
        strcpy(filename, "/usr/lib/libLicenseMediator.so");
#endif // __GNUC__


        FILE* file = ::fopen(filename, "rb");
        int chose=::fseek(file, 0, SEEK_END);
        if (::fseek(file, 0, SEEK_END) != 0)
        {
          DisplayLMErrorMessage(_T("The version of the DLL doesn't match the version of the header."));
          for (int i=0;i<kUniDllLoader_FuncCount;i++)
            funcA[i]=NULL;
          free(version2);
          return NULL;
        }
        long len = ::ftell(file);
        if (::fseek(file, 0, SEEK_SET) != 0)
        {
          DisplayLMErrorMessage(_T("The version of the DLL doesn't match the version of the header."));
          for (int i=0;i<kUniDllLoader_FuncCount;i++)
            funcA[i]=NULL;
          free(version2);
          return NULL;
        }
        unsigned char* buffer = reinterpret_cast<unsigned char*>(malloc(len * sizeof(unsigned char)));
        size_t readChars = ::fread(buffer, sizeof(unsigned char), len, file);
        if (readChars != len)
        {
          DisplayLMErrorMessage(_T("The version of the DLL doesn't match the version of the header."));
          for (int i=0;i<kUniDllLoader_FuncCount;i++)
            funcA[i]=NULL;
          free(version2);
          free(buffer);
          return NULL;
        }
        unsigned char* version3 = reinterpret_cast<unsigned char*>(malloc(21*sizeof(unsigned char)));
        ((kUniDllLoader_FuncType_global_Version3_ConstString_UINT32_ConstString)funcA[kUniDllLoader_Func_global_Version3_ConstString_UINT32_ConstString])(reinterpret_cast<const unsigned char*>(buffer), len, const_cast<const unsigned char**>(&version3));
        for (int j=0; j<20; j++)
        {
          if (version2[j]!=version3[j])
          {
            DisplayLMErrorMessage(_T("The version of the DLL doesn't match the version of the header."));
            for (int i=0;i<kUniDllLoader_FuncCount;i++)
              funcA[i]=NULL;
            free(version2);
            free(buffer);
            free(version3);
            return NULL;
          }
        }
      }
      break;

    case kUniDllLoader_GetFuncPtr :
      rv = reinterpret_cast<void*>(funcA[param]);
      break;
    case kUniDllLoader_DeleteObjet :
      accRC--;
      if(accRC < 0)
        throw 0;
      if(accRC == 0)
#ifndef __GNUC__
        if (hDll != NULL)
          ::FreeLibrary(hDll);
#else
        if (hDll != NULL)
          dlclose(hDll);
#endif //__GNUC__
      break;
    }
    return rv;
  };

  static void HandleWindowsError(wchar_t* _msg)
  {
#ifndef __GNUC__
    LPWSTR lpMsgBuf;
    FormatMessageW( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, GetLastError(), 0, (LPWSTR)(&lpMsgBuf), 0, NULL);
    std::wstring msg(reinterpret_cast<wchar_t*>(lpMsgBuf));
    msg += _msg;
    ::MessageBoxW( NULL, msg.c_str(), L"License Mediator", MB_OK | MB_ICONERROR );
    ::LocalFree( reinterpret_cast<LPVOID>(lpMsgBuf) );
#else
    printf(reinterpret_cast<char *>(_msg));
#endif //__GNUC__
  };
};

#ifndef UNIDLL_MANUAL_INIT
// if this symbol is defined, this means the UNIDLL boot process
// must be triggered manually by calling the UniDll_InitClass::BootDll(hModule)
// static function. This function will retrieve the path of the supplied module
// and will first set the current folder to the one containing the module before
// trying to load "LicenseMediator.dll". Under Linux, nothing is done before
// loading the .so file.
static UniDll_InitClass UniDllLoader_Instance = 0;
#endif //UNIDLL_MANUAL_INIT

inline int global_Refresh()
{
    void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_Refresh);
    kUniDllLoader_FuncType_global_Refresh func = (kUniDllLoader_FuncType_global_Refresh)(vfunc);
    if (func == NULL)
      return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
    return func();
}

inline int global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL(unsigned int licenses, int type, int index, int* retVal)
{
    void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL);
    kUniDllLoader_FuncType_global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL func = (kUniDllLoader_FuncType_global_CheckLicenses_UINT32_MediumLocation_INT32_BOOL)(vfunc);
    if (func == NULL)
      return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
    return func(licenses, type, index, retVal);
}

inline int global_CheckLicenses_UINT32_MediumLocation_BOOL(unsigned int licenses, int type, int* retVal)
{
    void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_CheckLicenses_UINT32_MediumLocation_BOOL);
    kUniDllLoader_FuncType_global_CheckLicenses_UINT32_MediumLocation_BOOL func = (kUniDllLoader_FuncType_global_CheckLicenses_UINT32_MediumLocation_BOOL)(vfunc);
    if (func == NULL)
      return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
    return func(licenses, type, retVal);
}

inline int global_CheckLicenses_UINT32_BOOL(unsigned int licenses, int* retVal)
{
    void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_CheckLicenses_UINT32_BOOL);
    kUniDllLoader_FuncType_global_CheckLicenses_UINT32_BOOL func = (kUniDllLoader_FuncType_global_CheckLicenses_UINT32_BOOL)(vfunc);
    if (func == NULL)
      return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
    return func(licenses, retVal);
}

inline int global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL(const char* key, int type, int index, int* retVal)
{
    void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL);
    kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL func = (kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_MediumLocation_INT32_BOOL)(vfunc);
    if (func == NULL)
      return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
    return func(key, type, index, retVal);
}

inline int global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL(const char* key, int type, int* retVal)
{
    void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL);
    kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL func = (kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_MediumLocation_BOOL)(vfunc);
    if (func == NULL)
      return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
    return func(key, type, retVal);
}

inline int global_CheckUserSecurityKey_ConstString_BOOL(const char* key, int* retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_CheckUserSecurityKey_ConstString_BOOL);
  kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_BOOL func = (kUniDllLoader_FuncType_global_CheckUserSecurityKey_ConstString_BOOL)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(key, retVal);
}

inline int global_GetMediumCount_MediumLocation_UINT32(int type, unsigned int* retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetMediumCount_MediumLocation_UINT32);
  kUniDllLoader_FuncType_global_GetMediumCount_MediumLocation_UINT32 func = (kUniDllLoader_FuncType_global_GetMediumCount_MediumLocation_UINT32)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(type, retVal);
}

inline int global_GetMediumCount_UINT32(unsigned int* retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetMediumCount_UINT32);
  kUniDllLoader_FuncType_global_GetMediumCount_UINT32 func = (kUniDllLoader_FuncType_global_GetMediumCount_UINT32)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(retVal);
}

inline int global_GetMediumLocation_INT32_MediumLocation(int index, int* retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetMediumLocation_INT32_MediumLocation);
  kUniDllLoader_FuncType_global_GetMediumLocation_INT32_MediumLocation func = (kUniDllLoader_FuncType_global_GetMediumLocation_INT32_MediumLocation)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, retVal);
}

inline int global_GetMediumType_INT32_MediumLocation_ConstString(int index, int type, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetMediumType_INT32_MediumLocation_ConstString);
  kUniDllLoader_FuncType_global_GetMediumType_INT32_MediumLocation_ConstString func = (kUniDllLoader_FuncType_global_GetMediumType_INT32_MediumLocation_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, type, retVal);
}

inline int global_GetMediumType_INT32_ConstString(int index, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetMediumType_INT32_ConstString);
  kUniDllLoader_FuncType_global_GetMediumType_INT32_ConstString func = (kUniDllLoader_FuncType_global_GetMediumType_INT32_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, retVal);
}

inline int global_GetUniqueID_INT32_MediumLocation_ConstString(int index, int type, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetUniqueID_INT32_MediumLocation_ConstString);
  kUniDllLoader_FuncType_global_GetUniqueID_INT32_MediumLocation_ConstString func = (kUniDllLoader_FuncType_global_GetUniqueID_INT32_MediumLocation_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, type, retVal);
}

inline int global_GetUniqueID_INT32_ConstString(int index, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetUniqueID_INT32_ConstString);
  kUniDllLoader_FuncType_global_GetUniqueID_INT32_ConstString func = (kUniDllLoader_FuncType_global_GetUniqueID_INT32_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, retVal);
}

inline int global_GetSerialNumber_INT32_MediumLocation_ConstString(int index, int type, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetSerialNumber_INT32_MediumLocation_ConstString);
  kUniDllLoader_FuncType_global_GetSerialNumber_INT32_MediumLocation_ConstString func = (kUniDllLoader_FuncType_global_GetSerialNumber_INT32_MediumLocation_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, type, retVal);
}

inline int global_GetSerialNumber_INT32_ConstString(int index, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetSerialNumber_INT32_ConstString);
  kUniDllLoader_FuncType_global_GetSerialNumber_INT32_ConstString func = (kUniDllLoader_FuncType_global_GetSerialNumber_INT32_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, retVal);
}

inline int global_EnterActivationCode_ConstString_INT32_MediumLocation(const char* activationCode, int index, int type)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_EnterActivationCode_ConstString_INT32_MediumLocation);
  kUniDllLoader_FuncType_global_EnterActivationCode_ConstString_INT32_MediumLocation func = (kUniDllLoader_FuncType_global_EnterActivationCode_ConstString_INT32_MediumLocation)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(activationCode, index, type);
}

inline int global_EnterActivationCode_ConstString_INT32(const char* activationCode, int index)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_EnterActivationCode_ConstString_INT32);
  kUniDllLoader_FuncType_global_EnterActivationCode_ConstString_INT32 func = (kUniDllLoader_FuncType_global_EnterActivationCode_ConstString_INT32)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(activationCode, index);
}

inline int global_GetErrorText_LicenseMediatorError_ConstString(int errorType, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetErrorText_LicenseMediatorError_ConstString);
  kUniDllLoader_FuncType_global_GetErrorText_LicenseMediatorError_ConstString func = (kUniDllLoader_FuncType_global_GetErrorText_LicenseMediatorError_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(errorType, retVal);
}

inline int global_SetUserSecurityKey_ConstString_MediumLocation_INT32(const char* key, int type, int index)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_SetUserSecurityKey_ConstString_MediumLocation_INT32);
  kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString_MediumLocation_INT32 func = (kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString_MediumLocation_INT32)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(key, type, index);
}

inline int global_SetUserSecurityKey_ConstString_MediumLocation(const char* key, int type)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_SetUserSecurityKey_ConstString_MediumLocation);
  kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString_MediumLocation func = (kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString_MediumLocation)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(key, type);
}

inline int global_SetUserSecurityKey_ConstString(const char* key)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_SetUserSecurityKey_ConstString);
  kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString func = (kUniDllLoader_FuncType_global_SetUserSecurityKey_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(key);
}

inline int global_GetEuresysLicenseCount_UINT32(unsigned int* retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetEuresysLicenseCount_UINT32);
  kUniDllLoader_FuncType_global_GetEuresysLicenseCount_UINT32 func = (kUniDllLoader_FuncType_global_GetEuresysLicenseCount_UINT32)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(retVal);
}

inline int global_GetLicenseName_UINT32_ConstString(unsigned int index, const char** retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetLicenseName_UINT32_ConstString);
  kUniDllLoader_FuncType_global_GetLicenseName_UINT32_ConstString func = (kUniDllLoader_FuncType_global_GetLicenseName_UINT32_ConstString)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, retVal);
}

inline int global_GetLicenseID_UINT32_License(unsigned int index, int* retVal)
{
  void* vfunc = UniDll_InitClass::Dispatcher(kUniDllLoader_GetFuncPtr, kUniDllLoader_Func_global_GetLicenseID_UINT32_License);
  kUniDllLoader_FuncType_global_GetLicenseID_UINT32_License func = (kUniDllLoader_FuncType_global_GetLicenseID_UINT32_License)(vfunc);
  if (func == NULL)
    return static_cast<int>(Euresys::LicenseMediatorError::MissingDLLCall);
  return func(index, retVal);
}

#endif //__LICENSEMEDIATOR_EXTERNC_DYNAMICLINK_H__
