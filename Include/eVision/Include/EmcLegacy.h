////////////////////////////////////////////////////////////////////////////////////////////////////
// EmcLegacy.h: Legacy EasyMultiCam library header file for eVision 6.7.1.0
//
// EasyMultiCam wraps the MultiCam drivers for Eurecards
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EMCLEGACY_H__
#define __EMCLEGACY_H__

#include "Easy.h"
#include "EColor.h"

#if defined E_GCC
  #include "WindowsUnixCompat.h"
  #include "lx_eventtools.h"
#else
  #define MC_MUTICAMFORPICOLO_NOTUSEDUNDERLINUX
#endif

// MultiCam header files

#include "multicam.h"

#if defined MC_MUTICAMFORPICOLO_NOTUSEDUNDERLINUX
  #include "MultiCam32.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// Automatically linking with EEmcMs60
/*
#if !defined MC_DYNAMIC_BINDING && !defined E_STATIC_EG && defined _WINDOWS
#ifdef _DEBUG
#define LIB_COMMENT "EEmcMs60D.lib"
#define LIB__MESSAGE "Automatically linking with EEmcMs60D.dll"
#else
#define LIB_COMMENT "EEmcMs60.lib"
#define LIB__MESSAGE "Automatically linking with EEmcMs60.dll"
#endif
#pragma comment( lib, LIB_COMMENT)
#pragma message( LIB__MESSAGE)
#endif
*/
////////////////////////////////////////////////////////////////////////////////
// Enumeration constants

typedef int EMCSTATUS;

enum EMC_CHANNEL_OPERATION
{
    EMC_CHANNEL_SYNC = 1,
    EMC_CHANNEL_VCAM = 2,
    EMC_CHANNEL_CTL = 3,
    EMC_CHANNEL_SCAN = 4,

    EMC_CHANNEL_UNKNOWN  = 0xFFFFFFFF
};

enum EMC_END_LIVE_MODE
{
    EMC_END_LIVE_NOW = 0,
    EMC_END_LIVE_WHEN_DONE = -1,
    EMC_BLOCKING_END_LIVE_NOW = -2,
    EMC_BLOCKING_END_LIVE_WHEN_DONE = -3,

    EMC_END_LIVE_UNKNOWN  = 0xFFFFFFFF
};

enum EMC_SURFACE_PROTECTION
{
    EMC_SURFACE_PROTECTED,
    EMC_SURFACE_UNPROTECTED
};

#define EMC_LAST_SURFACE_FILLED -1
#define EMC_LOCKED_SURFACE      -1
#define EMC_GRAB_INFINITE       -1

// + OBSOLETE after 6.0
#define EMCOpen                         EmcOpen
#define EMCClose                        EmcClose
#define GetEMCBoardByIndex              EmcGetBoardByIndex
#define GetEMCBoardByPciPosition        EmcGetBoardByPciPosition
#define GetEMCBoardByBoardName          EmcGetBoardByName
#define GetEMCBoardByBoardIdentifier    EmcGetBoardByIdentifier
#define GetAcquisitionPixelSize         EmcGetAcquisitionPixelSize
// - OBSOLETE after 6.0

// + OBSOLETE after 6.0.4
#define GetHdl GetHandle
// - OBSOLETE after 6.0.4

class EPtrList;
class EMCBoard;
class EMCChannel;
class EMCProcessor;
class EMCSurface;
class EMCCluster;
class EMCSource;

class ECodedImage;

E_DLL0 void E_DLL1   EmcOpen( );
E_DLL0 void E_DLL1   EmcClose( );

E_DLL0 void E_DLL1   EmcGetBoardCount( UINT32& un32BoardCount);

E_DLL0 void E_DLL1   EmcGetBoardByIndex( INT32 n32Index, EMCBoard* &pBoard);
E_DLL0 void E_DLL1   EmcGetBoardByPciPosition( INT32 n32PciPosition, EMCBoard* &pBoard);
E_DLL0 void E_DLL1   EmcGetBoardByName( const char* pszBoardName, EMCBoard* &pBoard);
E_DLL0 void E_DLL1   EmcGetBoardByName( const UNICHAR* pszBoardName, EMCBoard* &pBoard);
E_DLL0 void E_DLL1   EmcGetBoardByIdentifier( const char* pszBoardIdentifier, EMCBoard* &pBoard);
E_DLL0 void E_DLL1   EmcGetBoardByIdentifier( const UNICHAR* pszBoardIdentifier, EMCBoard* &pBoard);

