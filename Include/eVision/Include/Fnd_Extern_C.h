#ifndef __EFIND_EXTERN_C_H__
#define __EFIND_EXTERN_C_H__

// ---------------------------------------------------------------------------
//
//  Functions extern "C"
//
// ---------------------------------------------------------------------------


extern "C"
{
  E_DLL0 int E_DLL1 PatternFinder_CtorInternal(void **ptr);
  E_DLL0 int E_DLL1 PatternFinder_DtorInternal(void* impl_);
  E_DLL0 int E_DLL1 PatternFinder_Learn(void* fdPattern, const void* pSrc, const void* pDCare);
  E_DLL0 int E_DLL1 PatternFinder_Find(void *fdPattern, const void * pSrc, void* foundPat);
  E_DLL0 int E_DLL1 PatternFinder_Save(void *fndPattern, const char* name);
  E_DLL0 int E_DLL1 PatternFinder_Load(void *fndPattern, const char* name);
  E_DLL0 int E_DLL1 PatternFinder_Save_wchar(void *fndPattern, const wchar_t* name);
  E_DLL0 int E_DLL1 PatternFinder_Load_wchar(void *fndPattern, const wchar_t* name);
  E_DLL0 int E_DLL1 PatternFinder_GetContrastMode(void* fndPattern, int* contrast);
  E_DLL0 int E_DLL1 PatternFinder_SetContrastMode(void* fndPattern, int contrast);
  E_DLL0 int E_DLL1 PatternFinder_GetInterpolate(void* fndPattern, bool* interpolate);
  E_DLL0 int E_DLL1 PatternFinder_SetInterpolate(void* fndPattern, bool interpolate);
  E_DLL0 int E_DLL1 PatternFinder_GetMaxInstances(void* fndPattern, UINT32* un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_SetMaxInstances(void* fndPattern, UINT32 un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_GetMinScore(void* fndPattern, FLOAT32* f32Score);
  E_DLL0 int E_DLL1 PatternFinder_SetMinScore(void* fndPattern, FLOAT32 f32Score);
  E_DLL0 int E_DLL1 PatternFinder_GetAngleBias(void* fndPattern, FLOAT32* f32AngleBias);
  E_DLL0 int E_DLL1 PatternFinder_SetAngleBias(void* fndPattern, FLOAT32 f32AngleBias);
  E_DLL0 int E_DLL1 PatternFinder_GetAngleTolerance(void* fndPattern, FLOAT32* f32AngleTolerance);
  E_DLL0 int E_DLL1 PatternFinder_SetAngleTolerance(void* fndPattern, FLOAT32 f32AngleTolerance);
  E_DLL0 int E_DLL1 PatternFinder_GetScaleBias(void* fndPattern, FLOAT32* f32ScaleBias);
  E_DLL0 int E_DLL1 PatternFinder_SetScaleBias(void* fndPattern, FLOAT32 f32ScaleBias);
  E_DLL0 int E_DLL1 PatternFinder_GetScaleTolerance(void* fndPattern, FLOAT32* f32ScaleTolerance);
  E_DLL0 int E_DLL1 PatternFinder_SetScaleTolerance(void* fndPattern, FLOAT32 f32ScaleTolerance);
  E_DLL0 int E_DLL1 PatternFinder_GetCoarseStage(void* fndPattern, UINT32* f32CoarseStage);
  E_DLL0 int E_DLL1 PatternFinder_SetCoarseStage(void* fndPattern, UINT32 f32CoarseStage);
  E_DLL0 int E_DLL1 PatternFinder_GetFineStage(void* fndPattern, UINT32* f32FineStage);
  E_DLL0 int E_DLL1 PatternFinder_SetFineStage(void* fndPattern, UINT32 f32FineStage);
  E_DLL0 int E_DLL1 PatternFinder_GetMinFeaturePoints(void* fndPattern, UINT32* f32MinFeaturePoints);
  E_DLL0 int E_DLL1 PatternFinder_SetMinFeaturePoints(void* fndPattern, UINT32 f32MinFeaturePoints);
  E_DLL0 int E_DLL1 PatternFinder_GetMaxFeaturePoints(void* fndPattern, UINT32* f32MaxFeaturePoints);
  E_DLL0 int E_DLL1 PatternFinder_SetMaxFeaturePoints(void* fndPattern, UINT32 f32MaxFeaturePoints);
  E_DLL0 int E_DLL1 PatternFinder_GetFeatureSelection(void* fndPattern, int* eFeatureSelection);
  E_DLL0 int E_DLL1 PatternFinder_SetFeatureSelection(void* fndPattern, int eFeatureSelection);
  E_DLL0 int E_DLL1 PatternFinder_GetLocalSearchMode(void* fndPattern, int* eLocalSearchMode);
  E_DLL0 int E_DLL1 PatternFinder_SetLocalSearchMode(void* fndPattern, int eLocalSearchMode);
  E_DLL0 void E_DLL1 PatternFinder_LearningDone(void* fndPattern, int* res);
#if !defined(EVISION_CLR) && !defined(EVISION_PYTHON)
  E_DLL0 void E_DLL1 FoundPattern_Draw(HDC hDC, const void* featurePoints, const void* rectangleCorners, const void* cent,
    FLOAT32 f32PanX, FLOAT32 f32PanY, FLOAT32 f32ZoomX, FLOAT32 f32ZoomY, int bEdges, void* originRoi,
    void* unifRegion, int patType, FLOAT32 scale, FLOAT32 angle);
  E_DLL0 void E_DLL1 FoundPattern_DrawInstance_DrawAdapter(Euresys::DrawAdapter* drawAdapter, const void* featurePoints, const void* rectangleCorners, const void* cent,
    FLOAT32 f32PanX, FLOAT32 f32PanY, FLOAT32 f32ZoomX, FLOAT32 f32ZoomY, int bEdges, void* originRoi,
    void* unifRegion, int patType, FLOAT32 scale, FLOAT32 angle);
#endif // (not defined EVISION_CLR) && (not defined EVISION_PYTHON)
  E_DLL0 int E_DLL1 PatternFinder_GetAngleSearchExtent(void* fndPattern, INT32* un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_SetAngleSearchExtent(void* fndPattern, INT32 un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_GetScaleSearchExtent(void* fndPattern, INT32* un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_SetScaleSearchExtent(void* fndPattern, INT32 un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_GetXSearchExtent(void* fndPattern, INT32* un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_SetXSearchExtent(void* fndPattern, INT32 un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_GetYSearchExtent(void* fndPattern, INT32* un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_SetYSearchExtent(void* fndPattern, INT32 un32MaxInstances);
  E_DLL0 int E_DLL1 PatternFinder_GetCoarseToFineAnalysisMode(void* fndPattern, int* eMode);
  E_DLL0 int E_DLL1 PatternFinder_SetCoarseToFineAnalysisMode(void* fndPattern, int eMode);
  E_DLL0 int E_DLL1 PatternFinder_GetFindExtension(void* fndPattern, INT32* val);
  E_DLL0 int E_DLL1 PatternFinder_SetFindExtension(void* fndPattern, INT32 val);
  E_DLL0 int E_DLL1 PatternFinder_GetPivot(void* fndPattern, void* val);
  E_DLL0 int E_DLL1 PatternFinder_SetPivot(void* fndPattern, const void* val);
  E_DLL0 int E_DLL1 PatternFinder_Save_Serializer(void *fndPattern, void* ser);
  E_DLL0 int E_DLL1 PatternFinder_Load_Serializer(void *fndPattern, void* ser);
  E_DLL0 int E_DLL1 PatternFinder_GetPatternTypeNewEnum(void* fndPattern, int* patternType);
  E_DLL0 int E_DLL1 PatternFinder_SetPatternTypeNewEnum(void* fndPattern, int patternType);
  E_DLL0 void E_DLL1 FoundPattern_Destructor(void* img);
  E_DLL0 void E_DLL1 FoundPattern_Copy(void* src, void** dst);
};


#endif // __EFIND_EXTERN_C_H__
