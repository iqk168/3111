#ifndef __EASYFIND_EXTERNC_INTERFACE_H__
#define __EASYFIND_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 PatternFinder_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 PatternFinder_Learn_ROIBW8(void* impl, void* pattern);
  E_DLL0 int E_DLL1 PatternFinder_Learn_ROIBW8_ROIBW8(void* impl, void* pattern, void* dontCare);
  E_DLL0 int E_DLL1 PatternFinder_Find_ROIBW8_Vector(void* impl, void* source, void** retVal);
  E_DLL0 int E_DLL1 PatternFinder_Load_ConstString(void* impl, const char* path);
  E_DLL0 int E_DLL1 PatternFinder_Save_ConstString(void* impl, const char* path);
  E_DLL0 int E_DLL1 PatternFinder_getContrastMode_EasyFindContrast(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setContrastMode_EasyFindContrast(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getInterpolate_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setInterpolate_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getMaxInstances_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setMaxInstances_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getMinScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setMinScore_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 PatternFinder_getAngleBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setAngleBias_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 PatternFinder_getAngleTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setAngleTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 PatternFinder_getScaleBias_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setScaleBias_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 PatternFinder_getScaleTolerance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setScaleTolerance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 PatternFinder_getCoarseStage_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setCoarseStage_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getFineStage_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setFineStage_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getMinFeaturePoints_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setMinFeaturePoints_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getMaxFeaturePoints_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setMaxFeaturePoints_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getLearningDone_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_getFindExtension_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setFindExtension_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getPivot_PointF(void* impl, void** retVal);
  E_DLL0 int E_DLL1 PatternFinder_setPivot_PointF(void* impl, void* retVal);
  E_DLL0 int E_DLL1 PatternFinder_getPatternType_EasyFindPatternType(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setPatternType_EasyFindPatternType(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getLightBalance_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setLightBalance_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 PatternFinder_getLightBalancedImage_ImageBW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 PatternFinder_getTransitionThickness_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setTransitionThickness_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_DrawModel_DrawAdapter_FLOAT32_FLOAT32_INT32_INT32(void* impl, void* context, float zoomX, float zoomY, int panX, int panY);
  E_DLL0 int E_DLL1 PatternFinder_DrawModel_DrawAdapter_FLOAT32_FLOAT32_INT32(void* impl, void* context, float zoomX, float zoomY, int panX);
  E_DLL0 int E_DLL1 PatternFinder_DrawModel_DrawAdapter_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 PatternFinder_DrawModel_DrawAdapter_FLOAT32(void* impl, void* context, float zoomX);
  E_DLL0 int E_DLL1 PatternFinder_DrawModel_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 PatternFinder_getForcedThreshold_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setForcedThreshold_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getThinStructureMode_EasyFindThinStructureMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setThinStructureMode_EasyFindThinStructureMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_CreatePatternCopy_ImageBW8(void* impl, void** retVal);
  E_DLL0 int E_DLL1 PatternFinder_getLocalSearchMode_EasyFindLocalSearchMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setLocalSearchMode_EasyFindLocalSearchMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getAngleSearchExtent_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setAngleSearchExtent_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getScaleSearchExtent_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setScaleSearchExtent_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getXSearchExtent_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setXSearchExtent_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 PatternFinder_getYSearchExtent_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 PatternFinder_setYSearchExtent_INT32(void* impl, int retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  PatternFinder_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  PatternFinder_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 PatternFinder_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 PatternFinder_Dtor(void* impl);
  E_DLL0 int E_DLL1 FoundPattern_Draw_DrawAdapter_BOOL_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int edges, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 FoundPattern_Draw_DrawAdapter_BOOL_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int edges, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 FoundPattern_Draw_DrawAdapter_BOOL_FLOAT32_FLOAT32(void* impl, void* context, int edges, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 FoundPattern_Draw_DrawAdapter_BOOL_FLOAT32(void* impl, void* context, int edges, float zoomX);
  E_DLL0 int E_DLL1 FoundPattern_Draw_DrawAdapter_BOOL(void* impl, void* context, int edges);
  E_DLL0 int E_DLL1 FoundPattern_Draw_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 FoundPattern_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 FoundPattern_getAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 FoundPattern_setAngle_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 FoundPattern_getScale_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 FoundPattern_setScale_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 FoundPattern_getScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 FoundPattern_setScore_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 FoundPattern_getCenter_PointF(void* impl, void** retVal);
  E_DLL0 int E_DLL1 FoundPattern_setCenter_PointF(void* impl, void* retVal);
  E_DLL0 void E_DLL1 FoundPattern_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 FoundPattern_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EASYFIND_EXTERNC_INTERFACE_H__