struct IEMCParameter
{
    virtual E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, INT32 n32Value)                              = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const char* pszParamName, INT32 n32Value)                       = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, INT32 n32Value)                    = 0;
    virtual E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, const char* pszValue)                        = 0;
    virtual E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, const UNICHAR* pszValue)                     = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const char* pszParamName, const char* pszValue)                 = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, const UNICHAR* pszValue)           = 0;
    virtual E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, FLOAT64 f64Value)                            = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const char* pszParamName, FLOAT64 f64Value)                     = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, FLOAT64 f64Value)                  = 0;
    virtual E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, MCHANDLE ValueInst)                          = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const char* pszParamName, MCHANDLE ValueInst)                   = 0;
    virtual E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, MCHANDLE ValueInst)                = 0;

    virtual E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, PINT32 pn32Value)                            = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const char* ParamName, PINT32 pn32Value)                        = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const UNICHAR* ParamName, PINT32 pn32Value)                     = 0;
    virtual E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, char* pszValue, UINT32 un32MaxLength)        = 0;
    virtual E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, UNICHAR* pszValue, UINT32 un32MaxLength)     = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const char* pszParamName, char* pszValue, UINT32 un32MaxLength) = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const UNICHAR* pszParamName, UNICHAR* pszValue, UINT32 un32MaxLength) = 0;
    virtual E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, PFLOAT64 pf64Value)                          = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const char* pszParamName, PFLOAT64 pf64Value)                   = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const UNICHAR* pszParamName, PFLOAT64 pf64Value)                = 0;
    virtual E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, PMCHANDLE hValueInst)                        = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const char* pszParamName, PMCHANDLE hValueInst)                 = 0;
    virtual E_DLL0 void E_DLL1  GetParam( const UNICHAR* pszParamName, PMCHANDLE hValueInst)              = 0;
};

struct IEMCInitialization
{
    virtual E_DLL0 void E_DLL1  AssignSource( ) = 0;

    virtual E_DLL0 void E_DLL1  AssignSource( const char* pszCAMFile, const char* pszSite, const char* pszProcessType = NULL)          = 0;
    virtual E_DLL0 void E_DLL1  AssignSource( const UNICHAR* pszCAMFile, const UNICHAR* pszSite, const UNICHAR* pszProcessType = NULL) = 0;
    virtual E_DLL0 void E_DLL1  AssignSource( const char* pszCAMFile, const char* pszSite, INT32 n32ProcessType)                      = 0;
    virtual E_DLL0 void E_DLL1  AssignSource( const UNICHAR* pszCAMFile, const UNICHAR* pszSite, INT32 n32ProcessType)                = 0;

    virtual E_DLL0 void E_DLL1  AssignSourceByIndex( const char* pszCAMFile, const char* pszModel, INT32 n32Index = 0)                                      = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByIndex( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32Index = 0)                                = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByIndex( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, INT32 n32Index = 0)          = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByIndex( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, INT32 n32Index = 0) = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByIndex( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, INT32 n32Index)                    = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByIndex( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, INT32 n32Index)              = 0;

    virtual E_DLL0 void E_DLL1  AssignSourceByPciPosition( const char* pszCAMFile, const char* pszModel, INT32 n32PciPosition = 0)                                      = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByPciPosition( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32PciPosition = 0)                                = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByPciPosition( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, INT32 n32PciPosition = 0)          = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByPciPosition( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, INT32 n32PciPosition = 0) = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByPciPosition( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, INT32 n32PciPosition)                    = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByPciPosition( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, INT32 n32PciPosition)              = 0;

    virtual E_DLL0 void E_DLL1  AssignSourceByBoardName( const char* pszCAMFile, const char* pszModel, const char* pszBoardName)                                          = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardName( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszBoardName)                                 = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardName( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, const char* pszBoardName)              = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardName( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, const UNICHAR* pszBoardName)  = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardName( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, const char* pszBoardName)                    = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardName( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, const UNICHAR* pszBoardName)           = 0;

    virtual E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const char* pszCAMFile, const char* pszModel, const char* pszBoardIdentifier)                                         = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszBoardIdentifier)                                = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, const char* pszBoardIdentifier)             = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, const UNICHAR* pszBoardIdentifier) = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, const char* pszBoardIdentifier)                   = 0;
    virtual E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, const UNICHAR* pszBoardIdentifier)          = 0;

    virtual E_DLL0 void E_DLL1  ChangeProcess( const char* pszProcess)    = 0;
    virtual E_DLL0 void E_DLL1  ChangeProcess( const UNICHAR* pszProcess) = 0;
    virtual E_DLL0 void E_DLL1  ChangeProcess( INT32 n32ProcessType)      = 0;
};

struct IEMCAcquisition
{
    virtual E_DLL0 void E_DLL1  Activate( BOOL bActivate = TRUE)           = 0;
    virtual E_DLL0 void E_DLL1  Grab( )                                   = 0;
    virtual E_DLL0 void E_DLL1  Live( INT32 GrabCount = EMC_GRAB_INFINITE) = 0;
    virtual E_DLL0 void E_DLL1  EndLive( INT32 n32When = EMC_END_LIVE_NOW) = 0;
};

typedef struct
{
    INT32 un32NumImages;
    INT32 n32ImageSizeX;
    INT32 n32ImageSizeY;
    INT32 n32SrcImagePixelSize;
    INT32 n32DstImagePixelSize;
    INT32 n32SurfacePitch;
    INT32 n32ImageSize;
    INT32 n32SurfaceFormat;
    INT32 n32PlaneCount;
    INT32 n32Interlaced;
} EMCSurfaceInfo;

class E_DLL1 EMCBase : public IEMCParameter 
{
public:
    E_DLL0 CONSTRUCTOR E_DLL1  EMCBase( MCHANDLE hMCObject = 0);
    virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMCBase( );

    E_DLL0 CONSTRUCTOR E_DLL1  operator MCHANDLE( );
    E_DLL0 MCHANDLE E_DLL1  GetHandle( );

    virtual void Create( const char* pszModel);
    virtual void Create( INT32 n32Model);

