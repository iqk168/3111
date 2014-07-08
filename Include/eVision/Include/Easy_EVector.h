// Easy_EVector.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EVECTOR_H__
#define __EASY_EVECTOR_H__

class EVector
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

private:
  INT32                               m_n32AllocatedSize;
  INT32                               m_n32DataType;
  INT32                               m_n32NbGroup;
  INT32                               m_n32GroupLength;
  INT32                               m_n32NbMaxGroup;
  INT32                               m_n32DataSize;
  INT32                               m_n32VectType;
  INT32                               m_n32Use;
  INT32                               m_n32Param0;
  INT32                               m_n32Param1;
  INT32                               m_n32Param2;
  INT32                               m_n32Param3;
  INT32                               m_n32Param4;
  INT32                               m_n32Param5;
  INT32                               m_n32Param6;
  INT32                               m_n32Param7;
  void*                               m_DataPtr;

public :
  E_DLL0 CONSTRUCTOR E_DLL1           EVector               ( INT32 n32AllocateMemory = 0);
  virtual E_DLL0 DESTRUCTOR E_DLL1    ~EVector              ( );

  E_DLL0 void* E_DLL1                 GetDataPtr            ( );
  E_DLL0 INT16 E_DLL1                 SetStructure          ( INT32 n32DataSize, INT32 n32NGroup, INT32 n32GroupLength, INT32 n32DataType);
  E_DLL0 INT16 E_DLL1                 SetType               ( INT32 n32VectType, INT32 n32NGroup, INT32 n32GroupLength = 0);
  E_DLL0 INT16 E_DLL1                 SetAllocatedSize      ( INT32 n32AllocateMemory);
  E_DLL0 INT16 E_DLL1                 SetItemsAllocatedSize ( INT32 n32NItemsToAllocate);
  E_DLL0 INT16 E_DLL1                 Reallocate            ( INT32 n32AllocateMemory);
  E_DLL0 void E_DLL1                  SetDataSize           ( INT32 n32NewVal);
  E_DLL0 void E_DLL1                  SetNbGroup            ( INT32 n32NewVal);
  E_DLL0 void E_DLL1                  SetNbMaxGroup         ( );
  E_DLL0 void E_DLL1                  SetGroupLength        ( INT32 n32NewVal);
  E_DLL0 void E_DLL1                  SetUse                ( INT32 n32NewVal);
  E_DLL0 void E_DLL1                  SetDataType           ( INT32 n32NewVal);
  E_DLL0 void E_DLL1                  SetVectType           ( INT32 n32NewVal);
  E_DLL0 BOOL E_DLL1                  IsSameVectType        ( INT32 n32VectType);

  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, UINT8* pun8Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, UINT16* pun16Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, UINT32* pun32Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, INT8* pn8Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, INT16* pn16Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, INT32* pn32Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, FLOAT32* pf32Data);
  E_DLL0 INT16 E_DLL1                 GetGroups             ( INT32 n32StartGroup, INT32 n32Number, FLOAT64* pf64Data);

  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, UINT8& un8Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, UINT16& un16Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, UINT32& un32Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, INT8& n8Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, INT16& n16Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, INT32& n32Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, FLOAT32& f32Data);
  E_DLL0 INT16 E_DLL1                 GetData               ( INT32 n32Group, INT32 n32Offset, FLOAT64& f64Data);

  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, UINT8* pun8Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, UINT16* pun16Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, UINT32* pun32Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, INT8* pn8Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, INT16* pn16Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, INT32* pn32Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, FLOAT32* pf32Data);
  E_DLL0 INT16 E_DLL1                 SetGroups             ( INT32 n32StartGroup, INT32 n32Number, FLOAT64* pf64Data);

  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, UINT8 un8Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, UINT16 un16Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, UINT32 un32Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, INT8 n8Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, INT16 n16Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, INT32 n32Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, FLOAT32 f32Data);
  E_DLL0 INT16 E_DLL1                 SetData               ( INT32 n32Group, INT32 n32Offset, FLOAT64 f64Data);

  E_DLL0 INT32 E_DLL1                 GetAllocatedSize      ( );
  E_DLL0 INT32 E_DLL1                 GetDataType           ( );
  E_DLL0 INT32 E_DLL1                 GetDataSize           ( );
  E_DLL0 INT32 E_DLL1                 GetVectType           ( );
  E_DLL0 INT32 E_DLL1                 GetNbGroup            ( );
  E_DLL0 INT32 E_DLL1                 GetNbMaxGroup         ( );
  E_DLL0 INT32 E_DLL1                 GetGroupLength        ( );
  E_DLL0 INT32 E_DLL1                 GetUse                ( );
};

#endif //__EASY_EVECTOR_H__
