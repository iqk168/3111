// Easy_Debug.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_DEBUG_H__
#define __EASY_DEBUG_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Global stream operators for debugging info
//
E_DLL0 std::ostream& E_DLL1  operator<< (  std::ostream& strm, const EGenericROI& objref);
//template<typename T> E_DLL0 std::ostream& E_DLL1       operator<< (  std::ostream& strm, const EVectorTemplate<T>& obj);

E_DLL0 std::ostream& E_DLL1  operator<< ( std::ostream& strm, const ERun& run);
E_DLL0 std::ostream& E_DLL1  operator<< ( std::ostream& strm, const EC24& obj);
E_DLL0 std::ostream& E_DLL1  operator<< ( std::ostream& strm, const EColor& obj);

#endif //__EASY_DEBUG_H__
