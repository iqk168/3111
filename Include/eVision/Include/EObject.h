////////////////////////////////////////////////////////////////////////////////////////////////////
// EObject.h: EasyObject library header file for eVision 6.7.1.0
//
// EasyObject performs connected components labeling for feature extraction
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOBJECT_H__
#define __EOBJECT_H__

// eVision header files
#include "EImage.h"

#if (_MSC_VER >= 1300)
#pragma warning( push )
#pragma warning( disable : 4702 ) 
#endif // (_MSC_VER >= 1300)

#include <vector>

#if (_MSC_VER >= 1300)
#pragma warning( pop )
#endif // (_MSC_VER >= 1300)

#include "EObject_Enum.h"



////////////////////////////////////////////////////////////////////////////////
// Structures

struct EListItem
{
  struct EListItem* pPrev;
  INT8* pn8Data;
  struct EListItem* pNext;
};

struct EBlocStruct
{
  struct EListItem * pFirstBlocItem;
  struct EBlocStruct* pNext;
};

typedef struct EBlocStruct Bloc_Struct;

struct EDataStruct
{
  INT8* pn8Data;
  struct EDataStruct* pNext;
};

typedef struct EDataStruct Data_Struct;

////////////////////////////////////////////////////////////////////////////////
// + OBSOLETE
#define GetNbSelectedObjects GetNumSelectedObjects
#define GetNbObjs GetNumObjects
#define GetNbRuns GetNumRuns
#define GetNbFeats GetNumFeatures
#define GetObjNbRun GetNumObjectRuns
#define GetObjData GetObjectData
#define RemoveAllObjs RemoveAllObjects
#define SelectObjectUsingPosition SelectObjectsUsingPosition
// - OBSOLETE

////////////////////////////////////////////////////////////////////////////////
// Classes
class EItemList 
{
private : 
  // Blocs management
  inline void NewBlock();
  inline INT8* GetSlot();

  INT32 m_n32ItemDataSize;

  INT32 m_n32SlotSize;
  INT32 m_n32BlockSize;
  INT32 m_n32CurrentBlock;

  std::vector<INT8*> m_Blocks;

  INT8* m_pFirstFree;
  INT8* m_pBlockEnd;

  // Item List
  EListItem* m_pBegin;
  EListItem* m_pEnd;

  // Current item cursor
  EListItem* m_pCursor;

  // List Size
  INT32 m_n32NumItems;

public :
  // Constructors  
  EItemList( );
  ~EItemList( );

  INT16 Init(INT32 n32ItemDataSize, INT32 n32SlotsPerBlock);
  INT16 Init(INT32 n32DataSize);

  INT16 AddItem( INT8* pn8DataPtr);

  INT16 InsertItem( INT8* pn8DataPtr, INT32 n32Position);
  INT16 ModifyItem( INT8* pn8DataPtr, INT32 n32Position);
  INT16 RemoveItem( INT32 n32Position);
  INT16 RemoveAll( );
  INT16 MoveItems( INT32 n32SrcPosition, INT32 n32DstPosition, INT32 n32NbItemsToMove);

  INT16 GetPreviousItemData( INT8* pn8DataPtr);
  INT16 GetNextItemData( INT8* pn8DataPtr);
  INT16 GetFirstItemData( INT8* pn8DataPtr);
  INT16 GetLastItemData( INT8* pn8DataPtr);
  INT16 GetCurrentItemData( INT8* pn8DataPtr);
  INT16 GetItemData( INT8* pn8DataPtr, INT32 n32Position);

  INT16 InsertItem( INT8* pn8DataPtr, EListItem* pListItem);
  INT16 ModifyItem( INT8* pn8DataPtr, EListItem* pListItem);
  INT16 RemoveItem( EListItem* pListItem);
  INT16 MoveItems( EListItem* EListItemSrcPtr, EListItem* EListItemDstPtr, INT32 n32NbItemsToMove);
  
  EListItem* GetPreviousItemPtr( EListItem* pListItem);
  EListItem* GetNextItemPtr( EListItem* pListItem);
  EListItem* GetCurrentItemPtr( );
  EListItem* GetItemPtr( INT32 n32Position);

  INT16 GetPreviousItemData( INT8* pn8DataPtr, EListItem* pListItem);
  INT16 GetNextItemData( INT8* pn8DataPtr, EListItem* pListItem);
  INT16 GetItemData( INT8* pn8DataPtr, EListItem* pListItem);

  INT8* GetItemDataPtr( EListItem* pListItem);

  // inline functions
  inline INT32 GetNbUsedItems( );

  inline EListItem* GetFirstItemPtr();
  inline EListItem* GetLastItemPtr();

  inline INT16 TransferItem( EListItem* EListItemSrcPtr, EListItem* EListItemDstPtr);
  inline INT8* AddItem();
};

////////////////////////////////////////////////////////////////////////////////
// ERuns class
//

typedef struct 
{
  INT32 n32OrgX;
  INT32 n32OrgY;
  INT32 n32Len;
  INT32 n32Class;
  INT32 n32ObjNum;
  void* hpvReserved;
  void* hpvReserved2;
} ERunData;


class ERuns
{
private :
  
  
public :  
  EItemList* pRunList;
  
  // Constructors
  ERuns( INT16 n16NbRuns);
  ERuns( );
  ~ERuns( );
  
  // Access
  INT16 AddRun( ERunData* pRun);
  INT16 InsertRun( ERunData* pRun, INT32 n32Position);
  INT16 ModifyRun( ERunData* pRun, INT32 n32Position);
  INT16 RemoveRun( INT32 n32Position);
  INT16 RemoveAllRuns( );
  INT16 MoveRuns( INT32 n32SrcPosition, INT32 n32DstPosition, INT32 n32NbRunsToMove);
  
  INT16 GetPreviousRunData( ERunData* pRun);
  INT16 GetNextRunData( ERunData* pRun);
  INT16 GetFirstRunData( ERunData* pRun);
  INT16 GetLastRunData( ERunData* pRun);
  INT16 GetCurrentRunData( ERunData* pRun);
  INT16 GetRunData( ERunData* pRun, INT32 n32Position);
  
