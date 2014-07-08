// Easy_EMeasurementUnit.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EMEASUREMENTUNIT_H__
#define __EASY_EMEASUREMENTUNIT_H__

///////////////////////////////////////////////////////////////////////////////
// class EMeasurementUnit

class EMeasurementUnit
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public :
  // Constructor. Ex.( 1000., "Km") -> 1000.( m) "Km"
  E_DLL0 CONSTRUCTOR E_DLL1             EMeasurementUnit  ( );
  E_DLL0 CONSTRUCTOR E_DLL1             EMeasurementUnit  ( EMeasurementUnit *pUnit);
  E_DLL0 CONSTRUCTOR E_DLL1             EMeasurementUnit  ( FLOAT32 f32Magnitude, const char* pszName);
  E_DLL0 CONSTRUCTOR E_DLL1             EMeasurementUnit  ( FLOAT32 f32Magnitude, const UNICHAR* pszName);

  // Returns the unit name. Ex:( ) -> returns "Km"
  const E_DLL0 char* E_DLL1             GetName           ( );
  const E_DLL0 UNICHAR* E_DLL1          GetNameUnicode    ( );
  const E_DLL0 char* E_DLL1             GetName           ( ) const;
  const E_DLL0 UNICHAR* E_DLL1          GetNameUnicode    ( ) const;
  E_DLL0 void E_DLL1                    SetName           ( const char* pszName);
  E_DLL0 void E_DLL1                    SetNameUnicode    ( const UNICHAR* pszName);

  // Get or set the unit magnitude. Ex:( ) -> returns 1000.( m)
  E_DLL0 FLOAT32 E_DLL1                 GetMagnitude      ( ) const { return m_f32Magnitude; }
  E_DLL0 void E_DLL1                    SetMagnitude      ( FLOAT32 f32Magnitude) { m_f32Magnitude = f32Magnitude; }

  // Returns a conversion factor to another unit. Ex:( &Dm) -> returns 100.
  E_DLL0 FLOAT32 E_DLL1                 ConversionFactorTo( const EMeasurementUnit& Unit) const;

  static E_DLL0 EMeasurementUnit* E_DLL1 GetPredefinedUnit( const char* pszUnitName);
  const E_DLL0 BOOL E_DLL1              IsPredefinedUnit  ( ) const;

protected:                        
  FLOAT32                               m_f32Magnitude; 

private :                               
  char                                  m_pszName[16];

  static E_DLL0 EMeasurementUnit*       E_DLL1  EPredefinedUnits[];
};




///////////////////////////////////////////////////////////////////////////////
// Global variables

extern E_DLL0 EMeasurementUnit E_DLL1  EUnitNone;

// Metric units 
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_um;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_mm;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_cm;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_dm;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_m;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_dam;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_hm;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_km;

// Imperial/US units
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_mil; 
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_inch;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_foot;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_yard;
extern E_DLL0 EMeasurementUnit E_DLL1  EUnit_mile;

#endif //__EASY_EMEASUREMENTUNIT_H__