    virtual void SetParam( MCPARAMID ParamID, INT32 n32Value);
    virtual void SetParam( const char* pszParamName, INT32 n32Value);
    virtual void SetParam( const UNICHAR* pszParamName, INT32 n32Value);
    virtual void SetParam( MCPARAMID ParamID, const char* pszValue);
    virtual void SetParam( MCPARAMID ParamID, const UNICHAR* pszValue);
    virtual void SetParam( const char* pszParamName, const char* pszValue);
    virtual void SetParam( const UNICHAR* pszParamName, const UNICHAR* pszValue);
    virtual void SetParam( MCPARAMID ParamID, FLOAT64 f64Value);
    virtual void SetParam( const char* pszParamName, FLOAT64 f64Value);
    virtual void SetParam( const UNICHAR* pszParamName, FLOAT64 f64Value);
    virtual void SetParam( MCPARAMID ParamID, MCHANDLE ValueInst);
    virtual void SetParam( const char* pszParamName, MCHANDLE ValueInst);
    virtual void SetParam( const UNICHAR* pszParamName, MCHANDLE ValueInst);

    virtual void GetParam( MCPARAMID ParamID, PINT32 pn32Value);
    virtual void GetParam( const char* ParamName, PINT32 pn32Value);
    virtual void GetParam( const UNICHAR* ParamName, PINT32 pn32Value);
    virtual void GetParam( MCPARAMID ParamID, char* pszValue, UINT32 un32MaxLength);
    virtual void GetParam( MCPARAMID ParamID, UNICHAR* pszValue, UINT32 un32MaxLength);
    virtual void GetParam( const char* pszParamName, char* pszValue, UINT32 un32MaxLength);
    virtual void GetParam( const UNICHAR* pszParamName, UNICHAR* pszValue, UINT32 un32MaxLength);
    virtual void GetParam( MCPARAMID ParamID, PFLOAT64 pf64Value);
    virtual void GetParam( const char* pszParamName, PFLOAT64 pf64Value);
    virtual void GetParam( const UNICHAR* pszParamName, PFLOAT64 pf64Value);
    virtual void GetParam( MCPARAMID ParamID, PMCHANDLE hValueInst);
    virtual void GetParam( const char* pszParamName, PMCHANDLE hValueInst);
    virtual void GetParam( const UNICHAR* pszParamName, PMCHANDLE hValueInst);

protected:
    MCHANDLE m_hMCObject;
};

class E_DLL1 EMCBoard : public EMCBase 
{
public:
    // Construction
    EMCBoard( INT32 n32DriverIndex, INT32 n32BoardHandle = MC_CONFIGURATION);
    virtual ~EMCBoard( );

    EMCSTATUS AddChannel( EMCChannel* pEMCChannel);
    EMCSTATUS RemoveChannel( EMCChannel* pEMCChannel);
    EMCSTATUS RemoveProcessor( EMCProcessor* pEMCProcessor);

    virtual void Create( const char* pszModel)   {}
    virtual void Create( INT32 n32Model)         {}

    virtual INT32 IsIdle( )          = 0;
    virtual void  Idle( )            = 0;
    virtual INT32 LoadParameters( )  = 0;
    virtual INT32 IsUnified( )       = 0;
    virtual INT32 GetBoardAttributes( ) = 0;

    virtual E_DLL0 INT32 E_DLL1   GetDriverIndex( );
    virtual E_DLL0 INT32 E_DLL1   GetPciPosition( );
    virtual E_DLL0 INT32 E_DLL1   GetType( );
    virtual E_DLL0 INT32 E_DLL1   GetTopology( );
    virtual E_DLL0 INT32 E_DLL1   GetSerialNumber( );
    virtual E_DLL0 INT32 E_DLL1   GetFirmwareRevision( );
    virtual E_DLL0 INT32 E_DLL1   GetSourceCount( );

    virtual const E_DLL0 char* E_DLL1  GetName( );
    virtual const E_DLL0 UNICHAR* E_DLL1  GetNameUnicode( );
    virtual const E_DLL0 char* E_DLL1  GetIdentifier( );
    virtual const E_DLL0 UNICHAR* E_DLL1  GetIdentifierUnicode( );
    virtual const E_DLL0 char* E_DLL1  GetModuleType( );
    virtual const E_DLL0 UNICHAR* E_DLL1  GetModuleTypeUnicode( );

    virtual E_DLL0 void E_DLL1    NameBoard( const char* pszNameBoard);
    virtual E_DLL0 void E_DLL1    NameBoard( const UNICHAR* pszNameBoard);

protected:
    char      m_cName[64];
    char      m_cIdentifier[64];
    char      m_cModuleType[64];

    UNICHAR   m_wcName[64];
    UNICHAR   m_wcIdentifier[64];
    UNICHAR   m_wcModuleType[64];

    INT32     m_n32DriverIndex;
    INT32     m_n32PciPosition;
    INT32     m_n32Type;
    INT32     m_n32Topology;
    INT32     m_n32SerialNumber;
    INT32     m_n32FirmwareRevision;
    INT32     m_n32SourceCount;

    EPtrList* m_pListChannel;
    EPtrList* m_pListProcessor;
    friend class EMCConfiguration;
};

class E_DLL1 ECluster 
{
public:
    E_DLL0 CONSTRUCTOR E_DLL1                ECluster( );
    virtual E_DLL0 DESTRUCTOR E_DLL1        ~ECluster( );