  /*INT16 GoToPosition( INT32 n32Position); 
  INT16 GoToBegin( );
  INT16 GoToEnd( );
  INT16 GoToNext( );
  INT16 GoToPrevious( );*/
  
  INT16 InsertRun( ERunData* pRun, EListItem* pListItem);
  INT16 ModifyRun( ERunData* pRun, EListItem* pListItem);
  INT16 RemoveRun( EListItem* pListItem);
  INT16 MoveRuns( EListItem* EListItemSrcPtr, EListItem* EListItemDstPtr, INT32 n32NbRunsToMove);
  
  EListItem* GetPreviousRunPtr( EListItem* pListItem);
  EListItem* GetNextRunPtr( EListItem* pListItem);
  EListItem* GetFirstRunPtr( );
  EListItem* GetLastRunPtr( );
  EListItem* GetCurrentRunPtr( );
  EListItem* GetRunPtr( INT32 n32Position);
  EListItem* GetRunPtrByCoordinates( INT32 n32X, INT32 n32Y);
  ERunData* GetRunDataPtr( EListItem* pListItem);
  
  INT16 GetPreviousRunData( ERunData* pRun, EListItem* pListItem);
  INT16 GetNextRunData( ERunData* pRun, EListItem* pListItem);
  INT16 GetRunData( ERunData* pRun, EListItem* pListItem);
  
  INT32 GetNumRuns( );
};



////////////////////////////////////////////////////////////////////////////////
// EObjects class
//

typedef struct 
{
  INT32 n32Class;
  INT32 n32ObjNum;
  INT32 n32ObjNbRun;
  INT32 n32ObjNbHole;
  UINT8 un8IsSelected;
  void* hpvReserved1;
  void* hpvReserved2;
  BOOL bIsHole;
  void* hpvParent;
  void* hpvFirstHole;
  void* hpvNextHole;
} EObjectData;


class EObjects
{
private :
  
public :
  EItemList* pObjList;
  INT32 n32NbSelectedObjects; 
  
  // Constructors
  EObjects( INT16 n16NbObjs);
  EObjects( );
  ~EObjects( );
  
  // Edition
  INT16 AddObj( EObjectData* pObj);
  INT16 InsertObj( EObjectData* pObj, INT32 n32ObjNum);
  INT16 ModifyObj( EObjectData* pObj, INT32 n32ObjNum);
  INT16 RemoveObj( INT32 n32ObjNum);
  INT16 RemoveAllObjs( );
  INT16 MoveObjs( INT32 n32SrcPosition, INT32 n32DstPosition, INT32 n32NbObjsToMove);
  
  INT16 GetPreviousObjData( EObjectData* pObject);
  INT16 GetNextObjData( EObjectData* pObject);
  INT16 GetFirstObjData( EObjectData* pObject);
  INT16 GetLastObjData( EObjectData* pObject);
  INT16 GetCurrentObjData( EObjectData* pObject);
  INT16 GetObjData( EObjectData* pObject, INT32 n32ObjNum);
  
  /*INT16 GoToPosition( INT32 n32Position); 
  INT16 GoToBegin( );
  INT16 GoToEnd( );
  INT16 GoToNext( );
  INT16 GoToPrevious( );*/
  
  INT16 InsertObj( EObjectData* pObject, EListItem* pListItem);
  INT16 ModifyObj( EObjectData* pObject, EListItem* pListItem);
  INT16 RemoveObj( EListItem* pListItem);
  INT16 MoveObjs( EListItem* EListItemSrcPtr, EListItem* EListItemDstPtr, INT32 n32NbObjsToMove);
  
  INT16 GetPreviousObjData( EObjectData* pObject, EListItem* pListItem);
  INT16 GetNextObjData( EObjectData* pObject, EListItem* pListItem);
  INT16 GetObjData( EObjectData* pObject, EListItem* pListItem);
  
  INT32 GetNumObjects( );
  INT16 AddRunToObj( INT32 n32ObjNum);
  void AddRunToObj( EListItem* pListItem);
  INT32 GetObjNbRun( INT32 n32ObjNum);
  INT32 GetObjNbRun( EListItem* pListItem);
  INT16 SetFirstRunPtr( EListItem* EListItemFirstRunPtr, INT32 n32ObjNum);
  INT16 SetFirstRunPtr( EListItem* EListItemFirstRunPtr, EListItem* pListItem);
  INT16 SetLastRunPtr( EListItem* EListItemLastRunPtr, INT32 n32ObjNum);
  INT16 SetLastRunPtr( EListItem* EListItemLastRunPtr, EListItem* pListItem);
  INT16 DetachRunsFromObj( INT32 n32ObjNum);
  INT16 DetachRunsFromObj( EListItem* pListItem);
  
  EListItem* GetObjPtrByNum( INT32 n32ObjNum);
  EListItem* GetPreviousObjPtr( EListItem* pListItem);
  EListItem* GetNextObjPtr( EListItem* pListItem);
  EListItem* GetFirstObjPtr( );
  EListItem* GetLastObjPtr( );
  EListItem* GetCurrentObjPtr( );
  EListItem* GetObjPtr( INT32 n32ObjNum);
  EListItem* GetObjFirstRunPtr( INT32 n32ObjNum);
  EListItem* GetObjFirstRunPtr( EListItem* pListItem);
  EListItem* GetObjLastRunPtr( INT32 n32ObjNum);
  EListItem* GetObjLastRunPtr( EListItem* pListItem);
  EObjectData* GetObjDataPtr( EListItem* pListItem);
  EListItem* GetObjPtrByPos( INT32 n32Position);
  
  INT32 GetNumSelectedObjects( );
  void SetNbSelectedObjects( INT32 n32NbSelectedObjects);
  INT16 SelectObject( INT32 n32ObjNum);
  INT16 SelectObject( EListItem* pListItem);
  INT16 UnselectObject( INT32 n32ObjNum);
  INT16 UnselectObject( EListItem* pListItem);
  INT16 IsObjectSelected( INT32 n32ObjNum, BOOL& bSelected);
  INT16 IsObjectSelected( EListItem* pListItem, BOOL& bSelected);
  void SelectAllObjects( );
  void UnselectAllObjects( );
};


