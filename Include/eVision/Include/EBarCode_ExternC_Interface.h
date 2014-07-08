#ifndef __EBARCODE_EXTERNC_INTERFACE_H__
#define __EBARCODE_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 BarCode_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 BarCode_Detect_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 BarCode_Decode_EasyBarCodeSymbologies_String_UINT32(void* impl, int symbology, char** string, unsigned int length);
  E_DLL0 int E_DLL1 BarCode_Read_ROIBW8_String_UINT32(void* impl, void** sourceImage, char** string, unsigned int length);
  E_DLL0 int E_DLL1 BarCode_getNumEnabledSymbologies_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BarCode_getNumDecodedSymbologies_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BarCode_GetDecodedSymbology_UINT32_EasyBarCodeSymbologies(void* impl, unsigned int index, int* retVal);
  E_DLL0 int E_DLL1 BarCode_GetDecodedDirection_EasyBarCodeSymbologies_BOOL(void* impl, int symbology, int* directEncoding);
  E_DLL0 int E_DLL1 BarCode_GetDecodedAngle_EasyBarCodeSymbologies_FLOAT32_FLOAT32(void* impl, int symbology, float* decodedAngle, float cutAngle);
  E_DLL0 int E_DLL1 BarCode_GetDecodedAngle_EasyBarCodeSymbologies_FLOAT32(void* impl, int symbology, float* decodedAngle);
  E_DLL0 int E_DLL1 BarCode_GetDecodedAngle_FLOAT32_FLOAT32(void* impl, float* decodedAngle, float cutAngle);
  E_DLL0 int E_DLL1 BarCode_GetDecodedAngle_FLOAT32(void* impl, float* decodedAngle);
  E_DLL0 int E_DLL1 BarCode_GetDecodedRectangle_EasyBarCodeSymbologies_Rectangle(void* impl, int symbology, void** rect);
  E_DLL0 int E_DLL1 BarCode_GetDecodedRectangle_Rectangle(void* impl, void** rect);
  E_DLL0 int E_DLL1 BarCode_getStandardSymbologies_EasyBarCodeSymbologies(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BarCode_setStandardSymbologies_EasyBarCodeSymbologies(void* impl, int retVal);
  E_DLL0 int E_DLL1 BarCode_getAdditionalSymbologies_EasyBarCodeSymbologies(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BarCode_setAdditionalSymbologies_EasyBarCodeSymbologies(void* impl, int retVal);
  E_DLL0 int E_DLL1 BarCode_getKnownLocation_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BarCode_setKnownLocation_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 BarCode_getKnownModule_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BarCode_setKnownModule_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 BarCode_getModule_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_setModule_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 BarCode_getThicknessRatio_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_setThicknessRatio_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 BarCode_getVerifyChecksum_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BarCode_setVerifyChecksum_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 BarCode_Set_Rectangle(void* impl, void* rectangle);
  E_DLL0 int E_DLL1 BarCode_SetReadingCenter_FLOAT32_FLOAT32(void* impl, float relativeX, float relativeY);
  E_DLL0 int E_DLL1 BarCode_getRelativeReadingX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_getRelativeReadingY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_SetReadingSize_FLOAT32_FLOAT32(void* impl, float relativeSizeX, float relativeSizeY);
  E_DLL0 int E_DLL1 BarCode_getRelativeReadingSizeX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_getRelativeReadingSizeY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_getReadingAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_setReadingAngle_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 BarCode_Draw_DrawAdapter_DrawingMode_BOOL(void* impl, void* context, int drawingMode, int daughters);
  E_DLL0 int E_DLL1 BarCode_Draw_DrawAdapter_DrawingMode(void* impl, void* context, int drawingMode);
  E_DLL0 int E_DLL1 BarCode_Draw_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 BarCode_HitTest_BOOL_BOOL(void* impl, int daughters, int* retVal);
  E_DLL0 int E_DLL1 BarCode_HitTest_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BarCode_Drag_INT32_INT32(void* impl, int cursorX, int cursorY);
  E_DLL0 int E_DLL1 BarCode_SetZoom_FLOAT32_FLOAT32(void* impl, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 BarCode_SetZoom_FLOAT32(void* impl, float zoomX);
  E_DLL0 int E_DLL1 BarCode_SetZoom(void* impl);
  E_DLL0 int E_DLL1 BarCode_getZoomX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_getZoomY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_SetPan_FLOAT32_FLOAT32(void* impl, float panX, float panY);
  E_DLL0 int E_DLL1 BarCode_SetPan_FLOAT32(void* impl, float panX);
  E_DLL0 int E_DLL1 BarCode_SetPan(void* impl);
  E_DLL0 int E_DLL1 BarCode_getPanX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BarCode_getPanY_FLOAT32(void* impl, float* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  BarCode_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  BarCode_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 BarCode_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 BarCode_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EBARCODE_EXTERNC_INTERFACE_H__
