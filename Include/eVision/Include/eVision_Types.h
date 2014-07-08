#ifndef _EVISION_TYPES_H_
#define _EVISION_TYPES_H_

// Basic data types
typedef int BOOL;
typedef unsigned short UNICHAR;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed int INT32;
typedef unsigned int UINT32;
typedef float FLOAT32;
typedef double FLOAT64;

#ifdef __GNUC__
typedef long long INT64;
typedef unsigned long long UINT64;
#else
typedef __int64 INT64;
typedef unsigned __int64 UINT64;
#endif

typedef INT8* PINT8;
typedef INT16* PINT16;
typedef INT32* PINT32;
typedef UINT8* PUINT8;
typedef UINT16* PUINT16;
typedef UINT32* PUINT32;
typedef float* PFLOAT32;
typedef double* PFLOAT64;

typedef void (E_STDCALL *FinalizeCallback)(int handle);

#endif
