// EOCR_Enum.h: EasyOCR library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCR_ENUM_H__
#define __EOCR_ENUM_H__


///////////////////////////////////////////////////////////////////////////////
// Character classes
enum OCRClasses
{ 
  OCR_CLASS_0 = 0x1,
  OCR_CLASS_1 = 0x2,
  OCR_CLASS_2 = 0x4,
  OCR_CLASS_3 = 0x8,
  OCR_CLASS_4 = 0x10,
  OCR_CLASS_5 = 0x20,
  OCR_CLASS_6 = 0x40,
  OCR_CLASS_7 = 0x80,
  OCR_CLASS_8 = 0x100,
  OCR_CLASS_9 = 0x200,
  OCR_CLASS_10 = 0x400,
  OCR_CLASS_11 = 0x800,
  OCR_CLASS_12 = 0x1000,
  OCR_CLASS_13 = 0x2000,
  OCR_CLASS_14 = 0x4000,
  OCR_CLASS_15 = 0x8000,
  OCR_CLASS_16 = 0x10000,
  OCR_CLASS_17 = 0x20000,
  OCR_CLASS_18 = 0x40000,
  OCR_CLASS_19 = 0x80000,
  OCR_CLASS_20 = 0x100000,
  OCR_CLASS_21 = 0x200000,
  OCR_CLASS_22 = 0x400000,
  OCR_CLASS_23 = 0x800000,
  OCR_CLASS_24 = 0x1000000,
  OCR_CLASS_25 = 0x2000000,
  OCR_CLASS_26 = 0x4000000,
  OCR_CLASS_27 = 0x8000000,
  OCR_CLASS_28 = 0x10000000,
  OCR_CLASS_29 = 0x20000000,
  OCR_CLASS_30 = 0x40000000,
  OCR_CLASS_31 = 0x80000000,

  OCR_DIGIT = OCR_CLASS_0,
  OCR_UPPERCASE = OCR_CLASS_1,
  OCR_LOWERCASE = OCR_CLASS_2,
  OCR_SPECIAL = OCR_CLASS_3,
  OCR_EXTENDED = OCR_CLASS_4,

  OCR_ALL_CLASSES  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Text color
enum OCRColor
{ 
  OCR_BLACK_ON_WHITE,
  OCR_WHITE_ON_BLACK,
  OCR_DARK_ON_LIGHT,
  OCR_LIGHT_ON_DARK,
  OCR_CONTRAST_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Segmentation mode
enum OCRSegmentationMode
{ 
  OCR_KEEP_OBJECTS,
  OCR_REPASTE_OBJECTS,
  OCR_SEGMENTATION_OBJECTS_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Matching modes
enum OCR_MATCHING_MODES
{
  OCR_MATCH_RMS,
  OCR_MATCH_STANDARD,
  OCR_MATCH_NORMALIZED,

  OCR_MATCH_UNDEFINED  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
// Shifting modes
enum OCR_SHIFTING_MODES
{
  OCR_SHIFT_CHARS,
  OCR_SHIFT_TEXT,

  OCR_SHIFT_UNDEFINED  = 0xFFFFFFFF
};



#endif //__EOCR_ENUM_H__
  
