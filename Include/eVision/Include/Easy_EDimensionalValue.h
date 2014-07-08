// Easy_EDimensionalValue.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EDIMENSIONALVALUE_H__
#define __EASY_EDIMENSIONALVALUE_H__

///////////////////////////////////////////////////////////////////////////////
// class EDimensionalValue

class EDimensionalValue
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public :
  // Default constructor ( 1 NoUnit)
  E_DLL0 CONSTRUCTOR E_DLL1               EDimensionalValue ( );

  // Constructor; sets the value and unit. Ex:( 3., &Km) -> 3. Km
  E_DLL0 CONSTRUCTOR E_DLL1               EDimensionalValue ( FLOAT32 f32Value, EMeasurementUnit* pUnit);

  // Destructor
  virtual E_DLL0 DESTRUCTOR E_DLL1        ~EDimensionalValue( );

  E_DLL0 EDimensionalValue& E_DLL1        operator=         ( const EDimensionalValue& other);

  // Get or set value, regardless the unit
  E_DLL0 FLOAT32 E_DLL1                   GetValue          ( ) const { return m_f32Value; }
  E_DLL0 void E_DLL1                      SetValue          ( FLOAT32 f32Value) { m_f32Value = f32Value; }

  // Sets the value and unit. Ex:( 3., &Km) -> 3. Km
  E_DLL0 void E_DLL1                      SetValue          ( FLOAT32 f32Value, EMeasurementUnit* pUnit);

  // Returns the value converted to another unit. Ex:( &M) -> 5. Km, return 5000.
  E_DLL0 FLOAT32 E_DLL1                   GetValue          ( EMeasurementUnit* pUnit);

  // Returns the current unit. Ex:( ) -> 5. Km, return &Km
  E_DLL0 EMeasurementUnit* E_DLL1         GetUnit           ( );
  E_DLL0 const EMeasurementUnit* E_DLL1   GetUnit           ( ) const;

  // Sets a new unit and converts the value. Ex:( &M) -> 5000. M
  E_DLL0 void E_DLL1                      SetUnit           ( EMeasurementUnit* pUnit);

  virtual E_DLL0 void E_DLL1              Serialize         ( ESerializer*  serializer, UINT32 un32Version = 0xFFFFFFFF);
  E_DLL0 UINT32 E_DLL1                    GetVersion        ( ) const;

protected:
  FLOAT32                                 m_f32Value; 

private :
  EMeasurementUnit                        m_Unit;

  static const UINT32                     m_un32FileVersion;
};

#endif //__EASY_EDIMENSIONALVALUE_H__