    virtual EMCBase*            GetSignalingObject( )                   = 0;
    virtual EMCSource*          GetSource( )                            = 0;

    E_DLL0 INT32 E_DLL1         GetImageIndex( );

    virtual void                LockSurface( EMCSurface *pEMCSurface)   = 0;
    virtual void                UnLockSurface( EMCSurface *pEMCSurface) = 0;

    E_DLL0 UINT32 E_DLL1         GetNumImages( );
    E_DLL0 void E_DLL1           SetNumImages( UINT32 un32NumImages);

    E_DLL0 void* E_DLL1         GetBuffer( INT32 n32Index = EMC_LAST_SURFACE_FILLED);
    E_DLL0 EMCSurface* E_DLL1    GetSurface( INT32 n32Index = EMC_LAST_SURFACE_FILLED);
    E_DLL0 void* E_DLL1          GetImage( INT32 n32Index = EMC_LAST_SURFACE_FILLED);

    EMCSurface*                 UpdateMCSurface( MCHANDLE hSurface);

    E_DLL0 BOOL E_DLL1           LockSurface( INT32 n32Index = EMC_LAST_SURFACE_FILLED);
    E_DLL0 BOOL E_DLL1           UnLockSurface( INT32 n32Index = EMC_LOCKED_SURFACE);

    E_DLL0 void E_DLL1           DisplayImageProtected( BOOL bProtected);

    void                                 SetSurfaceProtection( EMC_SURFACE_PROTECTION SurfaceProtection);
    E_DLL0 EMC_SURFACE_PROTECTION E_DLL1  GetSurfaceProtection( );

    EMCChannel*                 GetChannel( );
    EMCProcessor*               GetProcessor( );
    E_DLL0 EMCBoard* E_DLL1     GetBoard( );

    INT32                       GetBoardType( );

protected:
    EMCSurfaceInfo              m_SurfaceInfo;

    EMCChannel*                 m_pEMCChannel;
    EMCProcessor*               m_pEMCProcessor;
    EPtrList*                   m_pListSurface;

    EMCSurface**                m_ppEMCSurface;
    EMCSurface*                 m_pEMCSurfaceLocked;
    void*                       m_pImageLocked;

    EMC_SURFACE_PROTECTION      m_SurfaceProtection;
    BOOL                        m_bDisplayImageProtected;

    BOOL                        m_bMultiInterlaced;
    BOOL                        m_bClusterActivated, m_bSignalActivated;
};

class E_DLL1 EMCSurfaceMgr : virtual public ECluster 
{
public:
    // Construction
    E_DLL0 CONSTRUCTOR E_DLL1  EMCSurfaceMgr( UINT32 un32NumImages);
    virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMCSurfaceMgr( );

    E_DLL0 INT32 E_DLL1  GetBytesPerPixel( );

    E_DLL0 INT32 E_DLL1  GetImageSizeX( );
    E_DLL0 INT32 E_DLL1  GetImageSizeY( );
    E_DLL0 INT32 E_DLL1  GetImageSize( );

protected:
    virtual void LoadPixelSize( INT32& n32PixelSize) = 0;
    virtual void UpdateEImageSizes( )                = 0;
    virtual EMCSTATUS AllocateImages( )              = 0;
    virtual EMCSTATUS FreeImages( )                  = 0;

    EMCSTATUS ManageSurfaceAllocation( );
    EMCSTATUS CreateEMCSurfaces( BOOL bIsUnified);
    EMCSTATUS AllocateSurfaces( );
    EMCSTATUS FreeSurfaces( BOOL bIsUnified);
    EMCSTATUS InitializeSurfaces( BOOL bIsUnified);
    EMCSTATUS ActivateEMCCluster( );
};

#define EMC_MAX_EVENTS	8

class E_DLL1 EMCSignal : virtual public ECluster 
{
public:
    E_DLL0 CONSTRUCTOR E_DLL1  EMCSignal( EMC_SURFACE_PROTECTION SurfaceProtection);
    virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMCSignal( );

public:
    //MultiCam CallBack ( des)activation
    E_DLL0 void E_DLL1  UseAcquisitionCallBack( BOOL bEnable = TRUE);
    E_DLL0 void E_DLL1  UseTimingCallBack( BOOL bEnable = TRUE);
    E_DLL0 void E_DLL1  UseExceptionCallBack( BOOL bEnable = TRUE);
    E_DLL0 void E_DLL1  UseErrorCallBack( BOOL bEnable = TRUE);
    E_DLL0 void E_DLL1  GetUsedCallBacks( UINT32& un32CallBackMask);

    E_DLL0 INT32 E_DLL1  GetTimeCode();
    E_DLL0 void E_DLL1  SetTimeCode(INT32 n32TimeCode);

protected:
    // CallBacks
    static void( EMCSignal::*SignalList[EMC_MAX_EVENTS])( PMCCALLBACKINFO cbInfo);
    static void E_STDCALL MultiCamCallBack( PMCCALLBACKINFO cbInfo);
    static void E_STDCALL MultiCamCallBackThreadStart( PVOID Context);
    static void E_STDCALL MultiCamCallBackThreadEnd( PVOID Context);

    BOOL m_bUseAcquisitionCallBack;
    UINT32 m_un32SignalTimeout;
    UINT32 m_un32SignalFlags;

