// Easy_ESerializer.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_ESERIALIZER_H__
#define __EASY_ESERIALIZER_H__

// Serialization support
// ---------------------------------------------------------------------------

class EOpaqueSerializer;

class E_DLL1 ESerializer
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public :
  enum FileWriterMode
  {
    Create,
    Overwrite,
    Append
  };

  enum ObjectType
  {
    EndOfArchive,
    NotSerializable,
    EMatch = 0x20,
    EImageBW1,
    EImageBW8,
    EImageBW16,
    EImageBW32,
    EImageC15,
    EImageC16,
    EImageC24,
    EImageYUY2,
    EImageC24A,
    EImageSubPixel64,
    EImageComplex64,
    EImageRaw32,
    EImageRaw96,
    EROIBW1,
    EROIBW8,
    EROIBW16,
    EROIBW32,
    EROIC15,
    EROIC16,
    EROIC24,
    EROIYUY2,
    EROIC24A,
    EROISubPixel64,
    EROIComplex64,
    EROIRaw32,
    EROIRaw96,
    EJpegHandler,
    Unknown = 0xffffffff
  };

  enum
  {
    ArchiveFileSig = 0x45
  };

public :
  // allows to retrieve the type of the next object to be read from the archive
  virtual E_DLL0 ObjectType E_DLL1      GetNextObjectType     ( );
  virtual E_DLL0 void E_DLL1            Close                 ( );
  virtual E_DLL0 BOOL E_DLL1            IsFile                ( ) const;
  E_DLL0 BOOL E_DLL1                    IsReading             ( ) const;
  E_DLL0 BOOL E_DLL1                    IsWriting             ( ) const;
  E_DLL0 BOOL E_DLL1                    IsEOS                 ( ) const;
  E_DLL0 void E_DLL1                    PushStreamPos         ( );
  E_DLL0 void E_DLL1                    PopAndForgetStreamPos ( );
  E_DLL0 void E_DLL1                    PopAndApplyStreamPos  ( );
  virtual E_DLL0 UINT32 E_DLL1          GetData               (UINT8* destinationBuffer, UINT32 bufferLength);
  virtual E_DLL0 UINT32 E_DLL1          GetCurrentPos         ( );

public :
  static E_DLL0 ESerializer* E_DLL1     CreateFileWriter      (const std::string& filePath, FileWriterMode mode = Create);
  static E_DLL0 ESerializer* E_DLL1     CreateFileReader      (const std::string& filePath);
  static E_DLL0 ESerializer* E_DLL1     CreateFileWriter      (const std::basic_string<wchar_t>& filePath, FileWriterMode mode = Create);
  static E_DLL0 ESerializer* E_DLL1     CreateFileReader      (const std::basic_string<wchar_t>& filePath);
  static E_DLL0 ESerializer* E_DLL1     CreateMemoryWriter    ( );
  static E_DLL0 ESerializer* E_DLL1     CreateMemoryReader    (UINT8* sourceData, UINT32 length);


  // +--------------------------+
  // | private interface below  |
  // +--------------------------+
public :
  EOpaqueSerializer*                    GetOpaqueSerializer   ( );
  const EOpaqueSerializer*              GetOpaqueSerializer   ( ) const;

protected : 
  ESerializer           ( );  
public :
  virtual E_DLL0 DESTRUCTOR E_DLL1      ~ESerializer          ( );
private :
  ESerializer           ( const ESerializer& other);
  ESerializer&                          operator=             ( const ESerializer& other);

protected :
  EOpaqueSerializer*                    m_OpaqueSerializer;
};

inline EOpaqueSerializer* ESerializer::GetOpaqueSerializer( )
{
  return m_OpaqueSerializer;
}

inline const EOpaqueSerializer* ESerializer::GetOpaqueSerializer( ) const
{
  return m_OpaqueSerializer;
}

#endif //__EASY_ESERIALIZER_H__
