#ifndef __EMATCH_EXTERNC_INTERFACE_H__
#define __EMATCH_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 Matcher_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 Matcher_Ctor_Matcher(void** impl, void* match, int handle);
  E_DLL0 int E_DLL1 Matcher_Ctor_UINT32(void** impl, unsigned int maximumNumberOfDegreesOfFreedom, int handle);
  E_DLL0 int E_DLL1 Matcher_CopyTo_Matcher(void* impl, void** match);
  E_DLL0 int E_DLL1 Matcher_CopyTo(void* impl);
  E_DLL0 int E_DLL1 Matcher_LearnPattern_ROIBW8(void* impl, void** pattern);
  E_DLL0 int E_DLL1 Matcher_LearnPattern_ROIC24(void* impl, void** pattern);
  E_DLL0 int E_DLL1 Matcher_ClearImage(void* impl);
  E_DLL0 int E_DLL1 Matcher_Match_ROIBW8(void* impl, void** image);
  E_DLL0 int E_DLL1 Matcher_Match_ROIC24(void* impl, void** image);
  E_DLL0 int E_DLL1 Matcher_getMinReducedArea_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_setMinReducedArea_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Matcher_getDontCareThreshold_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_setDontCareThreshold_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Matcher_getFilteringMode_EasyMatchFilteringMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_setFilteringMode_EasyMatchFilteringMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Matcher_getCorrelationMode_EasyMatchCorrelationMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_setCorrelationMode_EasyMatchCorrelationMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Matcher_getContrastMode_EasyMatchContrastMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_setContrastMode_EasyMatchContrastMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Matcher_getInterpolate_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_setInterpolate_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Matcher_getFinalReduction_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_setFinalReduction_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Matcher_getNumReductions_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_getMaxPositions_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_setMaxPositions_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Matcher_getMaxInitialPositions_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_setMaxInitialPositions_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Matcher_getMinScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMinScore_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getInitialMinScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setInitialMinScore_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_GetPixelDimensions_FLOAT32_FLOAT32(void* impl, float* width, float* height);
  E_DLL0 int E_DLL1 Matcher_SetPixelDimensions_FLOAT32_FLOAT32(void* impl, float width, float height);
  E_DLL0 int E_DLL1 Matcher_getMinAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMinAngle_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMaxAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMaxAngle_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMinScale_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMinScale_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMaxScale_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMaxScale_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMinScaleX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMinScaleX_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMaxScaleX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMaxScaleX_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMinScaleY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMinScaleY_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getMaxScaleY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_setMaxScaleY_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Matcher_getIsotropicScale_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_getAngleStep_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_getScaleStep_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_getScaleXStep_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_getScaleYStep_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Matcher_SetExtension_INT32_INT32(void* impl, int extensionX, int extensionY);
  E_DLL0 int E_DLL1 Matcher_getNumPositions_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_GetPosition_UINT32_MatchPosition(void* impl, unsigned int index, void** retVal);
  E_DLL0 int E_DLL1 Matcher_DrawPosition_DrawAdapter_UINT32_BOOL_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, unsigned int index, int bCorner, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Matcher_DrawPosition_DrawAdapter_UINT32_BOOL_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, unsigned int index, int bCorner, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Matcher_DrawPosition_DrawAdapter_UINT32_BOOL_FLOAT32_FLOAT32(void* impl, void* context, unsigned int index, int bCorner, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Matcher_DrawPosition_DrawAdapter_UINT32_BOOL_FLOAT32(void* impl, void* context, unsigned int index, int bCorner, float zoomX);
  E_DLL0 int E_DLL1 Matcher_DrawPosition_DrawAdapter_UINT32_BOOL(void* impl, void* context, unsigned int index, int bCorner);
  E_DLL0 int E_DLL1 Matcher_DrawPosition_DrawAdapter_UINT32(void* impl, void* context, unsigned int index);
  E_DLL0 int E_DLL1 Matcher_DrawPositions_DrawAdapter_BOOL_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int bCorner, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Matcher_DrawPositions_DrawAdapter_BOOL_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, int bCorner, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Matcher_DrawPositions_DrawAdapter_BOOL_FLOAT32_FLOAT32(void* impl, void* context, int bCorner, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Matcher_DrawPositions_DrawAdapter_BOOL_FLOAT32(void* impl, void* context, int bCorner, float zoomX);
  E_DLL0 int E_DLL1 Matcher_DrawPositions_DrawAdapter_BOOL(void* impl, void* context, int bCorner);
  E_DLL0 int E_DLL1 Matcher_DrawPositions_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Matcher_Load_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Matcher_Save_ConstString(void* impl, const char* pathName);
  E_DLL0 int E_DLL1 Matcher_getVersion_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Matcher_getIsPatternLearnt_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_getPatternWidth_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Matcher_getPatternHeight_INT32(void* impl, int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Matcher_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Matcher_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Matcher_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 Matcher_Dtor(void* impl);
  E_DLL0 int E_DLL1 MatchPosition_getCenterX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setCenterX_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getCenterY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setCenterY_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getAngle_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setAngle_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getScale_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setScale_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getScore_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setScore_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getInterpolated_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setInterpolated_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getScaleX_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setScaleX_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getScaleY_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setScaleY_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 MatchPosition_getAreaRatio_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 MatchPosition_setAreaRatio_FLOAT32(void* impl, float retVal);
  E_DLL0 void E_DLL1 MatchPosition_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 MatchPosition_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EMATCH_EXTERNC_INTERFACE_H__