////////////////////////////////////////////////////////////////////////////////
// EFeatures class
//

typedef struct 
{
  INT32 n32Size;
  INT32 n32FeatNum;
  INT32 n32FeatDataType;
  INT32 n32FeatDataSize;
  void* hpvStartPtr;
  void* hpvEndPtr;
} EFeatureData;

class EFeatures
{
private :
  void BlankFeatureArray( EFeatureData* pFeature);
  
public :
  
  EItemList* pFeatList;
  
  // Constructors
  EFeatures( );
  ~EFeatures( );
  
  //INT16 AddFeat( EFeatureData* pFeat, INT32 n32NbObj);
  INT16 SetFeatInfo( EFeatureData* pFeature, INT16 n16Feature);
  void BlankFeatures( );
  
  INT16 RemoveAllFeats( );
  INT32 GetNumFeatures( );
  
  inline EListItem* GetFeatPtrByNum( INT32 n32NumFeat);
  EFeatureData* GetFeatDataPtr( EListItem* pListItem);
  
  void* GetFeatArrayPtr( INT32 n32Position);
  void* GetFeatArrayPtr( EListItem* pListItem);
  INT32 GetFeatSize( INT32 n32Position);
  INT32 GetFeatSize( EListItem* pListItem);
  INT32 GetFeatNum( INT32 n32Position);
  INT32 GetFeatNum( EListItem* pListItem);
  INT32 GetFeatDataSize( INT32 n32Position);
  INT32 GetFeatDataSize( EListItem* pListItem);
  INT32 GetFeatDataType( INT32 n32Position);
  INT32 GetFeatDataType( EListItem* pListItem);
  
  
  INT16 GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT8& n8Result);
  INT16 GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT16& n16Result);
  INT16 GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT32& n32Result);
  INT16 GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT32& f32Result);
  INT16 GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT64& f64Result);
  INT16 GetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, INT8& n8Result);
  INT16 GetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, INT16& n16Result);
  INT16 GetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, INT32& n32Result);
  INT16 GetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, FLOAT32& f32Result);
  INT16 GetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, FLOAT64& f64Result);
  
  INT16 SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT8 n8Result);
  INT16 SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT16 n16Result);
  INT16 SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT32 n32Result);
  INT16 SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT32 f32Result);
  INT16 SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT64 f64Result);
  INT16 SetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, INT8 n8Result);
  INT16 SetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, INT16 n16Result);
  INT16 SetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, INT32 n32Result);
  INT16 SetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, FLOAT32 f32Result);
  INT16 SetObjectFeature( EListItem* pListItem, INT32 n32ObjNum, FLOAT64 f64Result);

  //Reserved
  EListItem** m_pPositionList;
};

////////////////////////////////////////////////////////////////////////////////
// ECodedImage class
//


