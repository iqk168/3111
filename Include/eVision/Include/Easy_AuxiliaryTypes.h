// Easy_AuxiliaryTypes.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_AUXILIARYTYPES_H__
#define __EASY_AUXILIARYTYPES_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Auxiliary types

// List pointer
struct EListItem;

// Run descriptor
struct ERun
{
  // Pixel pointers
  void* pBeg, * pEnd;

  // Starting point coordinates
  INT16 n16X, n16Y;
};


#endif //__EASY_AUXILIARYTYPES_H__
