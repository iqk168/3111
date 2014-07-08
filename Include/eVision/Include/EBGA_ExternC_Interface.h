#ifndef __EBGA_EXTERNC_INTERFACE_H__
#define __EBGA_EXTERNC_INTERFACE_H__

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
  E_DLL0 void E_DLL1 ConvertBgaToShape(void** dst, void* src);
  E_DLL0 int E_DLL1 Bga_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 Bga_getUnit_MeasurementUnits(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setUnit_MeasurementUnits(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_Inspect_ROIBW8(void* impl, void** sourceImage);
  E_DLL0 int E_DLL1 Bga_getBallDiameterTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallDiameterTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getBallCircularityTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallCircularityTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getBallOffsetXTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallOffsetXTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getBallOffsetYTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallOffsetYTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getBallPitchXTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getBallPitchYTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getBallDoughnutnessTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallDoughnutnessTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getBallQualityFactorTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallQualityFactorTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getWhiteOnBlack_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setWhiteOnBlack_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getBlobThreshold_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setBlobThreshold_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getMaxBlobArea_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setMaxBlobArea_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getMinBlobArea_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setMinBlobArea_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getSingulatedComponents_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setSingulatedComponents_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getMaxMissingBalls_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setMaxMissingBalls_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getOuterRoiDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setOuterRoiDiameter_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getInnerRoiDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setInnerRoiDiameter_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_getPackCloseBlobs_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setPackCloseBlobs_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getMeasureAssessment_BgaMeasureAssessment(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setMeasureAssessment_BgaMeasureAssessment(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getCircularityAssessment_BgaCircularityAssessment(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setCircularityAssessment_BgaCircularityAssessment(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getEnabledQualityDiagnostics_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setEnabledQualityDiagnostics_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getEnabledQualityStatistics_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setEnabledQualityStatistics_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getPackageCenterX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getPackageCenterY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDiagnostics_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_GetDiagnostic_BgaDiagnostics_BOOL(void* impl, int diagnostic, int* retVal);
  E_DLL0 int E_DLL1 Bga_getNumBallsFound_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getNumMissingBalls_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getNumClutter_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getNumExtraBalls_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getMinimumOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMaximumOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getAverageOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDeviationOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMinimumPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMaximumPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getAveragePitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDeviationPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMinimumDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMaximumDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getAverageDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDeviationDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMinimumCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMaximumCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getAverageCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDeviationCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMinimumDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMaximumDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getAverageDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDeviationDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMinimumQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getMaximumQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getAverageQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getDeviationQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_ClearBatchStatistics_BOOL(void* impl, int enable);
  E_DLL0 int E_DLL1 Bga_ClearBatchStatistics(void* impl);
  E_DLL0 int E_DLL1 Bga_DrawPackages_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Bga_DrawClutter_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Bga_DrawExtraBalls_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Bga_getNumBalls_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getComponentNumBalls_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_Load_ConstString_BOOL(void* impl, const char* pathName, int recurse);
  E_DLL0 int E_DLL1 Bga_Load_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Bga_Save_ConstString_BOOL(void* impl, const char* pathName, int recurse);
  E_DLL0 int E_DLL1 Bga_Save_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Bga_Draw_DrawAdapter_DrawingMode_BOOL(void* impl, void* context, int drawingMode, int recurse);
  E_DLL0 int E_DLL1 Bga_Draw_DrawAdapter_DrawingMode(void* impl, void* context, int drawingMode);
  E_DLL0 int E_DLL1 Bga_DrawArrayLabels_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Bga_EnableBehaviorFilter_ShapeBehavior_BOOL(void* impl, int behavior, int value);
  E_DLL0 int E_DLL1 Bga_EnableBehaviorFilter_ShapeBehavior(void* impl, int behavior);
  E_DLL0 int E_DLL1 Bga_DisableBehaviorFilter_ShapeBehavior(void* impl, int behavior);
  E_DLL0 int E_DLL1 Bga_getPackageWidth_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getPackageHeight_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_SetPackageSize_FLOAT32_FLOAT32(void* impl, float packageWidth, float packageHeight);
  E_DLL0 int E_DLL1 Bga_SetPackageSize_FLOAT32(void* impl, float packageWidth);
  E_DLL0 int E_DLL1 Bga_getPackageName_ConstString(void* impl, const char** retVal);
  E_DLL0 int E_DLL1 Bga_setPackageName_ConstString(void* impl, const char* retVal);
  E_DLL0 int E_DLL1 Bga_getBallDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_setBallDiameter_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Bga_GetBall_INT32_INT32_BgaBall(void* impl, int colIndex, int rowIndex, void** retVal);
  E_DLL0 int E_DLL1 Bga_getNumArrays_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getCurrentArray_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setCurrentArray_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getArray_BgaArray(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32_FLOAT32_INT32_INT32_FLOAT32_FLOAT32_BOOL(void* impl, float arrayWidth, float arrayHeight, int numCols, int numRows, float centerX, float centerY, int staggered);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32_FLOAT32_INT32_INT32_FLOAT32_FLOAT32(void* impl, float arrayWidth, float arrayHeight, int numCols, int numRows, float centerX, float centerY);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32_FLOAT32_INT32_INT32_FLOAT32(void* impl, float arrayWidth, float arrayHeight, int numCols, int numRows, float centerX);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32_FLOAT32_INT32_INT32(void* impl, float arrayWidth, float arrayHeight, int numCols, int numRows);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32_FLOAT32_INT32(void* impl, float arrayWidth, float arrayHeight, int numCols);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32_FLOAT32(void* impl, float arrayWidth, float arrayHeight);
  E_DLL0 int E_DLL1 Bga_AddArray_FLOAT32(void* impl, float arrayWidth);
  E_DLL0 int E_DLL1 Bga_AddArray(void* impl);
  E_DLL0 int E_DLL1 Bga_RemoveArray(void* impl);
  E_DLL0 int E_DLL1 Bga_getArrayNumBalls_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getArrayNumCols_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_getArrayNumRows_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_SetArrayLogicalSize_INT32_INT32_BOOL(void* impl, int numCols, int numRows, int staggered);
  E_DLL0 int E_DLL1 Bga_SetArrayLogicalSize_INT32_INT32(void* impl, int numCols, int numRows);
  E_DLL0 int E_DLL1 Bga_SetArrayLogicalSize_INT32(void* impl, int numCols);
  E_DLL0 int E_DLL1 Bga_SetArrayLogicalSize(void* impl);
  E_DLL0 int E_DLL1 Bga_getArraySizeX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getArraySizeY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_SetArrayPhysicalSize_FLOAT32_FLOAT32(void* impl, float width, float height);
  E_DLL0 int E_DLL1 Bga_SetArrayPhysicalSize_FLOAT32(void* impl, float width);
  E_DLL0 int E_DLL1 Bga_SetArrayPhysicalSize(void* impl);
  E_DLL0 int E_DLL1 Bga_getArrayPitchX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getArrayPitchY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_SetArrayPitches_FLOAT32_FLOAT32(void* impl, float pitchX, float pitchY);
  E_DLL0 int E_DLL1 Bga_SetArrayPitches_FLOAT32(void* impl, float pitchX);
  E_DLL0 int E_DLL1 Bga_SetArrayPitches(void* impl);
  E_DLL0 int E_DLL1 Bga_getArrayCenterX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getArrayCenterY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_SetArrayCenter_FLOAT32_FLOAT32(void* impl, float centerX, float centerY);
  E_DLL0 int E_DLL1 Bga_SetArrayCenter_FLOAT32(void* impl, float centerX);
  E_DLL0 int E_DLL1 Bga_SetArrayCenter(void* impl);
  E_DLL0 int E_DLL1 Bga_getSymmetry_BgaSymmetry(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setSymmetry_BgaSymmetry(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_ToggleBall_UINT32_UINT32(void* impl, unsigned int col, unsigned int row);
  E_DLL0 int E_DLL1 Bga_ToggleBalls_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int endX, int endY);
  E_DLL0 int E_DLL1 Bga_getNumComponents_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Bga_SetNumComponents_UINT32_UINT32(void* impl, unsigned int numCols, unsigned int numRows);
  E_DLL0 int E_DLL1 Bga_SetCurrentComponent_UINT32_UINT32(void* impl, unsigned int colIndex, unsigned int rowIndex);
  E_DLL0 int E_DLL1 Bga_getComponent_BgaComponent(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Bga_getComponentPitchX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_getComponentPitchY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Bga_SetComponentPitches_FLOAT32_FLOAT32(void* impl, float pitchX, float pitchY);
  E_DLL0 int E_DLL1 Bga_SetComponentPitches_FLOAT32(void* impl, float pitchX);
  E_DLL0 int E_DLL1 Bga_getRegularPlacement_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_SetNumComponents_UINT32(void* impl, unsigned int num);
  E_DLL0 int E_DLL1 Bga_SetCurrentComponent_UINT32(void* impl, unsigned int index);
  E_DLL0 int E_DLL1 Bga_SetComponentCenter_FLOAT32_FLOAT32(void* impl, float centerX, float centerY);
  E_DLL0 int E_DLL1 Bga_getAutoCalibrateBalls_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setAutoCalibrateBalls_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_getAutoCalibrateWorld_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Bga_setAutoCalibrateWorld_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Bga_SetBallPitchTolerance_FLOAT32_FLOAT32(void* impl, float xTolerance, float yTolerance);
  E_DLL0 int E_DLL1 Bga_SetBallPitchTolerance_FLOAT32(void* impl, float xTolerance);
  E_DLL0 int E_DLL1 Bga_getBlobs_CodedImage(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Bga_getBadBalls_Vector(void* impl, void** retVal);
  E_DLL0 int E_DLL1 Bga_getCurrentComponent_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Bga_setCurrentComponent_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Bga_SetBallOffsetTolerance_FLOAT32_FLOAT32(void* impl, float xTolerance, float yTolerance);
  E_DLL0 int E_DLL1 Bga_ArrangeDaughters(void* impl);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Bga_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Bga_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Bga_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 Bga_Dtor(void* impl);
  E_DLL0 void E_DLL1 ConvertBgaBallToShape(void** dst, void* src);
  E_DLL0 int E_DLL1 BgaBall_getDiagnostics_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaBall_GetDiagnostic_BgaDiagnostics_BOOL(void* impl, int diagnostic, int* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredOffsetX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredOffsetY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredPitchX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredPitchY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMeasuredQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getNumBatchSamples_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMinimumOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMaximumOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getAverageOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getDeviationOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMinimumPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMaximumPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getAveragePitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getDeviationPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMinimumDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMaximumDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getAverageDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getDeviationDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMinimumCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMaximumCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getAverageCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getDeviationCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMinimumDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMaximumDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getAverageDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getDeviationDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMinimumQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getMaximumQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getAverageQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getDeviationQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getCenter_Point(void* impl, void** retVal);
  E_DLL0 int E_DLL1 BgaBall_getRadius_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaBall_getComponentIndex_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaBall_getComponent_BgaComponent(void* impl, void** retVal);
  E_DLL0 int E_DLL1 BgaBall_getArray_BgaArray(void* impl, void** retVal);
  E_DLL0 int E_DLL1 BgaBall_getArrayIndex_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaBall_getBallRowIndex_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaBall_getBallColumnIndex_UINT32(void* impl, unsigned int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  BgaBall_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  BgaBall_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 BgaBall_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 BgaBall_Dtor(void* impl);
  E_DLL0 void E_DLL1 ConvertBgaArrayToShape(void** dst, void* src);
  E_DLL0 int E_DLL1 BgaArray_getInverseRowNumbering_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BgaArray_setInverseRowNumbering_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 BgaArray_getInverseColNumbering_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BgaArray_setInverseColNumbering_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 BgaArray_getCenter_Point(void* impl, void** retVal);
  E_DLL0 int E_DLL1 BgaArray_getStaggered_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 BgaArray_setStaggered_BOOL(void* impl, int retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  BgaArray_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  BgaArray_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 BgaArray_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 BgaArray_Dtor(void* impl);
  E_DLL0 void E_DLL1 ConvertBgaComponentToShape(void** dst, void* src);
  E_DLL0 int E_DLL1 BgaComponent_getNumBalls_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaComponent_SetCenter_FLOAT32_FLOAT32(void* impl, float centerX, float centerY);
  E_DLL0 int E_DLL1 BgaComponent_getNumBallsFound_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getNumMissingBalls_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDiagnostics_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 BgaComponent_GetDiagnostic_BgaDiagnostics_BOOL(void* impl, int diagnostic, int* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMinimumOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMaximumOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getAverageOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDeviationOffset_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMinimumPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMaximumPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getAveragePitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDeviationPitch_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMinimumDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMaximumDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getAverageDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDeviationDiameter_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMinimumCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMaximumCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getAverageCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDeviationCircularity_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMinimumDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMaximumDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getAverageDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDeviationDoughnutness_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMinimumQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getMaximumQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getAverageQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getDeviationQualityFactor_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 BgaComponent_getCenter_Point(void* impl, void** retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  BgaComponent_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  BgaComponent_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 BgaComponent_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 BgaComponent_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EBGA_EXTERNC_INTERFACE_H__
