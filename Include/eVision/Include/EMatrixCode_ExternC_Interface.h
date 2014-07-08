#ifndef __EMATRIXCODE_EXTERNC_INTERFACE_H__
#define __EMATRIXCODE_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 MatrixCodeReader_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 MatrixCodeReader_getLearnMask_EasyMatrixCodeLearnParam_BOOL(void* impl, int learnParam, int* retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_setLearnMask_EasyMatrixCodeLearnParam_BOOL(void* impl, int learnParam, int retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_getComputeGrading_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_setComputeGrading_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_getMinimumPrintGrowth_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_setMinimumPrintGrowth_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_getMaximumPrintGrowth_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_setMaximumPrintGrowth_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_getNominalPrintGrowth_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_setNominalPrintGrowth_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_getTimeOut_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_setTimeOut_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_Reset(void* impl);
  E_DLL0 int E_DLL1 MatrixCodeReader_Read_ROIBW8_MatrixCode(void* impl, void** roi, void** retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_Learn_ROIBW8_MatrixCode(void* impl, void** roi, void** retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_LearnMore_ROIBW8_MatrixCode(void* impl, void** roi, void** retVal);
  E_DLL0 int E_DLL1 MatrixCodeReader_Load_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 MatrixCodeReader_Save_ConstString(void* impl, const char* pathName);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  MatrixCodeReader_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  MatrixCodeReader_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 MatrixCodeReader_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 MatrixCodeReader_Dtor(void* impl);
  E_DLL0 int E_DLL1 MatrixCode_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 MatrixCode_Ctor_MatrixCode(void** impl, void* other, int handle);
  E_DLL0 int E_DLL1 MatrixCode_getDecodedString_ConstString(void* impl, const char** retVal);
  E_DLL0 int E_DLL1 MatrixCode_setDecodedString_ConstString(void* impl, const char* retVal);
  E_DLL0 int E_DLL1 MatrixCode_getNumErrors_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setNumErrors_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getLogicalSize_EasyMatrixCodeLogicalSize(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setLogicalSize_EasyMatrixCodeLogicalSize(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getContrastType_EasyMatrixCodeContrast(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setContrastType_EasyMatrixCodeContrast(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getFlipping_EasyMatrixCodeFlipping(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setFlipping_EasyMatrixCodeFlipping(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getFamily_EasyMatrixCodeFamily(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setFamily_EasyMatrixCodeFamily(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getLogicalSizeWidth_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setLogicalSizeWidth_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getLogicalSizeHeight_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setLogicalSizeHeight_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getLocationThreshold_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setLocationThreshold_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getReadingThreshold_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setReadingThreshold_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getIsFound_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setIsFound_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getContrast_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setContrast_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCode_getContrastGrade_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setContrastGrade_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getPrintGrowth_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setPrintGrowth_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCode_getMeasuredPrintGrowth_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setMeasuredPrintGrowth_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCode_getPrintGrowthGrade_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setPrintGrowthGrade_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getAxialNonUniformity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setAxialNonUniformity_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCode_getAxialNonUniformityGrade_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setAxialNonUniformityGrade_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getUnusedErrorCorrection_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setUnusedErrorCorrection_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatrixCode_getUnusedErrorCorrectionGrade_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setUnusedErrorCorrectionGrade_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_getOverallGrade_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 MatrixCode_setOverallGrade_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 MatrixCode_Draw_DrawAdapter_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 MatrixCode_Draw_DrawAdapter_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 MatrixCode_Draw_DrawAdapter_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 MatrixCode_Draw_DrawAdapter_FLOAT32(void* impl, void* context, float zoomX);
  E_DLL0 int E_DLL1 MatrixCode_Draw_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 MatrixCode_DrawErrors_DrawAdapter_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 MatrixCode_DrawErrors_DrawAdapter_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 MatrixCode_DrawErrors_DrawAdapter_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 MatrixCode_DrawErrors_DrawAdapter_FLOAT32(void* impl, void* context, float zoomX);
  E_DLL0 int E_DLL1 MatrixCode_DrawErrors_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 MatrixCode_getCenter_PointF(void* impl, void** retVal);
  E_DLL0 int E_DLL1 MatrixCode_getAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatrixCode_getCorners_INT32_PointF(void* impl, int index, void** retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  MatrixCode_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  MatrixCode_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 MatrixCode_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 MatrixCode_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EMATRIXCODE_EXTERNC_INTERFACE_H__