    INT32 m_n32TimeCode;

    HANDLE m_hEvLastAcquisition;
    HANDLE m_hEvError;
    

public:
    void MCPSignalCallBack( EMCSurface* pEMCSurface, BOOL bLast);
#if defined MC_MUTICAMFORPICOLO_NOTUSEDUNDERLINUX
    void MCPErrorCallBack( PECEVENTINFO pInfo);
#endif

protected:
    void SurfaceProcessing( PMCCALLBACKINFO cbInfo);
    void SurfaceFilled( PMCCALLBACKINFO cbInfo);
    void UnrecoverableOverRun( PMCCALLBACKINFO cbInfo);
    void FrameTriggerViolation( PMCCALLBACKINFO cbInfo);
    void StartExposure( PMCCALLBACKINFO cbInfo);
    void EndExposure( PMCCALLBACKINFO cbInfo);
    void AcquisitionFailure( PMCCALLBACKINFO cbInfo);
    void ClusterUnavalable( PMCCALLBACKINFO cbInfo);
    void SetSignal( UINT32 mc_signal_type, BOOL bEnable);
    void ActivateMCSignal( BOOL bActivate);
    void ActivateMCPSignal( BOOL bActivate);
    void RegisterCallBack( BOOL bCallBack);

    // Pure virtual function implemented in EMCImage<pixel>
    // in order to change the EImage<pixel> pointer
    virtual EMCSTATUS OnMCSurface( EMCSurface* pEMCSurface)  = 0;

    // Pure virtual functions having to be implemented in the client class
    // in order to intercept the MultiCam CallBacks
    virtual void OnMCAcquisition( INT32 n32Signal)           = 0;
    virtual void OnMCTiming( INT32 n32Signal)                = 0;
    virtual void OnMCException( INT32 n32Signal)             = 0;
    virtual void OnMCError( INT32 n32Signal)                 = 0;
    virtual void OnMCThreadStart( )                          = 0;
    virtual void OnMCThreadEnd( )                            = 0;
};

class E_DLL1 EMCCluster : 
public IEMCInitialization,
public IEMCParameter,
public IEMCAcquisition,
public EMCSurfaceMgr,
public EMCSignal
{
public:
    // Construction
    E_DLL0 CONSTRUCTOR E_DLL1  EMCCluster( );
    E_DLL0 CONSTRUCTOR E_DLL1  EMCCluster( UINT32 un32NumImages, EMC_SURFACE_PROTECTION SurfaceProtection = EMC_SURFACE_PROTECTED);
    virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMCCluster( );

    E_DLL0 CONSTRUCTOR E_DLL1  operator MCHANDLE( );
    E_DLL0 MCHANDLE E_DLL1  GetHandle( );

public:
    // IEMCParameter overload
    E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, INT32 n32Value);
    E_DLL0 void E_DLL1  SetParam( const char* pszParamName, INT32 n32Value);
    E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, INT32 n32Value);
    E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, const char* pszValue);
    E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, const UNICHAR* pszValue);
    E_DLL0 void E_DLL1  SetParam( const char* pszParamName, const char* pszValue);
    E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, const UNICHAR* pszValue);
    E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, FLOAT64 f64Value);
    E_DLL0 void E_DLL1  SetParam( const char* pszParamName, FLOAT64 f64Value);
    E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, FLOAT64 f64Value);
    E_DLL0 void E_DLL1  SetParam( MCPARAMID ParamID, MCHANDLE ValueInst);
    E_DLL0 void E_DLL1  SetParam( const char* pszParamName, MCHANDLE ValueInst);
    E_DLL0 void E_DLL1  SetParam( const UNICHAR* pszParamName, MCHANDLE ValueInst);

    E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, PINT32 pn32Value);
    E_DLL0 void E_DLL1  GetParam( const char* ParamName, PINT32 pn32Value);
    E_DLL0 void E_DLL1  GetParam( const UNICHAR* ParamName, PINT32 pn32Value);
    E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, char* pszValue, UINT32 un32MaxLength);
    E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, UNICHAR* pszValue, UINT32 un32MaxLength);
    E_DLL0 void E_DLL1  GetParam( const char* pszParamName, char* pszValue, UINT32 un32MaxLength);
    E_DLL0 void E_DLL1  GetParam( const UNICHAR* pszParamName, UNICHAR* pszValue, UINT32 un32MaxLength);
    E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, PFLOAT64 pf64Value);
    E_DLL0 void E_DLL1  GetParam( const char* pszParamName, PFLOAT64 pf64Value);
    E_DLL0 void E_DLL1  GetParam( const UNICHAR* pszParamName, PFLOAT64 pf64Value);
    E_DLL0 void E_DLL1  GetParam( MCPARAMID ParamID, PMCHANDLE hValueInst);
    E_DLL0 void E_DLL1  GetParam( const char* pszParamName, PMCHANDLE hValueInst);
    E_DLL0 void E_DLL1  GetParam( const UNICHAR* pszParamName, PMCHANDLE hValueInst);

