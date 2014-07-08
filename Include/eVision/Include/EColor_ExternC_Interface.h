#ifndef __ECOLOR_EXTERNC_INTERFACE_H__
#define __ECOLOR_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 global_XyzToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_YuvToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_YiqToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_LshToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_VshToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_IshToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_YshToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_LabToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_LchToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_LuvToRgb_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToXyz_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToYuv_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToYiq_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLsh_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToVsh_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToIsh_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToYsh_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLab_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLch_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLuv_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_XyzToLab_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_LabToXyz_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_XyzToLuv_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_LuvToXyz_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToReducedXyz_C24_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_XyzToRgb_Xyz_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_YuvToRgb_Yuv_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_YiqToRgb_Yiq_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_LshToRgb_Lsh_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_VshToRgb_Vsh_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_IshToRgb_Ish_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_YshToRgb_Ysh_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_LabToRgb_Lab_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_LchToRgb_Lch_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_LuvToRgb_Luv_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToXyz_Rgb_Xyz(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToYuv_Rgb_Yuv(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToYiq_Rgb_Yiq(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLsh_Rgb_Lsh(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToVsh_Rgb_Vsh(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToIsh_Rgb_Ish(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToYsh_Rgb_Ysh(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLab_Rgb_Lab(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLch_Rgb_Lch(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToLuv_Rgb_Luv(void* in, void** out);
  E_DLL0 int E_DLL1 global_XyzToLab_Xyz_Lab(void* in, void** out);
  E_DLL0 int E_DLL1 global_LabToXyz_Lab_Xyz(void* in, void** out);
  E_DLL0 int E_DLL1 global_XyzToLuv_Xyz_Luv(void* in, void** out);
  E_DLL0 int E_DLL1 global_LuvToXyz_Luv_Xyz(void* in, void** out);
  E_DLL0 int E_DLL1 global_RgbToReducedXyz_Rgb_Xyz(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Ish_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Lab_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Lch_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Lsh_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Luv_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Rgb_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Vsh_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Xyz_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Yiq_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Ysh_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Quantize_Yuv_C24(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Ish(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Lab(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Lch(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Lsh(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Luv(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Rgb(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Vsh(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Xyz(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Yiq(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Ysh(void* in, void** out);
  E_DLL0 int E_DLL1 global_Dequantize_C24_Yuv(void* in, void** out);
  E_DLL0 int E_DLL1 global_Compose_ROIBW8_ROIBW8_ROIBW8_ROIC24_ColorLookup(void** sourceImageOfColor0, void** sourceImageOfColor1, void** sourceImageOfColor2, void** colorDestinationImage, void** lookup);
  E_DLL0 int E_DLL1 global_Compose_ROIBW8_ROIBW8_ROIBW8_ROIC24(void** sourceImageOfColor0, void** sourceImageOfColor1, void** sourceImageOfColor2, void** colorDestinationImage);
  E_DLL0 int E_DLL1 global_Decompose_ROIC24_ROIBW8_ROIBW8_ROIBW8_ColorLookup(void** colorSourceImage, void** destinationImageOfColor0, void** destinationImageOfColor1, void** destinationImageOfColor2, void** lookup);
  E_DLL0 int E_DLL1 global_Decompose_ROIC24_ROIBW8_ROIBW8_ROIBW8(void** colorSourceImage, void** destinationImageOfColor0, void** destinationImageOfColor1, void** destinationImageOfColor2);
  E_DLL0 int E_DLL1 global_GetComponent_ROIC24_ROIBW8_INT32_ColorLookup(void** colorSourceImage, void** bWDestinationImage, int component, void** lookup);
  E_DLL0 int E_DLL1 global_GetComponent_ROIC24_ROIBW8_INT32(void** colorSourceImage, void** bWDestinationImage, int component);
  E_DLL0 int E_DLL1 global_SetComponent_ROIBW8_ROIC24_INT32(void** bWSourceImage, void** colorDestinationImage, int component);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24_INT32_INT32_INT32_INT32_INT32_INT32(void** sourceImage, void** destinationImage, int rShiftX, int gShiftX, int bShiftX, int rShiftY, int gShiftY, int bShiftY);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24_INT32_INT32_INT32_INT32_INT32(void** sourceImage, void** destinationImage, int rShiftX, int gShiftX, int bShiftX, int rShiftY, int gShiftY);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24_INT32_INT32_INT32_INT32(void** sourceImage, void** destinationImage, int rShiftX, int gShiftX, int bShiftX, int rShiftY);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24_INT32_INT32_INT32(void** sourceImage, void** destinationImage, int rShiftX, int gShiftX, int bShiftX);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24_INT32_INT32(void** sourceImage, void** destinationImage, int rShiftX, int gShiftX);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24_INT32(void** sourceImage, void** destinationImage, int rShiftX);
  E_DLL0 int E_DLL1 global_RegisterPlanes_ROIC24_ROIC24(void** sourceImage, void** destinationImage);
  E_DLL0 int E_DLL1 global_Transform_ROIC24_ROIC24_ColorLookup(void** sourceImage, void** destinationImage, void** lookup);
  E_DLL0 int E_DLL1 global_TransformBayer_ROIBW8_ROIBW8_ColorLookup_BOOL_BOOL(void** sourceImage, void** destinationImage, void** lookup, int evenCol, int evenRow);
  E_DLL0 int E_DLL1 global_TransformBayer_ROIBW8_ROIBW8_ColorLookup_BOOL(void** sourceImage, void** destinationImage, void** lookup, int evenCol);
  E_DLL0 int E_DLL1 global_TransformBayer_ROIBW8_ROIBW8_ColorLookup(void** sourceImage, void** destinationImage, void** lookup);
  E_DLL0 int E_DLL1 global_PseudoColor_ROIBW8_ROIC24_PseudoColorLookup(void** sourceImage, void** destinationImage, void** lookup);
  E_DLL0 int E_DLL1 global_getSrcQuantization_ColorQuantization(int* retVal);
  E_DLL0 int E_DLL1 global_setSrcQuantization_ColorQuantization(int retVal);
  E_DLL0 int E_DLL1 global_getRgbStandard_RgbStandard(int* retVal);
  E_DLL0 int E_DLL1 global_setRgbStandard_RgbStandard(int retVal);
  E_DLL0 int E_DLL1 global_getDstQuantization_ColorQuantization(int* retVal);
  E_DLL0 int E_DLL1 global_setDstQuantization_ColorQuantization(int retVal);
  E_DLL0 int E_DLL1 global_Format422To444_ROIBW16_ROIC24_BOOL(void** sourceImage, void** destinationImage, int yFirst);
  E_DLL0 int E_DLL1 global_Format444To422_ROIC24_ROIBW16_BOOL(void** sourceImage, void** destinationImage, int yFirst);
  E_DLL0 int E_DLL1 global_BayerToC24_ROIBW8_ROIC24_BOOL_BOOL_BOOL_BOOL(void** sourceImage, void** destinationImage, int evenCol, int evenRow, int interpolate, int improved);
  E_DLL0 int E_DLL1 global_BayerToC24_ROIBW8_ROIC24_BOOL_BOOL_BOOL(void** sourceImage, void** destinationImage, int evenCol, int evenRow, int interpolate);
  E_DLL0 int E_DLL1 global_BayerToC24_ROIBW8_ROIC24_BOOL_BOOL(void** sourceImage, void** destinationImage, int evenCol, int evenRow);
  E_DLL0 int E_DLL1 global_BayerToC24_ROIBW8_ROIC24_BOOL(void** sourceImage, void** destinationImage, int evenCol);
  E_DLL0 int E_DLL1 global_BayerToC24_ROIBW8_ROIC24(void** sourceImage, void** destinationImage);
  E_DLL0 int E_DLL1 global_C24ToBayer_ROIC24_ROIBW8_BOOL_BOOL(void** sourceImage, void** destinationImage, int evenCol, int evenRow);
  E_DLL0 int E_DLL1 global_C24ToBayer_ROIC24_ROIBW8_BOOL(void** sourceImage, void** destinationImage, int evenCol);
  E_DLL0 int E_DLL1 global_C24ToBayer_ROIC24_ROIBW8(void** sourceImage, void** destinationImage);
  E_DLL0 int E_DLL1 global_AssignNearestClass_ROIC24_ROIBW8_C24Vector(void** sourceImage, void** destinationImage, void** classCenters);
  E_DLL0 int E_DLL1 global_AssignNearestClassCenter_ROIC24_ROIC24_C24Vector(void** sourceImage, void** destinationImage, void** classCenters);
  E_DLL0 int E_DLL1 global_ImproveClassCenters_ROIC24_C24Vector(void** sourceImage, void** classCenters);
  E_DLL0 int E_DLL1 global_ClassAverages_ROIC24_C24Vector_ColorVector(void** sourceImage, void** classCenters, void** averages);
  E_DLL0 int E_DLL1 global_ClassVariances_ROIC24_C24Vector_ColorVector_ColorVector(void** sourceImage, void** classCenters, void** averages, void** variances);
  E_DLL0 int E_DLL1 ColorLookup_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 ColorLookup_getInterpolation_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ColorLookup_setInterpolation_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 ColorLookup_getIndexBits_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ColorLookup_setIndexBits_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 ColorLookup_getColorSystemIn_ColorSystem(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ColorLookup_getColorSystemOut_ColorSystem(void* impl, int* retVal);
  E_DLL0 int E_DLL1 ColorLookup_Transform_C24_C24(void* impl, void* sourceImageColor, void** destinationImageColor);
  E_DLL0 int E_DLL1 ColorLookup_AdjustGainOffset_ColorSystem_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, int colorSystem, float gain0, float offset0, float gain1, float offset1, float gain2, float offset2);
  E_DLL0 int E_DLL1 ColorLookup_ConvertFromRgb_ColorSystem(void* impl, int colorSystem);
  E_DLL0 int E_DLL1 ColorLookup_ConvertToRgb_ColorSystem(void* impl, int colorSystem);
  E_DLL0 int E_DLL1 ColorLookup_Calibrate_C24_FLOAT32_FLOAT32_FLOAT32_C24_FLOAT32_FLOAT32_FLOAT32_C24_FLOAT32_FLOAT32_FLOAT32(void* impl, void* color0, float x0, float y0, float z0, void* color1, float x1, float y1, float z1, void* color2, float x2, float y2, float z2);
  E_DLL0 int E_DLL1 ColorLookup_WhiteBalance_FLOAT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, float gain, float gamma, float balanceRed, float balanceGreen, float balanceBlue);
  E_DLL0 int E_DLL1 ColorLookup_Transform_ROIC24_ROIC24(void* impl, void** sourceImage, void** destinationImage);
  E_DLL0 int E_DLL1 ColorLookup_Calibrate_C24_FLOAT32_FLOAT32_FLOAT32_C24_FLOAT32_FLOAT32_FLOAT32_C24_FLOAT32_FLOAT32_FLOAT32_C24_FLOAT32_FLOAT32_FLOAT32(void* impl, void* color0, float x0, float y0, float z0, void* color1, float x1, float y1, float z1, void* color2, float x2, float y2, float z2, void* color3, float x3, float y3, float z3);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  ColorLookup_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  ColorLookup_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 ColorLookup_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 ColorLookup_Dtor(void* impl);
  E_DLL0 int E_DLL1 PseudoColorLookup_SetShading_C24_C24_ColorSystem_BOOL(void* impl, void* black, void* white, int colorSystem, int wrap);
  E_DLL0 int E_DLL1 PseudoColorLookup_SetShading_C24_C24_ColorSystem(void* impl, void* black, void* white, int colorSystem);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  PseudoColorLookup_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  PseudoColorLookup_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 PseudoColorLookup_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 PseudoColorLookup_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __ECOLOR_EXTERNC_INTERFACE_H__
