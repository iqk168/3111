// Easy_ErrorAndVersion.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_ERRORANDVERSION_H__
#define __EASY_ERRORANDVERSION_H__

#include "eVision_Types.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Error handling and miscellaneous
//

// Versioning
const E_DLL0 char* E_DLL1             EGetVersion           ( );
const E_DLL0 UNICHAR* E_DLL1          EGetVersionUnicode    ( );

// Tracing modes
E_DLL0 void E_DLL1                    ESetTraceMode         ( enum E_TRACE_MODE TraceMode);
E_DLL0 enum E_TRACE_MODE E_DLL1       EGetTraceMode         ( );

// Error conditions
E_DLL0 enum E_ERRORS E_DLL1           EGetError             ( );
E_DLL0 BOOL E_DLL1                    ESuccess              ( );
E_DLL0 BOOL E_DLL1                    EFailure              ( );

// Error messages
const E_DLL0 char* E_DLL1             EGetErrorText         ( );
const E_DLL0 UNICHAR* E_DLL1          EGetErrorTextUnicode  ( );

const E_DLL0 char* E_DLL1             EGetErrorText         ( enum E_ERRORS eError);
const E_DLL0 UNICHAR* E_DLL1          EGetErrorTextUnicode  ( enum E_ERRORS eError);

// Helpers
E_DLL0 enum E_ERRORS E_DLL1           EOk                   ( );
E_DLL0 enum E_ERRORS E_DLL1           ESetError             ( enum E_ERRORS eError);
E_DLL0 enum E_ERRORS E_DLL1           ETraceError           ( char* pszFunction);
E_DLL0 void E_DLL1                    EETraceTraceMode      ( );
E_DLL0 INT16 E_DLL1                   ETraceFullError       ( char* pszFile, int nLine, char* pszCall);

extern E_DLL0 BOOL E_DLL1             bEMacroTrace;


#endif //__EASY_ERRORANDVERSION_H__
