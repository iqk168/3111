// Easy_Macros.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_MACROS_H__
#define __EASY_MACROS_H__


#if (_MSC_VER >= 1300)
#pragma warning( push )
#pragma warning( disable : 4702 ) 
#endif // (_MSC_VER >= 1300)

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <map>
#include <cstdio>
#include <cassert>

#if (_MSC_VER >= 1300)
#pragma warning( pop )
#endif // (_MSC_VER >= 1300)

#ifndef _WIN32

#if defined E_GCC  // Linux declarations

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>

#include "eVision_Types.h"

typedef void* HGDIOBJ;

#if !defined __WINTYPES_H
typedef struct EDC {
  Display *dpy;
  Drawable d;
  INT32 n32XOffset, n32YOffset;
  GC gc;
  HGDIOBJ GDIObject;

  EDC() { n32XOffset = n32YOffset = 0; }

} E_PACKED EDC;

typedef EDC* HDC;
#endif

#else

// STRICT definitions
// Courtesy of Microsoft Corporation
struct HWND__ { int unused; };
typedef struct HWND__ * HWND;
struct HDC__ { int unused; };
typedef struct HDC__ * HDC;
struct HANDLE__ { int unused; };
typedef struct HANDLE__ * HANDLE;

#endif

#else
// the following #define prevents the windows headers from defining min and max, which would break 
// some of the standard headers
#define NOMINMAX
#include <windows.h>
#endif

#if !defined TRUE
#define TRUE 1
#define FALSE 0
#endif

#if !defined NULL
#define NULL 0
#endif



////////////////////////////////////////////////////////////////////////////////
// Standard includes
//
#include <iostream>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Constant definitions
//
#include "eVision_Constants.h"
// Dragging handle size
#define HALF_HANDLE_SIZE 4

// Output a detailed error message and forward the status
#define ETrace( f) ( EETraceTraceMode( ), f, ETraceFullError( __FILE__, __LINE__, #f))

// Output a detailed error message and exit from the calling function without status
#define ETraceR( f) { f; if ( EGetError( ) != E_OK) return; }

// Output a detailed error message and exit from the calling function with status
#define ETraceRS( f) { f; if ( EGetError( ) != E_OK) return EGetError( ); }

// The following macros are no more in use in eVision libraries 
// but they will remain in the file for backward compatibility.
// Data member access helpers
#define GetBool( Member) \
  protected: BOOL m_b##Member;\
  public: E_DLL0 BOOL E_DLL1  Get##Member( )\

#define GetInt32( Member) \
  protected: INT32 m_n32##Member;\
  public: E_DLL0 INT32 E_DLL1  Get##Member( )\

#define GetUint32( Member) \
  protected: UINT32 m_un32##Member;\
  public: E_DLL0 UINT32 E_DLL1  Get##Member( )\

#define GetFloat32( Member) \
  protected: FLOAT32 m_f32##Member;\
  public: E_DLL0 FLOAT32 E_DLL1  Get##Member( )\

#define GetSetBool( Member) \
  protected: BOOL m_b##Member;\
  public: E_DLL0 BOOL E_DLL1  Get##Member( );\
  public: E_DLL0 void E_DLL1  Set##Member( BOOL b##Member)\

#define GetSetInt32( Member) \
  protected: INT32 m_n32##Member;\
  public: E_DLL0 INT32 E_DLL1  Get##Member( );\
  public: E_DLL0 void E_DLL1  Set##Member( INT32 n32##Member)\

#define GetSetUint32( Member) \
  protected: UINT32 m_un32##Member;\
  public: E_DLL0 UINT32 E_DLL1  Get##Member( );\
  public: E_DLL0 void E_DLL1  Set##Member( UINT32 un32##Member)\

#define GetSetFloat32( Member) \
  protected: FLOAT32 m_f32##Member;\
  public: E_DLL0 FLOAT32 E_DLL1  Get##Member( );\
  public: E_DLL0 void E_DLL1  Set##Member( FLOAT32 f32##Member)\

#define GetSetEnum( Type, Member) \
  protected: enum Type m_e##Member;\
  public: E_DLL0 enum Type E_DLL1  Get##Member( );\
  public: E_DLL0 void E_DLL1  Set##Member( enum Type e##Member)\


#endif //__EASY_MACROS_H__
