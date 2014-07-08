// Easy_EJpegHandler.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EJPEGHANDLER_H__
#define __EASY_EJPEGHANDLER_H__

class EJpegHandler_OpDat;

class E_DLL1 EJpegHandler 
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  enum ScalingMode
  {
    Full = E_EJPEGHANDLER_FULL,
    Half = E_EJPEGHANDLER_HALF,
    Quarter = E_EJPEGHANDLER_QUARTER,
    Eighth = E_EJPEGHANDLER_EIGHTH
  };
    
public :
  E_DLL0 CONSTRUCTOR E_DLL1           EJpegHandler            ( );
  virtual E_DLL0 CONSTRUCTOR E_DLL1  ~EJpegHandler            ( );
  E_DLL0 void E_DLL1                  SetBuffers              ( UINT8* upField, const UINT32 upFieldByteSize, UINT8* downField, const UINT32 downFieldByteSize );
  E_DLL0 void E_DLL1                  UpdateSizeAndTimestamp  ( UINT32 upFieldByteSize, UINT32 downFieldByteSize, UINT32 timeStamp0, UINT32 timeStamp1);
  E_DLL0 void E_DLL1                  DecompressToImage       ( EImageC24&, const ScalingMode& mode = Full ) const;
  E_DLL0 void E_DLL1                  Load                    ( const char* );
  E_DLL0 void E_DLL1                  Load                    ( const UNICHAR* pszPathName);
  E_DLL0 void E_DLL1                  Load                    ( const std::string& );
  E_DLL0 void E_DLL1                  Load                    ( const std::basic_string<wchar_t>& );
  E_DLL0 void E_DLL1                  LoadFJfif               ( const char* );
  E_DLL0 void E_DLL1                  LoadFJfif               ( const std::string& );
  E_DLL0 void E_DLL1                  LoadSJfif               ( const char* );
  E_DLL0 void E_DLL1                  LoadSJfif               ( const std::string& );
  E_DLL0 void E_DLL1                  SaveFJfif               ( const char* );
  E_DLL0 void E_DLL1                  SaveFJfif               ( const std::string& );
  E_DLL0 void E_DLL1                  SaveSJfif               ( const char* );
  E_DLL0 void E_DLL1                  SaveSJfif               ( const std::string& );
  E_DLL0 void E_DLL1                  Load                    ( FILE* );
  E_DLL0 void E_DLL1                  Load                    ( ESerializer* );
  E_DLL0 void E_DLL1                  Save                    ( const char* ) const;
  E_DLL0 void E_DLL1                  Save                    ( const UNICHAR* ) const;
  E_DLL0 void E_DLL1                  Save                    ( const std::string& ) const;
  E_DLL0 void E_DLL1                  Save                    ( const std::basic_string<wchar_t>& ) const;
  E_DLL0 void E_DLL1                  Save                    ( FILE* ) const;
  E_DLL0 void E_DLL1                  Save                    ( ESerializer* ) const;
  static E_DLL0 void E_DLL1           CreateJpegFromRGB24     ( UINT8*& resultBuffer, UINT32& resultBufferSize, const UINT8* srcImg, const UINT32 linePitch, const UINT32 width, const UINT32 height, const UINT32 quality);
private :
  explicit                            EJpegHandler            ( const EJpegHandler& );
  EJpegHandler&                       operator=               ( const EJpegHandler& );
public :
  EJpegHandler_OpDat*  _opdat;
};

#endif //__EASY_EJPEGHANDLER_H__
