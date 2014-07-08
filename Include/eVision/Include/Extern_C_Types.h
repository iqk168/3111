#ifndef __EASY_EXTERN_C_TYPES_H__
#define __EASY_EXTERN_C_TYPES_H__


#ifdef E_GCC
  #define __int8  char
  #define __int16 short int
  #define __int32 int
#endif

extern "C"
{

typedef struct
{
  unsigned __int32 m_un32Start;
  unsigned __int32 m_un32Length;
  __int32 m_n32Amplitude;
  __int32 m_n32Area;
  float m_f32Center;
} CPeak;

typedef struct
{
  __int16 m_n16X;
  __int16 m_n16Y;
  unsigned __int8 m_bw8Pixel;
} CBW8Path;

typedef struct
{
  __int16 m_n16X;
  __int16 m_n16Y;
  unsigned __int16 m_bw16Pixel;
} CBW16Path;

typedef struct
{
  __int16 m_n16X;
  __int16 m_n16Y;
  unsigned __int8 m_c24Pixel_c0;
  unsigned __int8 m_c24Pixel_c1;
  unsigned __int8 m_c24Pixel_c2;
} CC24Path;

typedef struct
{
  __int32 red;
  __int32 green;
  __int32 blue;
} CRGBColor;

typedef struct
{
  float c0;
  float c1;
  float c2;
} CFloatTriplet;

typedef struct
{
  float centerX;
  float centerY;
} CCPoint;

typedef struct
{
  CCPoint point;
  float angle;
  float scale;
} CFrame;

typedef struct
{
  CFrame frame;
  float halfLength;
} CLine;

typedef struct
{
  CFrame frame;
  float sizeX;
  float sizeY;
} CRectangle;

typedef struct
{
  CFrame frame;
  float innerRadius;
  float outerRadius;
  float amplitude;
} CWedge;

typedef struct
{
  CFrame frame;
  float radius;
  float amplitude;
} CCircle;

typedef struct
{
  float centerX;
  float centerY;
  float angle;
  float scale;
  float score;
  int interpolated;
} CMatchPosition;

typedef struct
{
  CCPoint Center;;
  float Angle;
  float Scale;
  float Score;
  float* FeaturePointsDataX;
  float* FeaturePointsDataY;
  float* RectangleCornersDataX;
  float* RectangleCornersDataY;
  int numFeaturePoints;
  int numRectangleCorners;
} CFoundPattern;

typedef struct
{
  int numFoundPattern;
  CFoundPattern* foundPattern;
} CArrayOfFoundPattern;

}
#endif //__EASY_EXTERN_C_TYPES_H__
