// Easy_Compilers.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_COMPILERS_H__
#define __EASY_COMPILERS_H__

// Compiler identification
//-----------------------------------------------------------------------------
#if defined __BORLANDC__
#define E_COMPILER "Borland C++ ( Builder)"
#define E_COMPILER_VERSION __BORLANDC__
#if __BORLANDC__ == 0x460
#define E_BC
#define E_BC45
#define E_COMPILER_SHORT_STRING  "BC45"
#elif __BORLANDC__ == 0x500
#define E_BC
#define E_BC50
#define E_COMPILER_SHORT_STRING  "BC50"
#elif __BORLANDC__ == 0x510 || __BORLANDC__ == 0x520 || __BORLANDC__ == 0x530
#define E_BCB
#define E_BCB1
#define E_COMPILER_SHORT_STRING  "BcB1"
#elif __BORLANDC__ == 0x540
#define E_BCB
#define E_BCB4
#define E_COMPILER_SHORT_STRING  "BcB4"
#elif __BORLANDC__ < 0x560
#define E_BCB
#define E_BCB5
#define E_COMPILER_SHORT_STRING  "BcB5"
#elif __BORLANDC__ == 0x560
#define E_BCB
#define E_BCB6
#define E_COMPILER_SHORT_STRING  "BcB6"
#elif __BORLANDC__ > 0x560
#define E_BCB
#define E_BCB6
// The following define was intended to identify the patched version but it prevent EasyCheck
// to open a directory with a '+' in the pathname, so it has been commented out
//    #define E_COMPILER_SHORT_STRING  "BcB6+"
#define E_COMPILER_SHORT_STRING  "BcB6"
#endif

// External linkage attributes ( DLL import/export)
#define E_DLL0
#if defined E_STATIC
#define E_DLL1
#elif defined E_DLL_EXPORT
#define E_DLL1 __export
#else
#define E_DLL1 __import
#endif

#define E_STDCALL __stdcall
#define E_CDECL __cdecl

//-----------------------------------------------------------------------------
#elif defined _MSC_VER

#define E_COMPILER "Microsoft Visual C++"
#define E_COMPILER_VERSION _MSC_VER
#define E_MSVC

#if ( _MSC_VER == 1000)
#define E_MSVC4
#define E_COMPILER_SHORT_STRING   "Ms40"
#elif ( _MSC_VER == 1100)
#define E_MSVC5
#define E_COMPILER_SHORT_STRING   "Ms50"
#elif ( _MSC_VER == 1200)
#define E_MSVC6
#define E_COMPILER_SHORT_STRING   "Ms60"
#elif ( _MSC_VER == 1300) // Visual Studio .NET
#define E_MSVC7
#define E_COMPILER_SHORT_STRING   "Ms70"
#elif ( _MSC_VER == 1310) // Visual Studio .NET 2003
#define E_MSVC71
#define E_COMPILER_SHORT_STRING   "Ms71"
#elif ( _MSC_VER == 1400) // Visual Studio .NET 2005
#define E_MSVC8
#define E_COMPILER_SHORT_STRING   "Ms80"
#endif

#if _MSC_VER < 1300
#pragma warning(disable : 4786) // identifier was truncated to '255' characters in the browser/debug information
#pragma warning(disable : 4660) // template-class specialization 'identifier' is already instantiated
#endif

// External linkage attributes ( DLL import/export)
#if defined E_STATIC
#define E_DLL0
#elif defined E_DLL_EXPORT
#define E_DLL0 _declspec( dllexport)
#else
#define E_DLL0 _declspec( dllimport)
#endif
#define E_DLL1

#define E_STDCALL __stdcall
#define E_CDECL __cdecl

//-----------------------------------------------------------------------------
#elif defined CADUL

#define E_COMPILER "CAD-UL Organon CC386"
#define E_COMPILER_VERSION V612E
#define CU_

#define E_STDCALL 
#define E_CDECL 

// External linkage attributes ( DLL import/export)
#define E_DLL0
#define E_DLL1

//-----------------------------------------------------------------------------
#elif defined __GNUC__

#define E_COMPILER "GNU C under Linux"
#define E_GCC
#define E_COMPILER_SHORT_STRING   "Gcc"
#define E_DLL0
#define E_DLL1

#define E_STDCALL 
#define E_CDECL 

//-----------------------------------------------------------------------------
#else

#error Unsupported compiler

#endif
//-----------------------------------------------------------------------------

#define CONSTRUCTOR
#define DESTRUCTOR

// Pack attribute for structures and unions ( needed by GCC only)
#ifdef __GNUC__
#define E_PACKED __attribute__( ( packed))
#else
#define E_PACKED
#endif


#endif //__EASY_COMPILERS_H__
