// Easy_EPlot.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EPLOT_H__
#define __EASY_EPLOT_H__


class EPlot
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;
  EPlot() 
  { 
    handle_ = 0;
    callback_ = 0;
  }

public:
  // Plot window
  FLOAT64                               m_f64XMin;
  FLOAT64                               m_f64XMax;
  FLOAT64                               m_f64YMin;
  FLOAT64                               m_f64YMax;

  // Plot viewport                      
  INT32                                 m_n32XMin;
  INT32                                 m_n32XMax;
  INT32                                 m_n32YMin;
  INT32                                 m_n32YMax;

  // Automatic Y extent adjustment      
  BOOL                                  m_bAutoYRange;
  void                                  SetYRange         ( INT32 n32YMin, UINT32 un32YMax);
  E_DLL0 void E_DLL1                    SetAutoYRange     ( );

public:                           
  E_DLL0 void E_DLL1                    DrawAnnotations   ( HDC hDC, INT32 n32Width, INT32 n32Height,
    INT32 n32OrgX, INT32 n32OrgY,
    char* pszXLabel, char* pszYLabel);
  E_DLL0 void E_DLL1                    DrawAnnotations   ( Euresys::DrawAdapter* drawAdapter, INT32 n32Width, INT32 n32Height,
    INT32 n32OrgX, INT32 n32OrgY,
    char* pszXLabel, char* pszYLabel);
  E_DLL0 INT32 E_DLL1                   XView             ( FLOAT64 f64X);
  E_DLL0 INT32 E_DLL1                   YView             ( FLOAT64 f64Y); 
};


#endif //__EASY_EPLOT_H__
