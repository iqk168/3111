#ifndef __EOCR_EXTERNC_INTERFACE_H__
#define __EOCR_EXTERNC_INTERFACE_H__

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
  E_DLL0 int E_DLL1 Ocr_Ctor(void** impl, int handle);
  E_DLL0 int E_DLL1 Ocr_getCharSpacing_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setCharSpacing_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getMaxCharHeight_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setMaxCharHeight_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getMaxCharWidth_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setMaxCharWidth_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getMinCharHeight_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setMinCharHeight_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getMinCharWidth_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setMinCharWidth_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getRemoveNarrowOrFlat_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setRemoveNarrowOrFlat_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getNoiseArea_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setNoiseArea_INT32(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getCompareAspectRatio_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setCompareAspectRatio_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getSegmentationMode_EasyOcrSegmentationMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setSegmentationMode_EasyOcrSegmentationMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getCutLargeChars_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setCutLargeChars_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getRelativeSpacing_FLOAT32(void* impl, float* retVal);
  E_DLL0 int E_DLL1 Ocr_setRelativeSpacing_FLOAT32(void* impl, float retVal);
  E_DLL0 int E_DLL1 Ocr_getRemoveBorder_BOOL(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setRemoveBorder_BOOL(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getTextColor_EasyOcrColor(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setTextColor_EasyOcrColor(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getThreshold_ThresholdMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setThreshold_ThresholdMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getMatchingMode_EasyOcrMatchingMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setMatchingMode_EasyOcrMatchingMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_getShiftXTolerance_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocr_setShiftXTolerance_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Ocr_getShiftYTolerance_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocr_setShiftYTolerance_UINT32(void* impl, unsigned int retVal);
  E_DLL0 int E_DLL1 Ocr_getShiftingMode_EasyOcrShiftingMode(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_setShiftingMode_EasyOcrShiftingMode(void* impl, int retVal);
  E_DLL0 int E_DLL1 Ocr_EmptyChars(void* impl);
  E_DLL0 int E_DLL1 Ocr_AddChar_INT32_INT32_INT32_INT32(void* impl, int orgX, int orgY, int endX, int endY);
  E_DLL0 int E_DLL1 Ocr_BuildObjects_ROIBW8_INT16(void* impl, void** sourceImage, short* retVal);
  E_DLL0 int E_DLL1 Ocr_FindAllChars_ROIBW8_INT16(void* impl, void** sourceImage, short* retVal);
  E_DLL0 int E_DLL1 Ocr_MatchChar_ROIBW8_UINT32_INT32_INT32_INT32_INT16(void* impl, void** sourceImage, unsigned int classes, int* index, int shiftX, int shiftY, short* retVal);
  E_DLL0 int E_DLL1 Ocr_ReadText_ROIBW8_INT32_UINT32_String_BOOL_INT16(void* impl, void** sourceImage, int maximumNumberOfCharacters, unsigned int classes, char** string, int autoSegmentation, short* retVal);
  E_DLL0 int E_DLL1 Ocr_ReadText_ROIBW8_INT32_UINT32_String_INT16(void* impl, void** sourceImage, int maximumNumberOfCharacters, unsigned int classes, char** string, short* retVal);
  E_DLL0 int E_DLL1 Ocr_Recognize_ROIBW8_INT32_UINT32_String(void* impl, void** sourceImage, int maximumNumberOfCharacters, unsigned int classes, char** string);
  E_DLL0 int E_DLL1 Ocr_Recognize_ROIBW8_INT32_Vector_String(void* impl, void** sourceImage, int maximumNumberOfCharacters, void* classes, char** string);
  E_DLL0 int E_DLL1 Ocr_getNumChars_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetOrgX_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetOrgY_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetDstX_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetDstY_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetWidth_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetHeight_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetTotalOrgX_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetTotalOrgY_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetTotalDstX_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_CharGetTotalDstY_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_GetFirstCharCode_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_GetFirstCharDistance_INT32_FLOAT32(void* impl, int index, float* retVal);
  E_DLL0 int E_DLL1 Ocr_GetSecondCharCode_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_GetSecondCharDistance_INT32_FLOAT32(void* impl, int index, float* retVal);
  E_DLL0 int E_DLL1 Ocr_GetConfidenceRatio_INT32_FLOAT32(void* impl, int index, float* retVal);
  E_DLL0 int E_DLL1 Ocr_AddPatternFromImage_ROIBW8_INT32_INT32_INT32_INT32_INT32_UINT32(void* impl, void** sourceImage, int orgX, int orgY, int width, int height, int code, unsigned int classes);
  E_DLL0 int E_DLL1 Ocr_AddPatternFromImage_ROIBW8_INT32_INT32_INT32_INT32_INT32(void* impl, void** sourceImage, int orgX, int orgY, int width, int height, int code);
  E_DLL0 int E_DLL1 Ocr_HitChar_INT32_INT32_UINT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int charIndex, float zoomX, float zoomY, float panX, float panY, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChar_INT32_INT32_UINT32_FLOAT32_FLOAT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int charIndex, float zoomX, float zoomY, float panX, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChar_INT32_INT32_UINT32_FLOAT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int charIndex, float zoomX, float zoomY, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChar_INT32_INT32_UINT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int charIndex, float zoomX, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChar_INT32_INT32_UINT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int charIndex, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChars_INT32_INT32_UINT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int* charIndex, float zoomX, float zoomY, float panX, float panY, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChars_INT32_INT32_UINT32_FLOAT32_FLOAT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int* charIndex, float zoomX, float zoomY, float panX, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChars_INT32_INT32_UINT32_FLOAT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int* charIndex, float zoomX, float zoomY, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChars_INT32_INT32_UINT32_FLOAT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int* charIndex, float zoomX, int* retVal);
  E_DLL0 int E_DLL1 Ocr_HitChars_INT32_INT32_UINT32_BOOL(void* impl, int cursorX, int cursorY, unsigned int* charIndex, int* retVal);
  E_DLL0 int E_DLL1 Ocr_LearnPattern_ROIBW8_UINT32_INT32_UINT32_BOOL(void* impl, void** sourceImage, unsigned int charIndex, int code, unsigned int classes, int autoSegmentation);
  E_DLL0 int E_DLL1 Ocr_LearnPattern_ROIBW8_UINT32_INT32_UINT32(void* impl, void** sourceImage, unsigned int charIndex, int code, unsigned int classes);
  E_DLL0 int E_DLL1 Ocr_LearnPattern_ROIBW8_UINT32_INT32(void* impl, void** sourceImage, unsigned int charIndex, int code);
  E_DLL0 int E_DLL1 Ocr_LearnPatterns_ROIBW8_ConstString_UINT32_BOOL(void* impl, void** sourceImage, const char* string, unsigned int* classes, int autoSegmentation);
  E_DLL0 int E_DLL1 Ocr_LearnPatterns_ROIBW8_ConstString_UINT32(void* impl, void** sourceImage, const char* string, unsigned int* classes);
  E_DLL0 int E_DLL1 Ocr_RemovePattern_UINT32(void* impl, unsigned int index);
  E_DLL0 int E_DLL1 Ocr_getNumPatterns_INT32(void* impl, int* retVal);
  E_DLL0 int E_DLL1 Ocr_GetPatternCode_INT32_INT32(void* impl, int index, int* retVal);
  E_DLL0 int E_DLL1 Ocr_GetPatternClass_INT32_UINT32(void* impl, int index, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocr_GetPatternBitmap_INT32_BW8(void* impl, int index, void** retVal);
  E_DLL0 int E_DLL1 Ocr_Load_ConstString_INT16(void* impl, const char* pathName, short* retVal);
  E_DLL0 int E_DLL1 Ocr_NewFont_UINT32_UINT32_INT16(void* impl, unsigned int patternWidth, unsigned int patternHeight, short* retVal);
  E_DLL0 int E_DLL1 Ocr_NewFont_UINT32_INT16(void* impl, unsigned int patternWidth, short* retVal);
  E_DLL0 int E_DLL1 Ocr_NewFont_INT16(void* impl, short* retVal);
  E_DLL0 int E_DLL1 Ocr_getPatternWidth_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocr_getPatternHeight_UINT32(void* impl, unsigned int* retVal);
  E_DLL0 int E_DLL1 Ocr_Save_ConstString_INT16(void* impl, const char* pathName, short* retVal);
  E_DLL0 int E_DLL1 Ocr_Dump(void* impl);
  E_DLL0 int E_DLL1 Ocr_DrawChar_DrawAdapter_UINT32_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, unsigned int charIndex, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Ocr_DrawChar_DrawAdapter_UINT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, unsigned int charIndex, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Ocr_DrawChar_DrawAdapter_UINT32_FLOAT32_FLOAT32(void* impl, void* context, unsigned int charIndex, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocr_DrawChar_DrawAdapter_UINT32_FLOAT32(void* impl, void* context, unsigned int charIndex, float zoomX);
  E_DLL0 int E_DLL1 Ocr_DrawChar_DrawAdapter_UINT32(void* impl, void* context, unsigned int charIndex);
  E_DLL0 int E_DLL1 Ocr_DrawChars_DrawAdapter_FLOAT32_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY, float panX, float panY);
  E_DLL0 int E_DLL1 Ocr_DrawChars_DrawAdapter_FLOAT32_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY, float panX);
  E_DLL0 int E_DLL1 Ocr_DrawChars_DrawAdapter_FLOAT32_FLOAT32(void* impl, void* context, float zoomX, float zoomY);
  E_DLL0 int E_DLL1 Ocr_DrawChars_DrawAdapter_FLOAT32(void* impl, void* context, float zoomX);
  E_DLL0 int E_DLL1 Ocr_DrawChars_DrawAdapter(void* impl, void* context);
  E_DLL0 int E_DLL1 Ocr_getTrueThreshold_UINT32(void* impl, unsigned int* retVal);
#ifdef EVISION_CLR
  E_DLL0 void E_DLL1  Ocr_SetCallback(void** impl, [System::Runtime::InteropServices::MarshalAs(System::Runtime::InteropServices::UnmanagedType::FunctionPtr)]System::Delegate* callback, int handle);
#else
E_DLL0 void E_DLL1  Ocr_SetCallback(void** impl, void* callback, int handle);
#endif //EVISION_CLR
    E_DLL0 void E_DLL1 Ocr_GetWrapper(int* handle, void* impl);
  E_DLL0 int E_DLL1 Ocr_Dtor(void* impl);
}

#endif // E_EXTERN_C_BUILD
#endif // __EOCR_EXTERNC_INTERFACE_H__
