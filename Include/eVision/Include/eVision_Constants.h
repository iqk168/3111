#ifndef __EVISION_CONSTANTS_H__
#define __EVISION_CONSTANTS_H__

////////////////////////////////////////////////////////////////////////////////
// Numerical limits
//


#ifdef _MSC_VER

#define INT8_MIN ( static_cast<INT8>(-128))
#define INT8_MAX ( static_cast<INT8>(127))
#define INT16_MIN ( static_cast<INT16>(-32768))
#define INT16_MAX ( static_cast<INT16>(32767))
#define INT32_MIN ( static_cast<INT32>(-2147483648i32))
#define INT32_MAX ( static_cast<INT32>(2147483647i32))
#define INT64_MIN ( static_cast<INT64>(-0x7FFFFFFFFFFFFFFFui64))
#define INT64_MAX ( static_cast<INT64>(0x7FFFFFFFFFFFFFFFui64))

#define UINT8_MIN   (static_cast<UINT8>(0))
#define UINT8_MAX   (static_cast<UINT8>(0xFF))
#define UINT16_MIN  (static_cast<UINT16>(0))
#define UINT16_MAX  (static_cast<UINT16>(0xFFFF))
#define UINT32_MIN  (static_cast<UINT32>(0))
#define UINT32_MAX  (static_cast<UINT32>(0xFFFFFFFF))
#define UINT64_MAX  (static_cast<UINT64>(0xFFFFFFFFFFFFFFFF))

#elif defined __GNUC__ || defined E_BCB

#define INT8_MIN ( ( ( INT8)-127)-1)
#define INT8_MAX ( ( INT8)127)
#define INT16_MIN ( ( ( INT16)-32767L)-1)
#define INT16_MAX ( ( INT16)32767L)
#define INT32_MIN ( ( ( INT32)-2147483647L)-1)
#define INT32_MAX ( ( INT32)2147483647L)
#define INT64_MIN ( ( INT64)-0x7FFFFFFFFFFFFFFFL)
#define INT64_MAX ( ( INT64)0x7FFFFFFFFFFFFFFFL)

#define UINT8_MIN   (static_cast<UINT8>(0))
#define UINT8_MAX   (static_cast<UINT8>(0xFF))
#define UINT16_MIN  (static_cast<UINT16>(0))
#define UINT16_MAX  (static_cast<UINT16>(0xFFFF))
#define UINT32_MIN  (static_cast<UINT32>(0))
#define UINT32_MAX  (static_cast<UINT32>(0xFFFFFFFF))
#define UINT64_MAX  (static_cast<UINT64>(0xFFFFFFFFFFFFFFFF))

#else

#define INT8_MIN ( ( INT8)-128)
#define INT8_MAX ( ( INT8)127)
#define INT16_MIN ( ( INT16)-32768L)
#define INT16_MAX ( ( INT16)32767L)
#define INT32_MIN ( ( INT32)-2147483648L)
#define INT32_MAX ( ( INT32)2147483647L)
#define INT64_MIN ( ( INT64)-0x7FFFFFFFFFFFFFFFL)
#define INT64_MAX ( ( INT64)0x7FFFFFFFFFFFFFFFL)

#define UINT8_MIN   (static_cast<UINT8>(0))
#define UINT8_MAX   (static_cast<UINT8>(0xFF))
#define UINT16_MIN  (static_cast<UINT16>(0))
#define UINT16_MAX  (static_cast<UINT16>(0xFFFF))
#define UINT32_MIN  (static_cast<UINT32>(0))
#define UINT32_MAX  (static_cast<UINT32>(0xFFFFFFFF))
#define UINT64_MAX  (static_cast<UINT64>(0xFFFFFFFFFFFFFFFF))

#endif

#define FLOAT32_MAX 3.402823466e+38F
#define FLOAT32_MIN 1.175494351e-38F
#define FLOAT64_MAX 1.7976931348623158e+308
#define FLOAT64_MIN 2.2250738585072014e-308

#define UINT32_UNDEFINED  (static_cast<UINT32>(~0))
#define INT32_UNDEFINED   (static_cast<INT32>(~0))
#define BOOL_UNDEFINED    (static_cast<BOOL>(~0))
#define FLOAT32_UNDEFINED FLOAT32_MAX




#endif //__EVISION_CONSTANTS_H__