class ECodedImage
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public :
  ERuns* pRun;
  EObjects* pObj;
  EFeatures* pFeat;
  
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1  ECodedImage( INT32 n32NbRuns, INT32 n32NbObjects);
  E_DLL0 CONSTRUCTOR E_DLL1  ECodedImage( );
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~ECodedImage( );
  
  // Deallocator
  E_DLL0 void E_DLL1  Deallocate( );
  
  E_DLL0 enum OBJ_THRESHOLD_MODES E_DLL1  GetThresholdMode( ) { return m_eThresholdMode; }
  E_DLL0 void E_DLL1  SetThresholdMode( enum OBJ_THRESHOLD_MODES eThresholdMode) { m_eThresholdMode = eThresholdMode; }

  E_DLL0 INT16 E_DLL1  SetWhiteClass( INT16 n16WhiteClass = 3);
  E_DLL0 INT16 E_DLL1  SetNeutralClass( INT16 n16NeutralClass = 2);
  E_DLL0 INT16 E_DLL1  SetBlackClass( INT16 n16BlackClass = 1);
  
  // Simple thresholding
  E_DLL0 void E_DLL1  SetThreshold( UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD);
  E_DLL0 void E_DLL1  SetThresholdImage( EROIBW8* pImage);
  
  // Double thresholding
  E_DLL0 INT16 E_DLL1  SetLowThreshold( UINT32 un32LowThreshold);
  E_DLL0 INT16 E_DLL1  SetLowImage( EROIBW8* pImage);
  E_DLL0 INT16 E_DLL1  SetHighThreshold( UINT32 un32HighThreshold);
  E_DLL0 INT16 E_DLL1  SetHighImage( EROIBW8* pImage);
  
  // Color thresholding
  E_DLL0 INT16 E_DLL1  SetLowColorThreshold( EC24 c24LowThreshold);
  E_DLL0 INT16 E_DLL1  SetHighColorThreshold( EC24 c24HighThreshold);
  
  E_DLL0 INT16 E_DLL1  SetOrgX( INT32 n32OrgX);
  E_DLL0 INT16 E_DLL1  SetOrgY( INT32 n32OrgY);
  E_DLL0 void E_DLL1  SetContinuous( BOOL bContinuous) { m_bContinuous = bContinuous; }
  E_DLL0 INT16 E_DLL1  SetYOriginOffset( INT32 n32YOriginOffset);
  E_DLL0 INT16 E_DLL1  SetCutObjects( INT32 n32CutObjects);
  E_DLL0 INT16 E_DLL1  SetMaxObjectHeight( INT32 n32MaxObjectHeight);
  E_DLL0 INT16 E_DLL1  SetBuildRunsTimeOut( INT32 n32Build_Runs_TimeOut);
  E_DLL0 INT16 E_DLL1  SetBuildObjectsTimeOut( INT32 n32BuildObjectsTimeOut);
  E_DLL0 INT16 E_DLL1  SetSourceImage( EGenericROI* pSourceImage);
  
  E_DLL0 INT16 E_DLL1  GetWhiteClass( );
  E_DLL0 INT16 E_DLL1  GetNeutralClass( );
  E_DLL0 INT16 E_DLL1  GetBlackClass( );
  
  E_DLL0 enum OBJECT_CONNEXITY E_DLL1  GetConnexity( );
  E_DLL0 void E_DLL1  SetConnexity( enum OBJECT_CONNEXITY eConnexity);
  
  E_DLL0 UINT32 E_DLL1  GetLowThreshold( );
  E_DLL0 EC24 E_DLL1  GetLowColorThreshold( );
  E_DLL0 EGenericROI* E_DLL1  GetLowImage( );
  E_DLL0 UINT32 E_DLL1  GetHighThreshold( );
  E_DLL0 EC24 E_DLL1  GetHighColorThreshold( );
  E_DLL0 EGenericROI* E_DLL1  GetHighImage( );
  E_DLL0 UINT32 E_DLL1  GetThreshold( );
  E_DLL0 UINT32 E_DLL1  GetTrueThreshold( ) { return m_un32TrueThreshold; }

  E_DLL0 INT32 E_DLL1  GetOrgX( );
  E_DLL0 INT32 E_DLL1  GetOrgY( );
  E_DLL0 BOOL E_DLL1  GetContinuous( ) { return m_bContinuous; }
  E_DLL0 INT32 E_DLL1  GetYOriginOffset( );
  E_DLL0 INT32 E_DLL1  GetCutObjects( );
  E_DLL0 INT32 E_DLL1  GetMaxObjectHeight( );
  E_DLL0 INT32 E_DLL1  GetBuildRunsTimeOut( );
  E_DLL0 INT32 E_DLL1  GetBuildObjectsTimeOut( );
  E_DLL0 EGenericROI* E_DLL1  GetSourceImage( );
  
  /////////////////////////////////////////////////////////////
  // Runs construction
  //
  E_DLL0 void E_DLL1  BuildRuns( EROIBW1* pSrcImage);
  E_DLL0 void E_DLL1  BuildRuns( EROIBW8* pSrcImage);
  E_DLL0 void E_DLL1  BuildRuns( EROIC24* pSrcImage);
  
  E_DLL0 void E_DLL1  BuildLabeledRuns( EROIBW8* pSrcImage);
  E_DLL0 void E_DLL1  BuildLabeledRuns( EROIBW16* pSrcImage);

  E_DLL0 void E_DLL1  BuildThresholdedRuns( EROIBW1* pSrcImage);
  E_DLL0 void E_DLL1  BuildThresholdedRuns( EROIBW8* pSrcImage);

  /////////////////////////////////////////////////////////////
  // Objects construction
  //
  E_DLL0 void E_DLL1  BuildObjects( );
  E_DLL0 void E_DLL1  BuildObjects( EROIBW1* pSrcImage);
  E_DLL0 void E_DLL1  BuildObjects( EROIBW8* pSrcImage);
  E_DLL0 void E_DLL1  BuildObjects( EROIC24* pSrcImage);
  
  E_DLL0 void E_DLL1  BuildLabeledObjects( EROIBW8* pSrcImage);
  E_DLL0 void E_DLL1  BuildLabeledObjects( EROIBW16* pSrcImage);
  
  E_DLL0 void E_DLL1  BuildThresholdedObjects( EROIBW1* pSrcImage);
  E_DLL0 void E_DLL1  BuildThresholdedObjects( EROIBW8* pSrcImage);


  /////////////////////////////////////////////////////////////
  // Object features computation
  //
  E_DLL0 void E_DLL1  AnalyseObjects
    ( INT16 n16Feature1 = NULL, INT16 n16Feature2 = NULL, INT16 n16Feature3 = NULL,
    INT16 n16Feature4 = NULL, INT16 n16Feature5 = NULL, INT16 n16Feature6 = NULL, 
    INT16 n16Feature7 = NULL, INT16 n16Feature8 = NULL, INT16 n16Feature9 = NULL,
    INT16 n16Feature10 = NULL);
  
  E_DLL0 void E_DLL1  FeatureMinimum( enum OBJECT_FEATURES eFeature, FLOAT32& f32Minimum);
  E_DLL0 void E_DLL1  FeatureMaximum( enum OBJECT_FEATURES eFeature, FLOAT32& f32Maximum);
  E_DLL0 void E_DLL1  FeatureAverage( enum OBJECT_FEATURES eFeature, FLOAT32& f32Average);
  E_DLL0 void E_DLL1  FeatureVariance( enum OBJECT_FEATURES eFeature, FLOAT32& f32Average, FLOAT32& f32Variance);
  E_DLL0 void E_DLL1  FeatureDeviation( enum OBJECT_FEATURES eFeature, FLOAT32& f32Average, FLOAT32& f32Deviation);
  
  // Special features
  E_DLL0 void E_DLL1  ObjectConvexHull( EListItem* pObject, EPathVector* pDst);
  
  E_DLL0 void E_DLL1  SetLimitAngle( FLOAT32 f32Angle);
  E_DLL0 FLOAT32 E_DLL1  GetLimitAngle( );
  
  /////////////////////////////////////////////////////////////
  // Objects selection
  //
  E_DLL0 void E_DLL1  SelectObjectsUsingFeature( enum OBJECT_FEATURES Feature, 
    INT8 n8Min, INT8 n8Max, enum SELECT_OPTIONS Operation);
  E_DLL0 void E_DLL1  SelectObjectsUsingFeature( enum OBJECT_FEATURES Feature, 
    INT16 n16Min, INT16 n16Max, enum SELECT_OPTIONS Operation);
  E_DLL0 void E_DLL1  SelectObjectsUsingFeature( enum OBJECT_FEATURES Feature, 
    INT32 n32Min, INT32 n32Max, enum SELECT_OPTIONS Operation);
  E_DLL0 void E_DLL1  SelectObjectsUsingFeature( enum OBJECT_FEATURES Feature, 
    FLOAT32 f32Min, FLOAT32 f32Max, enum SELECT_OPTIONS Operation);
  E_DLL0 void E_DLL1  SelectObjectsUsingFeature( enum OBJECT_FEATURES Feature, 
    FLOAT64 f64Min, FLOAT64 f64Max, enum SELECT_OPTIONS Operation);
  E_DLL0 void E_DLL1  SelectObjectsUsingPosition( EGenericROI* pROI, 
    enum SELECT_BY_POSITION Operation);
  E_DLL0 void E_DLL1  SelectObjectsUsingPosition
    ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height, 
    enum SELECT_BY_POSITION Operation);
  
  /////////////////////////////////////////////////////////////
  // Objects sorting
  //
  E_DLL0 void E_DLL1  SortObjectsUsingFeature( enum OBJECT_FEATURES Feature,
    enum SORT_OPTIONS Operation);
  
  // Runs manipulation
  E_DLL0 INT16 E_DLL1  AddRun( ERunData* pRunData);
  E_DLL0 INT16 E_DLL1  InsertRun( ERunData* pRunData, INT32 n32Position);
  E_DLL0 INT16 E_DLL1  ModifyRun( ERunData* pRunData, INT32 n32Position);
  E_DLL0 INT16 E_DLL1  RemoveRun( INT32 n32Position);
  E_DLL0 INT16 E_DLL1  RemoveAllRuns( );
  E_DLL0 INT16 E_DLL1  MoveRuns( INT32 n32SrcPosition, INT32 n32DstPosition, INT32 n32NbRunsToMove);
  
  E_DLL0 INT16 E_DLL1  GetPreviousRunData( ERunData* pRunData);
  E_DLL0 INT16 E_DLL1  GetNextRunData( ERunData* pRunData);
  E_DLL0 INT16 E_DLL1  GetFirstRunData( ERunData* pRunData);
  E_DLL0 INT16 E_DLL1  GetLastRunData( ERunData* pRunData);
  E_DLL0 INT16 E_DLL1  GetCurrentRunData( ERunData* pRunData);
  E_DLL0 INT16 E_DLL1  GetRunData( ERunData* pRunData, INT32 n32Position);
  
  E_DLL0 INT16 E_DLL1  InsertRun( ERunData* pRunData, EListItem* pRunToInsertAfter);
  E_DLL0 INT16 E_DLL1  ModifyRun( ERunData* pRunData, EListItem* pRunToModify);
  E_DLL0 INT16 E_DLL1  RemoveRun( EListItem* pRunToRemove);
  E_DLL0 INT16 E_DLL1  MoveRuns( EListItem* pSrcRun, EListItem* pDstRun, INT32 n32NbRunsToMove);
  
  E_DLL0 EListItem* E_DLL1  GetPreviousRunPtr( EListItem* pCurrentRun);
  E_DLL0 EListItem* E_DLL1  GetNextRunPtr( EListItem* pCurrentRun);
  E_DLL0 EListItem* E_DLL1  GetFirstRunPtr( );
  E_DLL0 EListItem* E_DLL1  GetLastRunPtr( );
  E_DLL0 EListItem* E_DLL1  GetCurrentRunPtr( );
  E_DLL0 EListItem* E_DLL1  GetRunPtr( INT32 n32Position);
  E_DLL0 EListItem* E_DLL1  GetRunPtrByCoordinates( INT32 n32X, INT32 n32Y);
  E_DLL0 ERunData* E_DLL1  GetRunDataPtr( EListItem* pListItem);
  
  E_DLL0 INT16 E_DLL1  GetPreviousRunData( ERunData* pRunData, EListItem* pCurrentRun);
  E_DLL0 INT16 E_DLL1  GetNextRunData( ERunData* pRunData, EListItem* pCurrentRun);
  E_DLL0 INT16 E_DLL1  GetRunData( ERunData* pRunData, EListItem* pCurrentRun);
  
  E_DLL0 INT32 E_DLL1  GetNbRuns( );
  
  
  // Object manipulation
  E_DLL0 UINT32 E_DLL1  GetMaxObjects( ) { return m_un32MaxObjects; }
  E_DLL0 void E_DLL1  SetMaxObjects( UINT32 un32MaxObjects) { m_un32MaxObjects = un32MaxObjects; }

  E_DLL0 INT16 E_DLL1  AddObj( EObjectData* pObjData);
  E_DLL0 INT16 E_DLL1  InsertObj( EObjectData* pObjData, INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  ModifyObj( EObjectData* pObjData, INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  RemoveObj( INT32 n32ObjNum);
         INT16         RemoveObject( INT32 n32ObjNum) {return this->RemoveObj(n32ObjNum);};
  E_DLL0 INT16 E_DLL1  RemoveAllObjs( );
  E_DLL0 INT16 E_DLL1  MoveObjs( INT32 n32SrcPosition, INT32 n32DstPosition, INT32 n32NbObjsToMove);
  
  E_DLL0 INT16 E_DLL1  GetPreviousObjData( EObjectData* pObjData);
  E_DLL0 INT16 E_DLL1  GetNextObjData( EObjectData* pObjData);
  E_DLL0 INT16 E_DLL1  GetFirstObjData( EObjectData* pObjData);
  E_DLL0 INT16 E_DLL1  GetLastObjData( EObjectData* pObjData);
  E_DLL0 INT16 E_DLL1  GetCurrentObjData( EObjectData* pObjData);
  E_DLL0 INT16 E_DLL1  GetObjData( EObjectData* pObjData, INT32 n32ObjNum);
  
  E_DLL0 INT16 E_DLL1  InsertObj( EObjectData* pObjData, EListItem* pObjectToInsertAfter);
  E_DLL0 INT16 E_DLL1  ModifyObj( EObjectData* pObjData, EListItem* pObjectToModify);
  E_DLL0 INT16 E_DLL1  RemoveObj( EListItem* pObjectToRemove);
         INT16         RemoveObject( EListItem* pObjectToRemove) {return this->RemoveObj(pObjectToRemove);};
  E_DLL0 INT16 E_DLL1  MoveObjs( EListItem* pSrcObject, EListItem* pDstObject, INT32 n32NbObjsToMove);
  
  E_DLL0 INT16 E_DLL1  GetPreviousObjData( EObjectData* pObjData, EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  GetNextObjData( EObjectData* pObjData, EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  GetObjData( EObjectData* pObjData, EListItem* pCurrentObject);
  
  E_DLL0 INT32 E_DLL1  GetNumObjects( );
  E_DLL0 INT16 E_DLL1  AddRunToObj( INT32 n32ObjNum);
  E_DLL0 void E_DLL1  AddRunToObj( EListItem* pObjectToAddTo);
  E_DLL0 INT32 E_DLL1  GetNumObjectRuns( INT32 n32ObjNum);
  E_DLL0 INT32 E_DLL1  GetNumObjectRuns( EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  SetFirstRunPtr( EListItem* pFirstRun, INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  SetFirstRunPtr( EListItem* pFirstRun, EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  SetLastRunPtr( EListItem* pLastRun, INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  SetLastRunPtr( EListItem* pLastRun, EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  DetachRunsFromObj( INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  DetachRunsFromObj( EListItem* pCurrentObject);
  
  E_DLL0 EListItem* E_DLL1  GetObjPtrByNum( INT32 n32ObjNum);
  E_DLL0 EListItem* E_DLL1  GetPreviousObjPtr( EListItem* pCurrentObject);
  E_DLL0 EListItem* E_DLL1  GetNextObjPtr( EListItem* pCurrentObject);
  E_DLL0 EListItem* E_DLL1  GetFirstObjPtr( );
  E_DLL0 EListItem* E_DLL1  GetLastObjPtr( );
  E_DLL0 EListItem* E_DLL1  GetCurrentObjPtr( );
  E_DLL0 EListItem* E_DLL1  GetObjPtr( INT32 n32ObjNum);
  E_DLL0 EListItem* E_DLL1  GetObjPtrByCoordinates( INT32 n32X, INT32 n32Y);
  E_DLL0 EListItem* E_DLL1  GetObjFirstRunPtr( INT32 n32ObjNum);
  E_DLL0 EListItem* E_DLL1  GetObjFirstRunPtr( EListItem* pCurrentObject);
  E_DLL0 EListItem* E_DLL1  GetObjLastRunPtr( INT32 n32ObjNum);
  E_DLL0 EListItem* E_DLL1  GetObjLastRunPtr( EListItem* pCurrentObject);
  E_DLL0 EObjectData* E_DLL1  GetObjDataPtr( EListItem* pCurrentObject);
  
  E_DLL0 INT32 E_DLL1  GetNumSelectedObjects( );
  E_DLL0 void E_DLL1  SetNbSelectedObjects( INT32 n32Nb_Selected_Objects);
  E_DLL0 void E_DLL1  SetNumSelectedObjects( INT32 n32Nb_Selected_Objects);
  E_DLL0 INT16 E_DLL1  SelectObject( INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  SelectObject( EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  UnselectObject( INT32 n32ObjNum);
  E_DLL0 INT16 E_DLL1  UnselectObject( EListItem* pCurrentObject);
  E_DLL0 INT16 E_DLL1  IsObjectSelected( INT32 n32ObjNum, BOOL& bSelected);
  E_DLL0 INT16 E_DLL1  IsObjectSelected( EListItem* pCurrentObject, BOOL& bSelected);
  E_DLL0 EListItem* E_DLL1  GetObjPtrByPos( INT32 n32Position);
  E_DLL0 void E_DLL1  SelectAllObjects( );
  E_DLL0 void E_DLL1  UnselectAllObjects( );
  
  // Drawing
  E_DLL0 void E_DLL1  DrawObjects( HDC hDC, enum E_SELECTION_MODE eSelectionMode = E_SELECTED_TRUE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObject( HDC hDC, INT32 n32ObjectNumber,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObject( HDC hDC, EListItem* pObject,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  E_DLL0 void E_DLL1  DrawObjectsFeature( HDC hDC, enum OBJECT_FEATURES eFeature, enum E_SELECTION_MODE eSelectionMode = E_SELECTED_TRUE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObjectFeature( HDC hDC, enum OBJECT_FEATURES eFeature, EListItem* pObject,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObjectFeature( HDC hDC, enum OBJECT_FEATURES eFeature, INT32 n32ObjectNumber,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

    E_DLL0 void E_DLL1  DrawObjects( Euresys::DrawAdapter* drawAdapter, enum E_SELECTION_MODE eSelectionMode = E_SELECTED_TRUE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObject( Euresys::DrawAdapter* drawAdapter, INT32 n32ObjectNumber,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObject( Euresys::DrawAdapter* drawAdapter, EListItem* pObject,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  E_DLL0 void E_DLL1  DrawObjectsFeature( Euresys::DrawAdapter* drawAdapter, enum OBJECT_FEATURES eFeature, enum E_SELECTION_MODE eSelectionMode = E_SELECTED_TRUE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObjectFeature( Euresys::DrawAdapter* drawAdapter, enum OBJECT_FEATURES eFeature, EListItem* pObject,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawObjectFeature( Euresys::DrawAdapter* drawAdapter, enum OBJECT_FEATURES eFeature, INT32 n32ObjectNumber,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 BOOL E_DLL1  GetDrawDiagonals( ) { return m_bDrawDiagonals; }
  E_DLL0 void E_DLL1  SetDrawDiagonals( BOOL bDrawDiagonals) { m_bDrawDiagonals = bDrawDiagonals; }

  // Features manipulation
  E_DLL0 INT16 E_DLL1  AddFeat( EFeatureData* pFeatData, INT32 n32NbObj);
  E_DLL0 INT16 E_DLL1  SetFeatInfo( EFeatureData* pFeatData, INT16 n16Feature);
  E_DLL0 void E_DLL1  BlankFeatures( );
  E_DLL0 void E_DLL1  BlankFeatureArray( EFeatureData* pFeatData);
  
  E_DLL0 INT16 E_DLL1  RemoveAllFeats( );
  E_DLL0 INT32 E_DLL1  GetNumFeatures( );
  
  E_DLL0 EListItem* E_DLL1  GetFeatPtrByNum( INT32 n32NumFeat);
  E_DLL0 EFeatureData* E_DLL1  GetFeatDataPtr( EListItem* pCurrentFeature);
  
  E_DLL0 void* E_DLL1  GetFeatArrayPtr( INT32 n32Position);
  E_DLL0 void* E_DLL1  GetFeatArrayPtr( EListItem* pCurrentFeature);
  E_DLL0 INT32 E_DLL1  GetFeatSize( INT32 n32Position);
  E_DLL0 INT32 E_DLL1  GetFeatSize( EListItem* pCurrentFeature);
  E_DLL0 INT32 E_DLL1  GetFeatNum( INT32 n32Position);
  E_DLL0 INT32 E_DLL1  GetFeatNum( EListItem* pCurrentFeature);
  E_DLL0 INT32 E_DLL1  GetFeatDataSize( INT32 n32Position);
  E_DLL0 INT32 E_DLL1  GetFeatDataSize( EListItem* pCurrentFeature);
  E_DLL0 INT32 E_DLL1  GetFeatDataType( INT32 n32Position);
  E_DLL0 INT32 E_DLL1  GetFeatDataType( EListItem* pCurrentFeature);
  
  E_DLL0 void E_DLL1  GetObjectFeature( enum OBJECT_FEATURES eFeature, EListItem* pObject, INT8& n8Result);
  E_DLL0 void E_DLL1  GetObjectFeature( enum OBJECT_FEATURES eFeature, EListItem* pObject, INT16& n16Result);
  E_DLL0 void E_DLL1  GetObjectFeature( enum OBJECT_FEATURES eFeature, EListItem* pObject, INT32& n32Result);
  E_DLL0 void E_DLL1  GetObjectFeature( enum OBJECT_FEATURES eFeature, EListItem* pObject, FLOAT32& f32Result);
  E_DLL0 void E_DLL1  GetObjectFeature( enum OBJECT_FEATURES eFeature, EListItem* pObject, FLOAT64& f64Result);
  
  E_DLL0 INT16 E_DLL1  GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT8& n8Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT16& n16Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT32& n32Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT32& f32Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT64& f64Result);
  
  E_DLL0 INT16 E_DLL1  GetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, INT8& n8Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, INT16& n16Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, INT32& n32Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, FLOAT32& f32Result);
  E_DLL0 INT16 E_DLL1  GetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, FLOAT64& f64Result);
  
  E_DLL0 INT16 E_DLL1  SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT8 n8Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT16 n16Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, INT32 n32Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT32 f32Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( INT32 n32NumFeat, INT32 n32ObjNum, FLOAT64 f64Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, INT8 n8Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, INT16 n16Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, INT32 n32Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, FLOAT32 f32Result);
  E_DLL0 INT16 E_DLL1  SetObjectFeature( EListItem* pCurrentFeature, INT32 n32ObjNum, FLOAT64 f64Result);
  
  void PrepareRunsContinuousMode( );
  void RemoveCompleteObjects( );
  EListItem* m_pPreviousImageLastRun;
  EListItem* m_pPreviousImageFirstRunLastLine;
  
protected:
  enum OBJ_THRESHOLD_MODES m_eThresholdMode; 
  UINT32 m_un32TrueThreshold; 
  UINT32 m_un32MaxObjects; 
  BOOL m_bDrawDiagonals; 

private :
  // Classes
  INT16 n16WhiteClass;
  INT16 n16NeutralClass;
  INT16 n16BlackClass;
  
  // Source image
  EGenericROI* m_pSourceImage;
  
  // Thresholds
  UINT32 m_un32LowThreshold, m_un32HighThreshold;
  EC24 m_c24LowThreshold, m_c24HighThreshold;
  EGenericROI* m_pLowImage, * m_pHighImage;
  
  INT32 m_n32OrgX;
  INT32 m_n32OrgY;

  BOOL m_bContinuous;
  INT32 n32YOriginOffset;

  INT32 n32CutObjects;
  INT32 n32MaxObjectHeight;
  INT32 n32BuildRunsTimeOut;
  INT32 n32BuildObjectsTimeOut;
  
  // Features
  FLOAT32 m_f32LimitAngle;
  INT32 m_n32LimitAngleCos, m_n32LimitAngleSin;
  
  // Connexity
  enum OBJECT_CONNEXITY m_eConnexity;
  
  // Auto-threshold
  EBWHistogramVector m_Histo;
  
  // Helpers
  void BuildRunsSingleCst( );
  void BuildRunsSingleImg( );
  void BuildRunsDoubleCstCst( );
  void BuildRunsDoubleCstImg( );
  void BuildRunsDoubleImgCst( );
  void BuildRunsDoubleImgImg( );
  
  friend INT16 ObjFeatLimitAngledRectangle( ECodedImage* pCodedImage);

public:
  // Hole management
  E_DLL0 void E_DLL1 BuildHoles();
  E_DLL0 void E_DLL1 BuildHoles(EListItem* pObject);
  E_DLL0 void E_DLL1 RemoveHoles(EListItem* pObject= NULL);
  
  E_DLL0 void E_DLL1 SelectHoles(EListItem* pParentObject= NULL);
  E_DLL0 void E_DLL1 UnselectHoles(EListItem* pParentObject= NULL);

  E_DLL0 EListItem* E_DLL1 GetFirstHole(EListItem* pParentObject);
  E_DLL0 EListItem* E_DLL1 GetNextHole(EListItem* pHole);
  E_DLL0 EListItem* E_DLL1 GetHoleParentObject(EListItem* pHole);

  E_DLL0 BOOL E_DLL1 IsHole(EListItem* pObject);

  E_DLL0 INT32 E_DLL1 GetNumHoles(EListItem* pObject= NULL);
  E_DLL0 INT32 E_DLL1 GetObjectNumHoles() {return this->GetNumHoles( NULL ); };
  E_DLL0 INT32 E_DLL1 GetNumHoleRuns();

private:
  void CleanObjectHolesInformation();
  void ArrangeHolesByObject();
  void BuildObjectHolesRuns(EListItem* pObj, ERuns* pRuns);
  void TransferObjects(ECodedImage* pSource, ECodedImage* pDestination);

  INT32 BuildObjectHoles(ERuns* pRuns);
  
  INT32 m_n32NumHoles;
  INT32 m_n32NumHoleRuns;
};


/////////////////////////////////////////////////////////////
// Runs construction
//
E_DLL0 void E_DLL1  ObjBuildRuns( EROIBW8* pSrcImage, ECodedImage* pDstCodedImage);
E_DLL0 void E_DLL1  ObjBuildRuns( EROIC24* pSrcImage, ECodedImage* pDstCodedImage);

E_DLL0 void E_DLL1  ObjBuildLabeledRuns( EROIBW8* pSrcImage, ECodedImage* pDstCodedImage);
E_DLL0 void E_DLL1  ObjBuildLabeledRuns( EROIBW16* pSrcImage, ECodedImage* pDstCodedImage);

E_DLL0 void E_DLL1  ObjBuildThresholdedRuns( EROIBW1* pSrcImage, ECodedImage* pDstCodedImage);
E_DLL0 void E_DLL1  ObjBuildThresholdedRuns( EROIBW8* pSrcImage, ECodedImage* pDstCodedImage);

/////////////////////////////////////////////////////////////
// Objects construction
//
E_DLL0 INT16 E_DLL1  ObjBuildObjects( ECodedImage* pDstCodedImage);
E_DLL0 INT16 E_DLL1  ObjBuildObjects( EROIBW8* pSrcImage, ECodedImage* pDstCodedImage);
E_DLL0 INT16 E_DLL1  ObjBuildObjects( EROIC24* pSrcImage, ECodedImage* pDstCodedImage);

E_DLL0 void E_DLL1  ObjBuildLabeledObjects( EROIBW8* pSrcImage, ECodedImage* pDstCodedImage);
E_DLL0 void E_DLL1  ObjBuildLabeledObjects( EROIBW16* pSrcImage, ECodedImage* pDstCodedImage);

E_DLL0 void E_DLL1  ObjBuildThresholdedObjects( EROIBW1* pSrcImage, ECodedImage* pDstCImage);
E_DLL0 void E_DLL1  ObjBuildThresholdedObjects( EROIBW8* pSrcImage, ECodedImage* pDstCImage);

E_DLL0 void E_DLL1  ObjMergeObjects( ECodedImage* pOrgCImage, EListItem *pObject1, EListItem *pObject2);

/////////////////////////////////////////////////////////////
// Object features computation
E_DLL0 INT16 E_DLL1  ObjAnalyseObjects
( ECodedImage* pSrcCodedImage,
 INT16 n16Feature1 = NULL, INT16 n16Feature2 = NULL, INT16 n16Feature3 = NULL,
 INT16 n16Feature4 = NULL, INT16 n16Feature5 = NULL, INT16 n16Feature6 = NULL, 
 INT16 n16Feature7 = NULL, INT16 n16Feature8 = NULL, INT16 n16Feature9 = NULL,
 INT16 n16Feature10 = NULL);

E_DLL0 INT16 E_DLL1 ObjReComputeFeature( ECodedImage *pOrgCImage);

E_DLL0 void E_DLL1  ObjFeatureMinimum
( ECodedImage* pCodedImage, enum OBJECT_FEATURES eFeature,
 FLOAT32& f32Minimum);
E_DLL0 void E_DLL1  ObjFeatureMaximum
( ECodedImage* pCodedImage, enum OBJECT_FEATURES eFeature,
 FLOAT32& f32Maximum);
E_DLL0 void E_DLL1  ObjFeatureAverage
( ECodedImage* pCodedImage, enum OBJECT_FEATURES eFeature,
 FLOAT32& f32Average);
E_DLL0 void E_DLL1  ObjFeatureVariance
( ECodedImage* pCodedImage, enum OBJECT_FEATURES eFeature,
 FLOAT32& f32Average, FLOAT32& f32Variance);
E_DLL0 void E_DLL1  ObjFeatureDeviation
( ECodedImage* pCodedImage, enum OBJECT_FEATURES eFeature,
 FLOAT32& f32Average, FLOAT32& f32Deviation);

E_DLL0 void E_DLL1 FeretRectangle( EPathVector* pConvex, FLOAT32& f32Width, FLOAT32& f32Height, FLOAT32& f32CenterX, FLOAT32& f32CenterY, FLOAT32& f32Angle);

/////////////////////////////////////////////////////////////
// Objects selection
//
E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingFeature
( ECodedImage* pSrcCodedImage, enum OBJECT_FEATURES Feature, 
 INT8 n8Min, INT8 n8Max, enum SELECT_OPTIONS Operation);
E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingFeature
( ECodedImage* pSrcCodedImage, enum OBJECT_FEATURES Feature, 
 INT16 n16Min, INT16 n16Max, enum SELECT_OPTIONS Operation);
E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingFeature
( ECodedImage* pSrcCodedImage, enum OBJECT_FEATURES Feature, 
 INT32 n32Min, INT32 n32Max, enum SELECT_OPTIONS Operation);
E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingFeature
( ECodedImage* pSrcCodedImage, enum OBJECT_FEATURES Feature, 
 FLOAT32 f32Min, FLOAT32 f32Max, enum SELECT_OPTIONS Operation);
E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingFeature
( ECodedImage* pSrcCodedImage, enum OBJECT_FEATURES Feature, 
 FLOAT64 f64Min, FLOAT64 f64Max, enum SELECT_OPTIONS Operation);

E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingPosition
( ECodedImage* pSrcCodedImage, EGenericROI* pROI, 
 enum SELECT_BY_POSITION Operation);
E_DLL0 INT16 E_DLL1  ObjSelectObjectsUsingPosition
( ECodedImage* pSrcCodedImage,
 INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height, 
 enum SELECT_BY_POSITION Operation);

/////////////////////////////////////////////////////////////
// Objects sorting
//
E_DLL0 INT16 E_DLL1  ObjSortObjectsUsingFeature
( ECodedImage* pSrcCodedImage, enum OBJECT_FEATURES Feature, 
 enum SORT_OPTIONS Operation);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Contour features

E_DLL0 void E_DLL1  ObjContourArea
( EPathVector* pPathVector,
 INT32& n32Area);

E_DLL0 void E_DLL1  ObjContourGravityCenter
( EPathVector* pPathVector,
 INT32& n32Area,
 FLOAT32& f32GravityCenterX, FLOAT32& f32GravityCenterY);

E_DLL0 void E_DLL1  ObjContourInertia
( EPathVector* pPathVector,
 INT32& n32Area,
 FLOAT32& f32GravityCenterX, FLOAT32& f32GravityCenterY,
 FLOAT32& f32SigmaX, FLOAT32& f32SigmaY, FLOAT32& f32SigmaXY);

#endif //__EOBJECT_H__
