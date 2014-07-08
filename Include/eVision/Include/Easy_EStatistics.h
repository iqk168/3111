// Easy_EStatistics.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_ESTATISTICS_H__
#define __EASY_ESTATISTICS_H__

///////////////////////////////////////////////////////////////////////////////
// class EStatistics

class EStatistics
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1             EStatistics       ( UINT32 un32MaxElements = 0);
  E_DLL0 DESTRUCTOR E_DLL1              ~EStatistics      ( );

  // Values
  E_DLL0 void E_DLL1                    Reset             ( UINT32 un32MaxElements);
  E_DLL0 void E_DLL1                    NewElement        ( FLOAT32 f32Value);

  // Simple statistics
  E_DLL0 UINT32 E_DLL1                  Count             ( ) { return m_un32NumElements; }
  E_DLL0 FLOAT32 E_DLL1                 Average           ( );
  E_DLL0 FLOAT32 E_DLL1                 Deviation         ( );
  E_DLL0 FLOAT32 E_DLL1                 Minimum           ( );
  E_DLL0 FLOAT32 E_DLL1                 Maximum           ( );

private:
  // Data storage
  UINT32                                m_un32MaxElements;
  UINT32                                m_un32NumElements;
  UINT32                                m_un32NewElement;
  FLOAT32                               *m_pArray;
};


#endif //__EASY_ESTATISTICS_H__