public:
    // IEMCInitialization
    E_DLL0 void E_DLL1  AssignSource( );

    E_DLL0 void E_DLL1  AssignSource( const char* pszCAMFile, const char* pszSite, const char* pszProcessType = NULL);
    E_DLL0 void E_DLL1  AssignSource( const UNICHAR* pszCAMFile, const UNICHAR* pszSite, const UNICHAR* pszProcessType = NULL);
    E_DLL0 void E_DLL1  AssignSource( const char* pszCAMFile, const char* pszSite, INT32 n32ProcessType);
    E_DLL0 void E_DLL1  AssignSource( const UNICHAR* pszCAMFile, const UNICHAR* pszSite, INT32 n32ProcessType);

    E_DLL0 void E_DLL1  AssignSourceByIndex( const char* pszCAMFile, const char* pszModel, INT32 n32Index = 0);
    E_DLL0 void E_DLL1  AssignSourceByIndex( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32Index = 0);
    E_DLL0 void E_DLL1  AssignSourceByIndex( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, INT32 n32Index = 0);
    E_DLL0 void E_DLL1  AssignSourceByIndex( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, INT32 n32Index = 0);
    E_DLL0 void E_DLL1  AssignSourceByIndex( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, INT32 n32Index);
    E_DLL0 void E_DLL1  AssignSourceByIndex( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, INT32 n32Index);

    E_DLL0 void E_DLL1  AssignSourceByPciPosition( const char* pszCAMFile, const char* pszModel, INT32 n32PciPosition = 0);
    E_DLL0 void E_DLL1  AssignSourceByPciPosition( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32PciPosition = 0);
    E_DLL0 void E_DLL1  AssignSourceByPciPosition( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, INT32 n32PciPosition = 0);
    E_DLL0 void E_DLL1  AssignSourceByPciPosition( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, INT32 n32PciPosition = 0);
    E_DLL0 void E_DLL1  AssignSourceByPciPosition( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, INT32 n32PciPosition);
    E_DLL0 void E_DLL1  AssignSourceByPciPosition( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, INT32 n32PciPosition);

    E_DLL0 void E_DLL1  AssignSourceByBoardName( const char* pszCAMFile, const char* pszModel, const char* pszBoardName);
    E_DLL0 void E_DLL1  AssignSourceByBoardName( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszBoardName);
    E_DLL0 void E_DLL1  AssignSourceByBoardName( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, const char* pszBoardName);
    E_DLL0 void E_DLL1  AssignSourceByBoardName( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, const UNICHAR* pszBoardName);
    E_DLL0 void E_DLL1  AssignSourceByBoardName( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, const char* pszBoardName);
    E_DLL0 void E_DLL1  AssignSourceByBoardName( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, const UNICHAR* pszBoardName);

    E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const char* pszCAMFile, const char* pszModel, const char* pszBoardIdentifier);
    E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszBoardIdentifier);
    E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const char* pszCAMFile, const char* pszModel, const char* pszProcessType, const char* pszBoardIdentifier);
    E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, const UNICHAR* pszProcessType, const UNICHAR* pszBoardIdentifier);
    E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const char* pszCAMFile, const char* pszModel, INT32 n32ProcessType, const char* pszBoardIdentifier);
    E_DLL0 void E_DLL1  AssignSourceByBoardIdentifier( const UNICHAR* pszCAMFile, const UNICHAR* pszModel, INT32 n32ProcessType, const UNICHAR* pszBoardIdentifier);

    E_DLL0 void E_DLL1  ChangeProcess( const char* pszProcess);
    E_DLL0 void E_DLL1  ChangeProcess( const UNICHAR* pszProcess);
    E_DLL0 void E_DLL1  ChangeProcess( INT32 n32ProcessType);

public:
    // IEMCAcquisition
    E_DLL0 void E_DLL1  Activate( BOOL bActivate = TRUE);
    E_DLL0 void E_DLL1  Grab( );
    E_DLL0 void E_DLL1  Live( INT32 GrabCount = EMC_GRAB_INFINITE);
    E_DLL0 void E_DLL1  EndLive( INT32 n32When = EMC_END_LIVE_NOW);
    E_DLL0 void E_DLL1  SetTriggerMode( INT32 n32TrigMode, INT32 n32NextTrigMode);
    E_DLL0 void E_DLL1  SetTriggerMode( INT32 n32PageTrigMode);
    E_DLL0 void E_DLL1  SetLineRateMode( INT32 n32LineRateMode);

public:
    // Protected member access
    E_DLL0 void E_DLL1  SetNumImages( UINT32 un32NumImages, EMC_SURFACE_PROTECTION SurfaceProtection);

    // Protected member access
    const E_DLL0 char* E_DLL1  GetSite( );
    const E_DLL0 char* E_DLL1  GetModel( );
    const E_DLL0 char* E_DLL1  GetCamFile( );
    E_DLL0 INT32 E_DLL1  GetProcessType( );

    E_DLL0 INT32 E_DLL1  GetOperation( );
    E_DLL0 INT32 E_DLL1  GetChannelState( );

    E_DLL0 BOOL E_DLL1   IsAssigned( );

    virtual E_DLL0 EMCSTATUS E_DLL1  LoadImageSizes( );

    virtual E_DLL0 EGenericROI* E_DLL1  GetGenericROI( );
