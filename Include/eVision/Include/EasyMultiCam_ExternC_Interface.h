#ifndef __EASYMULTICAM_EXTERNC_INTERFACE_H__
#define __EASYMULTICAM_EXTERNC_INTERFACE_H__

#if defined __GNUC__
#define E_DLL0
#else
#if defined E_STATIC
#define E_DLL0
#elif defined E_DLL_EXPORT
#define E_DLL0 _declspec( dllexport )
#else
#define E_DLL0 _declspec( dllimport )
#endif
#endif //__GNUC__
#define E_DLL1


#include "Easy_Extern_C.h"
#include "Extern_C_Types.h"


#ifdef E_EXTERN_C_BUILD

extern "C"
{
  E_DLL0 const char* E_DLL1 Configuration_Ctor(void** impl, int handle);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_MCPARAMID_INT32(void* impl, int param, int value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_MCPARAMID_ConstString(void* impl, int param, const char* value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_MCPARAMID_FLOAT64(void* impl, int param, double value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_MCPARAMID_Surface(void* impl, int param, void** value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_ConstString_INT32(void* impl, const char* param, int value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_ConstString_ConstString(void* impl, const char* param, const char* value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_ConstString_FLOAT64(void* impl, const char* param, double value);
  E_DLL0 const char* E_DLL1 Configuration_SetParam_ConstString_Surface(void* impl, const char* param, void** value);
  E_DLL0 const char* E_DLL1 Configuration_GetParam_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParamInt_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParam_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Configuration_GetParamString_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Configuration_GetParam_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParamFloat_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParam_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParamInt_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParam_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Configuration_GetParamString_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Configuration_GetParam_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Configuration_GetParamFloat_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 void* E_DLL1 Configuration_Config();
  E_DLL0 const char* E_DLL1 Configuration_GetParamInfo_MCPARAMID_ParameterInfo(void* impl, int param, void** info);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Configuration_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Configuration_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Configuration_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 Configuration_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 Surface_Ctor(void** impl, int handle);
  E_DLL0 const char* E_DLL1 Surface_SetParam_MCPARAMID_INT32(void* impl, int param, int value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_MCPARAMID_ConstString(void* impl, int param, const char* value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_MCPARAMID_FLOAT64(void* impl, int param, double value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_MCPARAMID_Surface(void* impl, int param, void** value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_ConstString_INT32(void* impl, const char* param, int value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_ConstString_ConstString(void* impl, const char* param, const char* value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_ConstString_FLOAT64(void* impl, const char* param, double value);
  E_DLL0 const char* E_DLL1 Surface_SetParam_ConstString_Surface(void* impl, const char* param, void** value);
  E_DLL0 const char* E_DLL1 Surface_GetParam_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Surface_GetParamInt_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Surface_GetParam_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Surface_GetParamString_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Surface_GetParam_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Surface_GetParamFloat_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Surface_GetParam_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Surface_GetParamInt_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Surface_GetParam_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Surface_GetParamString_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Surface_GetParam_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Surface_GetParamFloat_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Surface_Free(void* impl);
  E_DLL0 const char* E_DLL1 Surface_Reserve(void* impl);
  E_DLL0 const char* E_DLL1 Surface_GetParamInfo_MCPARAMID_ParameterInfo(void* impl, int param, void** info);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Surface_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Surface_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Surface_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 Surface_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 Board_Ctor_INT32(void** impl, int index, int handle);
  E_DLL0 const char* E_DLL1 Board_SetParam_MCPARAMID_INT32(void* impl, int param, int value);
  E_DLL0 const char* E_DLL1 Board_SetParam_MCPARAMID_ConstString(void* impl, int param, const char* value);
  E_DLL0 const char* E_DLL1 Board_SetParam_MCPARAMID_FLOAT64(void* impl, int param, double value);
  E_DLL0 const char* E_DLL1 Board_SetParam_MCPARAMID_Surface(void* impl, int param, void** value);
  E_DLL0 const char* E_DLL1 Board_SetParam_ConstString_INT32(void* impl, const char* param, int value);
  E_DLL0 const char* E_DLL1 Board_SetParam_ConstString_ConstString(void* impl, const char* param, const char* value);
  E_DLL0 const char* E_DLL1 Board_SetParam_ConstString_FLOAT64(void* impl, const char* param, double value);
  E_DLL0 const char* E_DLL1 Board_SetParam_ConstString_Surface(void* impl, const char* param, void** value);
  E_DLL0 const char* E_DLL1 Board_GetParam_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Board_GetParamInt_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Board_GetParam_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Board_GetParamString_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Board_GetParam_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Board_GetParamFloat_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Board_GetParam_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Board_GetParamInt_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Board_GetParam_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Board_GetParamString_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Board_GetParam_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Board_GetParamFloat_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Board_GetParamInfo_MCPARAMID_ParameterInfo(void* impl, int param, void** info);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Board_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Board_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Board_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 Board_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 Channel_Ctor_Board_INT32(void** impl, void** board, int connector, int handle);
  E_DLL0 const char* E_DLL1 Channel_Ctor_Board_String(void** impl, void** board, char* connector, int handle);
  E_DLL0 const char* E_DLL1 Channel_SetParam_MCPARAMID_INT32(void* impl, int param, int value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_MCPARAMID_ConstString(void* impl, int param, const char* value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_MCPARAMID_FLOAT64(void* impl, int param, double value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_MCPARAMID_Surface(void* impl, int param, void** value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_ConstString_INT32(void* impl, const char* param, int value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_ConstString_ConstString(void* impl, const char* param, const char* value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_ConstString_FLOAT64(void* impl, const char* param, double value);
  E_DLL0 const char* E_DLL1 Channel_SetParam_ConstString_Surface(void* impl, const char* param, void** value);
  E_DLL0 const char* E_DLL1 Channel_GetParam_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Channel_GetParamInt_MCPARAMID_INT32(void* impl, int param, int* value);
  E_DLL0 const char* E_DLL1 Channel_GetParam_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Channel_GetParamString_MCPARAMID_String_INT32(void* impl, int param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Channel_GetParam_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Channel_GetParamFloat_MCPARAMID_FLOAT64(void* impl, int param, double* value);
  E_DLL0 const char* E_DLL1 Channel_GetParam_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Channel_GetParamInt_ConstString_INT32(void* impl, const char* param, int* value);
  E_DLL0 const char* E_DLL1 Channel_GetParam_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Channel_GetParamString_ConstString_String_INT32(void* impl, const char* param, char** value, int maximumlength);
  E_DLL0 const char* E_DLL1 Channel_GetParam_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Channel_GetParamFloat_ConstString_FLOAT64(void* impl, const char* param, double* value);
  E_DLL0 const char* E_DLL1 Channel_SetActive(void* impl);
  E_DLL0 const char* E_DLL1 Channel_SetIdle(void* impl);
  E_DLL0 const char* E_DLL1 Channel_Prepare(void* impl);
  E_DLL0 const char* E_DLL1 Channel_WaitSignal_MCSIGNAL_UINT32_SignalInfo(void* impl, int signal, unsigned int timeout, void** info);
  E_DLL0 const char* E_DLL1 Channel_GetSignalInfo_MCSIGNAL_SignalInfo(void* impl, int signal, void** info);
  E_DLL0 const char* E_DLL1 Channel_UnregisterCallback_MCSIGNAL(void* impl, int signal);
  E_DLL0 const char* E_DLL1 Channel_RegisterCallback_CALLBACKFUNCTION_CALLBACKCONTEXT_INT32(void* impl, void* callbackFunction, void* callBackContext, int signal);
  E_DLL0 const char* E_DLL1 Channel_getSurface_UINT32_Surface(void* impl, unsigned int index, void** retVal);
  E_DLL0 const char* E_DLL1 Channel_GetParamInfo_MCPARAMID_ParameterInfo(void* impl, int param, void** info);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Channel_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Channel_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Channel_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 Channel_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 BoardList_Ctor(void** impl, int handle);
  E_DLL0 const char* E_DLL1 BoardList_GetBoardByDriverIndex_INT32_Board(void* impl, int driverindex, void** retVal);
  E_DLL0 const char* E_DLL1 BoardList_GetBoardByPciPosition_INT32_Board(void* impl, int pciposition, void** retVal);
  E_DLL0 const char* E_DLL1 BoardList_GetBoardByBoardName_ConstString_Board(void* impl, const char* boardname, void** retVal);
  E_DLL0 const char* E_DLL1 BoardList_GetBoardByBoardIdentifier_ConstString_Board(void* impl, const char* boardidentifier, void** retVal);
  E_DLL0 void* E_DLL1 BoardList_Boards();
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  BoardList_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  BoardList_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 BoardList_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 BoardList_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 SignalInfo_getSignal_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 SignalInfo_getSurf_Surface(void* impl, void** retVal);
  E_DLL0 const char* E_DLL1 SignalInfo_Ctor(void** impl, int handle);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  SignalInfo_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  SignalInfo_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 SignalInfo_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 SignalInfo_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 ParameterInfo_getName_ConstString(void* impl, const char** retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getIndex_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getType_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getMin_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getMax_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getDefault_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getHasDefault_BOOL(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getCategory_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getEnumCount_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getEnumList_INT32_EnumItem(void* impl, int index, void** retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getFilter_INT32_UINT32(void* impl, int index, unsigned int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getLevel_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getStorage_INT32(void* impl, int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getFilterData_INT32_UINT32(void* impl, int index, unsigned int* retVal);
  E_DLL0 const char* E_DLL1 ParameterInfo_getHandle_INT32(void* impl, int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  ParameterInfo_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  ParameterInfo_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 ParameterInfo_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 ParameterInfo_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 EnumItem_getItemName_ConstString(void* impl, const char** retVal);
  E_DLL0 const char* E_DLL1 EnumItem_getItemIndex_INT32(void* impl, int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  EnumItem_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  EnumItem_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 EnumItem_GetWrapper(int* handle, void* impl);
  E_DLL0 const char* E_DLL1 EnumItem_Dtor(void* impl);
  E_DLL0 const char* E_DLL1 global_UpdateImageConfig_MultiCamSurface_ImageBW8(void* surface, void** image);
  E_DLL0 const char* E_DLL1 global_UpdateImageConfig_MultiCamSurface_ImageBW16(void* surface, void** image);
  E_DLL0 const char* E_DLL1 global_UpdateImageConfig_MultiCamSurface_ImageC24(void* surface, void** image);
  E_DLL0 const char* E_DLL1 global_UpdateImageConfig_MultiCamSurface_ImageC24A(void* surface, void** image);
  E_DLL0 const char* E_DLL1 global_UpdateImageConfig_MultiCamSurface_ImageC15(void* surface, void** image);
  E_DLL0 const char* E_DLL1 global_UpdateImageConfig_MultiCamSurface_ImageC16(void* surface, void** image);
  E_DLL0 const char* E_DLL1 global_CreateImageBW8_MultiCamSurface_ImageBW8(void* surface, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateImageBW16_MultiCamSurface_ImageBW16(void* surface, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateImageC24_MultiCamSurface_ImageC24(void* surface, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateImageC24A_MultiCamSurface_ImageC24A(void* surface, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateImageC15_MultiCamSurface_ImageC15(void* surface, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateImageC16_MultiCamSurface_ImageC16(void* surface, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ImageBW8_MultiCamSurface(void* image, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ImageBW16_MultiCamSurface(void* image, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ImageC24_MultiCamSurface(void* image, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ImageC24A_MultiCamSurface(void* image, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ImageC15_MultiCamSurface(void* image, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ImageC16_MultiCamSurface(void* image, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_BW8Vector_MultiCamSurface(void* vector, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_BW16Vector_MultiCamSurface(void* vector, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_BW32Vector_MultiCamSurface(void* vector, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_C24Vector_MultiCamSurface(void* vector, void** retVal);
  E_DLL0 const char* E_DLL1 global_CreateSurface_ColorVector_MultiCamSurface(void* vector, void** retVal);
  E_DLL0 const char* E_DLL1 global_SetSurfaceForJpegHandler_MultiCamSurface_JpegHandler(void* surface, void** jpeghandler);
}

#endif // E_EXTERN_C_BUILD
#endif // __EASYMULTICAM_EXTERNC_INTERFACE_H__
