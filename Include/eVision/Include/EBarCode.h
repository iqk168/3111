////////////////////////////////////////////////////////////////////////////////////////////////////
// EBarCode.h: EasyBarCode library header file for eVision 6.7.1.0
//
// EasyBarCode implements a bar code reader
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EBARCODE_H__
#define __EBARCODE_H__

// eVision header files
#include "EGauge.h"
#include "EBarCode_Enum.h"




const FLOAT32 BRC_DEFAULT_CUT_ANGLE = FLOAT32_MAX;

class EBarCode: public ERectangleShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Default constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1           EBarCode            ( );
  E_DLL0 DESTRUCTOR E_DLL1            ~EBarCode           ( );
                                
  // Updates                    
  E_DLL0 void E_DLL1                  Set                 ( ERectangle Rectangle);
                                
  // Direction                  
  E_DLL0 UINT32 E_DLL1                GetDirections       ( ) { return m_un32Directions; }
  E_DLL0 void E_DLL1                  SetDirections       ( UINT32 un32Directions) { m_un32Directions = un32Directions; }
                                
  E_DLL0 BOOL E_DLL1                  GetDirectReading    ( ) { return m_bDirectReading; }
  E_DLL0 void E_DLL1                  SetDirectReading    ( BOOL bDirectReading) { m_bDirectReading = bDirectReading; }
                                
  // Reading parameters         
  E_DLL0 void E_DLL1                  SetReadingCenter    ( FLOAT32 f32RelativeX, FLOAT32 f32RelativeY);
  E_DLL0 void E_DLL1                  SetReadingSize      ( FLOAT32 f32RelativeSizeX, FLOAT32 f32RelativeSizeY);
  E_DLL0 FLOAT32 E_DLL1               GetReadingAngle     ( ) { return m_f32ReadingAngle; }
  E_DLL0 void E_DLL1                  SetReadingAngle     ( FLOAT32 f32ReadingAngle) { m_f32ReadingAngle = f32ReadingAngle; }
                                
  E_DLL0 FLOAT32 E_DLL1               GetRelativeReadingX ( ) { return m_f32RelativeReadingX; }
                                
  E_DLL0 FLOAT32 E_DLL1               GetRelativeReadingY ( ) { return m_f32RelativeReadingY; }
                                
  E_DLL0 FLOAT32 E_DLL1               GetRelativeReadingSizeX( ) { return m_f32RelativeReadingSizeX; }
                                
  E_DLL0 FLOAT32 E_DLL1               GetRelativeReadingSizeY( ) { return m_f32RelativeReadingSizeY; }
                                
  E_DLL0 FLOAT32 E_DLL1               GetModule           ( ) { return m_f32Module; }
  E_DLL0 void E_DLL1                  SetModule           ( FLOAT32 f32Module) { m_f32Module = f32Module; }
                                
  E_DLL0 FLOAT32 E_DLL1               GetThicknessRatio   ( ) { return m_f32ThicknessRatio; }
  E_DLL0 void E_DLL1                  SetThicknessRatio   ( FLOAT32 f32ThicknessRatio) { m_f32ThicknessRatio = f32ThicknessRatio; }
                                
  E_DLL0 UINT32 E_DLL1                GetThreshold        ( ) { return m_un32Threshold; }
  E_DLL0 void E_DLL1                  SetThreshold        ( UINT32 un32Threshold) { m_un32Threshold = un32Threshold; }
                                
  // Reading modes              
  E_DLL0 BOOL E_DLL1                  GetKnownLocation    ( ) { return m_bKnownLocation; }
  E_DLL0 void E_DLL1                  SetKnownLocation    ( BOOL bKnownLocation) { m_bKnownLocation = bKnownLocation; }
                                
  E_DLL0 BOOL E_DLL1                  GetKnownModule      ( ) { return m_bKnownModule; }
  E_DLL0 void E_DLL1                  SetKnownModule      ( BOOL bKnownModule) { m_bKnownModule = bKnownModule; }
                                
  E_DLL0 BOOL E_DLL1                  GetVerifyChecksum   ( ) { return m_bVerifyChecksum; }
  E_DLL0 void E_DLL1                  SetVerifyChecksum   ( BOOL bVerifyChecksum) { m_bVerifyChecksum = bVerifyChecksum; }
                                
  // Reading                    
  E_DLL0 void E_DLL1                  Detect              ( EROIBW8* pSrc);
  E_DLL0 void E_DLL1                  Decode              ( enum BRC_SYMBOLOGIES eSymbology, char* pszString, UINT32 un32Length);
  E_DLL0 void E_DLL1                  Decode              ( enum BRC_SYMBOLOGIES eSymbology, UNICHAR* puszString, UINT32 un32Length);
  E_DLL0 void E_DLL1                  Read                ( EROIBW8* pSrc, char* pszString, UINT32 un32Length);
  E_DLL0 void E_DLL1                  Read                ( EROIBW8* pSrc, UNICHAR* puszString, UINT32 un32Length);
  E_DLL0 void E_DLL1                  GetDecodedDirection ( enum BRC_SYMBOLOGIES eSymbology, BOOL &bDirectEncoding);
  E_DLL0 void E_DLL1                  GetDecodedDirection ( BOOL &bDirectEncoding);
  E_DLL0 void E_DLL1                  GetDecodedModule    ( enum BRC_SYMBOLOGIES eSymbology, FLOAT32 &f32Module);
  E_DLL0 void E_DLL1                  GetDecodedModule    ( FLOAT32 &f32Module);
  E_DLL0 void E_DLL1                  GetDecodedThicknessRatio( enum BRC_SYMBOLOGIES eSymbology, FLOAT32 &f32ThicknessRatio);
  E_DLL0 void E_DLL1                  GetDecodedThicknessRatio( FLOAT32 &f32ThicknessRatio);
  E_DLL0 void E_DLL1                  GetDecodedAngle     ( enum BRC_SYMBOLOGIES eSymbology, FLOAT32 &f32DecodedAngle, FLOAT32 f32CutAngle = BRC_DEFAULT_CUT_ANGLE);
  E_DLL0 void E_DLL1                  GetDecodedAngle     ( FLOAT32 &f32DecodedAngle, FLOAT32 f32CutAngle = BRC_DEFAULT_CUT_ANGLE);
  E_DLL0 void E_DLL1                  GetDecodedRectangle ( enum BRC_SYMBOLOGIES eSymbology, ERectangle &rect);
  E_DLL0 void E_DLL1                  GetDecodedRectangle ( ERectangle &rect);

  
  // Reading results            
  E_DLL0 UINT32 E_DLL1                GetNumEnabledSymbologies( );
  E_DLL0 UINT32 E_DLL1                GetNumDecodedSymbologies( ) { return m_un32NumDecodedSymbologies; }

  E_DLL0 enum BRC_SYMBOLOGIES E_DLL1  GetDecodedSymbology ( UINT32 un32Index);
  
  // Symbologies
  E_DLL0 UINT32 E_DLL1                GetStandardSymbologies( ) { return m_un32StandardSymbologies; }
  E_DLL0 void E_DLL1                  SetStandardSymbologies( UINT32 un32StandardSymbologies);
                                
  E_DLL0 UINT32 E_DLL1                GetAdditionalSymbologies( ) { return m_un32AdditionalSymbologies; }
  E_DLL0 void E_DLL1                  SetAdditionalSymbologies( UINT32 un32AdditionalSymbologies);
                                
  // Drawing                    
  E_DLL0 void E_DLL1                  Draw                ( HDC hDC, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                  Draw                ( Euresys::DrawAdapter* drawAdapter, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = FALSE);
                                
  // Dragging                   
  E_DLL0 BOOL E_DLL1                  HitTest             ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                  Drag                ( INT32 n32CursorX, INT32 n32CursorY);
                                
  // Geometry                   
  E_DLL0 EFrame* E_DLL1               CastToFrame         ( ) { return this; }
  
  // Reading area
  EImageBW8                           m_Registered;
  ETransition                         m_Transition;

  // Helpers
  const E_DLL0 char* E_DLL1           GetSymbologyName    ( enum BRC_SYMBOLOGIES eSymbology);

protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1                GetSignature        ( );
  virtual E_DLL0 void E_DLL1          Serialize         ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bRecurse = TRUE);
  virtual E_DLL0 void E_DLL1          Serialize           ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

  UINT32                              m_un32Directions; 
  FLOAT32                             m_f32ReadingAngle; 
  FLOAT32                             m_f32RelativeReadingX; 
  FLOAT32                             m_f32RelativeReadingY; 
  FLOAT32                             m_f32RelativeReadingSizeX; 
  FLOAT32                             m_f32RelativeReadingSizeY; 
  FLOAT32                             m_f32Module; 
  FLOAT32                             m_f32ThicknessRatio; 
  UINT32                              m_un32Threshold; 
  BOOL                                m_bKnownLocation; 
  BOOL                                m_bKnownModule; 
  BOOL                                m_bVerifyChecksum; 
  UINT32                              m_un32NumDecodedSymbologies; 
  UINT32                              m_un32StandardSymbologies; 
  UINT32                              m_un32AdditionalSymbologies;
                                      
  BOOL                                m_bDirectReading;
                                      
private:                              
  // Reading area                     
  ERectangleShape                     m_ReadingArea;

  // Private EWorldShape
  EWorldShape                         m_InternalWorldShape;
                                      
  // Symbologies                      
  enum BRC_SYMBOLOGIES                m_eDecodedSymbology;
                                      
  // Helpers                          
  UINT32                              GetSymbologyIndex   ( enum BRC_SYMBOLOGIES eSymbology);
};

#endif //__EBARCODE_H__