#ifdef E_STATIC_EG
    virtual E_DLL0 ECodedImage* E_DLL1  GetECodedImage( );

    virtual E_DLL0 EMCSTATUS E_DLL1  SaveImage( );
    virtual E_DLL0 EMCSTATUS E_DLL1  CopyToClipBoard( );
    virtual E_DLL0 EMCSTATUS E_DLL1  CopyBmpInBuffers( INT32 n32BmpRcID);
    virtual E_DLL0 EMCSTATUS E_DLL1  FillBitmapInfo( BITMAPINFO* pBitmapInfo);
#endif

protected:
    // Protected functions
    void AssignSourceEx( const char* pszCAMFile, const char* pszModel,
        INT32 n32ProcessType, EMCBoard* pBoard);
    void AssignChannel( const char* pszCAMFile, const char* pszModel, EMCBoard* pEMCBoard);
    void AssignProcessor( INT32 n32ProcessType);
    void AssignCluster( UINT32 un32NumImages);

    E_DLL0 EMCBase* E_DLL1           GetSignalingObject( );
    E_DLL0 EMCSource* E_DLL1         GetSource( );

    E_DLL0 void E_DLL1  LockSurface( EMCSurface *pEMCSurface);
    E_DLL0 void E_DLL1  UnLockSurface( EMCSurface *pEMCSurface);

protected:
    char  m_pszSite[MAX_PATH];
    char  m_pszModel[MAX_PATH];
    char  m_pszCAMFile[MAX_PATH];
    INT32 m_n32ProcessType; 
    
    INT32 m_AssignState;

    BOOL  m_bAssigning;
};

template<class Pixel> class E_DLL1 EMCImage: public EImage<Pixel>, public EMCCluster 
{
public:
    E_DLL0 CONSTRUCTOR E_DLL1  EMCImage( );
    E_DLL0 CONSTRUCTOR E_DLL1  EMCImage( UINT32 un32NumImages, EMC_SURFACE_PROTECTION SurfaceProtection = EMC_SURFACE_PROTECTED);
    virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMCImage( );

    // Disallowed EImage function members
    E_DLL0 void E_DLL1  SetOrgX( INT32 n32OrgX);
    E_DLL0 void E_DLL1  SetOrgY( INT32 n32OrgY);
    E_DLL0 void E_DLL1  SetWidth( INT32 n32Width);
    E_DLL0 void E_DLL1  SetHeight( INT32 n32Height);
    E_DLL0 void E_DLL1  SetSize( INT32 n32Width, INT32 n32Height);
    E_DLL0 void E_DLL1  SetSize( EGenericROI* pImage);
    E_DLL0 void E_DLL1  SetImagePtr( void* pImagePtr, INT32 n32BitsPerRow = 0);
    E_DLL0 void E_DLL1  SetImagePtr( INT32 n32Width, INT32 n32Height, void* pImagePtr, INT32 n32BitsPerRow = 0);

    E_DLL0 INT32 E_DLL1  GetWidth( ) { return m_SurfaceInfo.n32ImageSizeX; };
    E_DLL0 INT32 E_DLL1  GetHeight( ) { return m_SurfaceInfo.n32ImageSizeY; };

    // Documented virtual functions
    virtual E_DLL0 void E_DLL1   OnMCAcquisition( INT32 n32Signal)  {}
    virtual E_DLL0 void E_DLL1   OnMCTiming( INT32 n32Signal)       {}
    virtual E_DLL0 void E_DLL1   OnMCException( INT32 n32Signal)    {}
    virtual E_DLL0 void E_DLL1   OnMCError( INT32 n32Signal)        {}
    virtual E_DLL0 void E_DLL1   OnMCThreadStart( )                 {}
    virtual E_DLL0 void E_DLL1   OnMCThreadEnd( )                   {}

    E_DLL0 EImage<Pixel>& E_DLL1  operator []( INT32 n32ImageIndex);
    E_DLL0 EImage<Pixel>* E_DLL1  GetImage( INT32 n32ImageIndex = EMC_LAST_SURFACE_FILLED);

    // Drawing function
    E_DLL0 void E_DLL1  Draw( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f);

protected:
	// Undocumented functions
	void ActivateUniformizationMc(EColor Light, EColorVector *pLightSrc, EColor Dark, EColorVector *pDarkSrc, INT32 Index);
	void ActivateContrastBrightnessAdjustmentMc(EColor f32Contrast, EColor f32Brightness, EColor f32Visibility, UINT32 bmNegative, INT32 Index);
	void ActivateLutMc(EC24Vector *pLut, INT32 Index);

protected:
    // Undocumented virtual functions
    virtual E_DLL0 void E_DLL1  LoadPixelSize( INT32& n32PixelSize);
    virtual E_DLL0 void E_DLL1  UpdateEImageSizes( );
    virtual E_DLL0 INT32 E_DLL1  AllocateImages( );
    virtual E_DLL0 INT32 E_DLL1  FreeImages( );

    E_DLL0 EMCSTATUS E_DLL1      OnMCSurface( EMCSurface* pEMCSurface);
    E_DLL0 EGenericROI* E_DLL1   GetGenericROI( );
};

// Predefined image types
typedef EMCImage<EBW8>  EMCImageBW8;
typedef EMCImage<EBW16> EMCImageBW16;
typedef EMCImage<EC16>  EMCImageC16;
typedef EMCImage<EC24A> EMCImageC24A;

