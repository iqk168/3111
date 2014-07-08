// Easy_EVectorTemplate.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EVECTORTEMPLATE_H__
#define __EASY_EVECTORTEMPLATE_H__

////////////////////////////////////////////////////////////////////////////////
// Template vector class
template<class Type> class
#ifdef E_BCB6
E_DLL1
#endif
EVectorTemplate
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  static  Type              m_PlaceHolder;

  // Constructor/destructor
  // ---------------------------------------------------------------------------
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EVectorTemplate   ( );
  E_DLL0 CONSTRUCTOR E_DLL1             EVectorTemplate   ( UINT32 un32NumElements);
  E_DLL0 CONSTRUCTOR E_DLL1             EVectorTemplate   ( const EVectorTemplate<Type>& Vec);

  virtual  E_DLL0 DESTRUCTOR E_DLL1     ~EVectorTemplate  ( );

  // Assignment
  // ---------------------------------------------------------------------------
public:
  E_DLL0 EVectorTemplate<Type>& E_DLL1 operator=         ( const EVectorTemplate<Type>& Vec);

  // Copy
  // ---------------------------------------------------------------------------
private :
  void                                 InitEmpty         ( );

public:
  E_DLL0 EVectorTemplate<Type>* E_DLL1 CopyTo            ( EVectorTemplate<Type>* pVec = NULL) const;

protected :
  EVectorTemplate<Type>*               InternalCopyTo    ( EVectorTemplate<Type>* pVec, BOOL bIsACtor) const;

public :
  // Debug stream
  // ---------------------------------------------------------------------------
  //  virtual  void                       DumpToStream      ( std::ostream& strm , int indent = 0 ) const;

  // Size information
  // ---------------------------------------------------------------------------
public:
  E_DLL0 UINT32 E_DLL1                 GetNumElements    ( ) const { return m_un32NumElements; }

  // Data access
  // ---------------------------------------------------------------------------
public:
  E_DLL0 void E_DLL1                    Empty             ( );
  E_DLL0 void E_DLL1                    AddElement        ( Type Element);
  E_DLL0 void E_DLL1                    RemoveElement     ( UINT32 un32Index);
  E_DLL0 Type& E_DLL1                   operator[]        ( UINT32 un32Index) const;
  E_DLL0 Type E_DLL1                    GetElement        ( INT32 index);
  E_DLL0 void E_DLL1                    SetElement        ( INT32 index, Type val );

  // File storage
  // ---------------------------------------------------------------------------
protected:
  static UINT8              m_un8Signature;
  static UINT8              m_un8Version;

public:
  E_DLL0 void E_DLL1                   Save              ( const char* pszPathName);
  E_DLL0 void E_DLL1                   Save              ( const UNICHAR* pszPathName);

  E_DLL0 void E_DLL1                   Load              ( const char* pszPathName);
  E_DLL0 void E_DLL1                   Load              ( const UNICHAR* pszPathName);

  virtual E_DLL0 void E_DLL1           Serialize         ( FILE*  pFile, BOOL bOutput, UINT32 un32Version);

  // Reserved
  // ---------------------------------------------------------------------------
protected:
  // Data members
  UINT32                                m_un32NumElements;
  UINT32                                m_un32MaxElements;
  Type*                                 m_pArray;

public:
  E_DLL0 UINT32 E_DLL1                  GetMaxElements    ( ) const { return m_un32MaxElements; }
  E_DLL0 void E_DLL1                    SetMaxElements    ( UINT32 un32MaxElements, BOOL bKeepElements = TRUE);
  E_DLL0 void E_DLL1                    SetNumElements    ( UINT32 un32NumElements);
  E_DLL0 Type* E_DLL1                   GetDataPtr        ( ) const { return m_pArray; }
  E_DLL0 void E_DLL1                    AddElementByRef   ( Type& Element);

  E_DLL0 void E_DLL1                    Sift              ( const Type& Element, INT32 (*pfLessThan)( const Type& Element1, const Type& Element2));
};


#endif //__EASY_EVECTORTEMPLATE_H__