class EMCImageC24 : public EMCImage<EC24>
{
public:
  E_DLL0 CONSTRUCTOR E_DLL1  EMCImageC24( UINT32 un32NumImages, EMC_SURFACE_PROTECTION SurfaceProtection = EMC_SURFACE_PROTECTED);
  E_DLL0 CONSTRUCTOR E_DLL1  EMCImageC24( );
	E_DLL0 void E_DLL1	ActivateUniformization(EColor Light = EColor(1,1,1), EColorVector *pLightSrc = NULL, EColor Dark = EColor(0,0,0), EColorVector *pDarkSrc = NULL);
	E_DLL0 void E_DLL1	ActivateUniformization(INT32 Index);

	E_DLL0 void E_DLL1	ActivateContrastBrightnessAdjustment(FLOAT32 f32Contrast = 1, FLOAT32 f32Brightness = 0, FLOAT32 f32Visibility = 0, BOOL bNegative = FALSE);
	E_DLL0 void E_DLL1	ActivateContrastBrightnessAdjustment(FLOAT32 f32Contrast0, FLOAT32 f32Brightness0, FLOAT32 f32Visibility0, BOOL bNegative0,
															 FLOAT32 f32Contrast1, FLOAT32 f32Brightness1, FLOAT32 f32Visibility1, BOOL bNegative1,
															 FLOAT32 f32Contrast2, FLOAT32 f32Brightness2, FLOAT32 f32Visibility2, BOOL bNegative2);
	E_DLL0 void E_DLL1	ActivateContrastBrightnessAdjustment(INT32 Index);

	E_DLL0 void E_DLL1	ActivateLut(EC24Vector *pLut);
	E_DLL0 void E_DLL1	ActivateLut(INT32 Index);
};

class E_DLL1 EMCJpegHandler: public EJpegHandler, public EMCCluster 
{
public:
    E_DLL0 CONSTRUCTOR E_DLL1           EMCJpegHandler( );
    E_DLL0 CONSTRUCTOR E_DLL1           EMCJpegHandler( UINT32 un32NumImages, EMC_SURFACE_PROTECTION SurfaceProtection = EMC_SURFACE_PROTECTED);
    virtual E_DLL0 DESTRUCTOR E_DLL1   ~EMCJpegHandler( );

    // Documented virtual functions
    virtual E_DLL0 void E_DLL1          OnMCAcquisition( INT32 n32Signal)  {}
    virtual E_DLL0 void E_DLL1          OnMCTiming( INT32 n32Signal)       {}
    virtual E_DLL0 void E_DLL1          OnMCException( INT32 n32Signal)    {}
    virtual E_DLL0 void E_DLL1          OnMCError( INT32 n32Signal)        {}
    virtual E_DLL0 void E_DLL1          OnMCThreadStart( )                 {}
    virtual E_DLL0 void E_DLL1          OnMCThreadEnd( )                   {}
    
    virtual void                        LoadPixelSize( INT32& n32PixelSize);
    virtual void                        UpdateEImageSizes( );

protected:
    // Undocumented virtual functions
    virtual E_DLL0 INT32 E_DLL1         AllocateImages( );
    virtual E_DLL0 INT32 E_DLL1         FreeImages( );

    E_DLL0 EMCSTATUS E_DLL1             OnMCSurface( EMCSurface* pEMCSurface);
};

#ifdef E_STATIC_EG

#include "EObject.h"

class E_DLL1 EMCCodedImage:  public ECodedImage, public EMCCluster 
{
public:
    E_DLL0 CONSTRUCTOR E_DLL1  EMCCodedImage( );
    E_DLL0 CONSTRUCTOR E_DLL1  EMCCodedImage( UINT32 un32NumImages, EMC_SURFACE_PROTECTION SurfaceProtection = EMC_SURFACE_PROTECTED);
    virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMCCodedImage( );

protected:
    FLOAT32 m_f32CompressionRatio;

protected:
    E_DLL0 INT32 E_DLL1  OnMCSurface( UINT32 hSurface);
    void DecodeRLC( PUINT16 Source);
    E_DLL0 ECodedImage* E_DLL1  GetECodedImage( );

public:
    //Documented virtual functions
    virtual E_DLL0 void E_DLL1  OnMCAcquisition( INT32 n32Signal) {}
    virtual E_DLL0 void E_DLL1  OnMCTiming( INT32 n32Signal)      {}
    virtual E_DLL0 void E_DLL1  OnMCException( INT32 n32Signal)   {}
    virtual E_DLL0 void E_DLL1  OnMCError( INT32 n32Signal)       {}
    virtual E_DLL0 void E_DLL1  OnMCThreadStart( )                {}
    virtual E_DLL0 void E_DLL1  OnMCThreadEnd( )                  {}

    E_DLL0 ECodedImage& E_DLL1  operator []( INT32 n32ImageIndex);
    E_DLL0 FLOAT32 E_DLL1  GetCompressionRatio( );

protected:
    // Undocumented virtual functions
    virtual E_DLL0 void E_DLL1  LoadPixelSize( INT32& n32PixelSize);
    virtual E_DLL0 void E_DLL1  UpdateEImageSizes( );
    virtual E_DLL0 INT32 E_DLL1  AllocateImages( );
    virtual E_DLL0 INT32 E_DLL1  FreeImages( );

    E_DLL0 EMCSTATUS E_DLL1      OnMCSurface( EMCSurface* pEMCSurface);
};
#endif //E_STATIC_EG

#endif //__EMCLEGACY_H__


