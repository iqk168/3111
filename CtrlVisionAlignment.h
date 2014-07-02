// CtrlVisionAlignment.h: interface for the CCtrlVisionAlignment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLVISIONALIGNMENT_H__951D6567_4A2D_4BF7_A492_1E1B4AAF2535__INCLUDED_)
#define AFX_CTRLVISIONALIGNMENT_H__951D6567_4A2D_4BF7_A492_1E1B4AAF2535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCtrlVisionAlignment  
{
public:
	CCtrlVisionAlignment();
	virtual ~CCtrlVisionAlignment();
public:

typedef struct tagVBmROI{
	long Top;
	long bottom;
	long Left;
	long Right;
} tagVBmROI;

//
typedef struct tagVBNCCFind{        
	unsigned int Width;
	unsigned int Height;
    double CX;
    double CY;
    double Angle;
	double Score;
} tagVBNCCFind;

public:

	//HINSTANCE
	HINSTANCE hInstLibraryVBCImageProcess;		// VBCImageProcess
	HINSTANCE hInstLibraryVBCImage;				// VBCImage
	HINSTANCE hInstLibraryVBCImageAlignment;	// VBCAlignment

	HANDLE hHandle;								// ptr, for Image (Pattern)
	HANDLE hHandleInspect;						// ptr, for Inspect Image
	HANDLE hHandleNCCTool;						// ptr, for NCC Tool
	HANDLE hHandleSubInspect;					// ptr, for Inspect Image

	//
	HANDLE hHandleMatchPatten;					// ptr, for Image (Sub Pattern)
	HANDLE hHandleMatchInspect;					// ptr, for Inspect Image
	HANDLE hHandleMatchSubInspect;				// ptr, for Inspect (Sub Inspect)

	//
	HANDLE hHandleExtInspect;					// ptr, for ext image use.

	//
	tagVBmROI VBROI;

	//
	tagVBmROI PatternVBROI;
public:

	tagVBNCCFind NCCFind;
//
	// CImage
	HANDLE (__cdecl *pCreateVBCColorImage)();
	HANDLE (__cdecl *pCreateVBCGrayImage)();
	HANDLE (__cdecl *pCreateVBCHSIImage)();
	HANDLE (__cdecl *pCreateVBCCIELabImage)();

	// NCTool
	HANDLE (__cdecl *pVBCreateNCCTool)();

	// Get
	int (__cdecl *pVBGetWidth)(HANDLE);
	int (__cdecl *pVBGetHeight)(HANDLE);

	// Destory	
	void (__cdecl *pDestroyVBCImage)(HANDLE);
	void (__cdecl *pVBDestroyNCCModel)(HANDLE);

	// IsNULL
	BOOL (__cdecl *pVBCImageIsNULL)(HANDLE);
	
	// Save SubImage
	BOOL (__cdecl *pVBGetSubImage)(HANDLE, HANDLE, tagVBmROI );

	// Excute
	BOOL (__cdecl *pVBCreateNCCMatchColorModel)(HANDLE, HANDLE);				  
	double dNCCLimit;
	double dMaxAng;
	double dMinAng;
	int iObjectNum;
	int (__cdecl *pVBFindNCCMatchColorModel)(HANDLE, HANDLE, double, double, double, bool, int);					

	BOOL   (__cdecl *pVBGetNCCMatchResults)(HANDLE, int, tagVBNCCFind* );

	// Load / Save
	BOOL   (__cdecl *pLoadCImage)(HANDLE, char*);
	BOOL   (__cdecl *pSaveCImage)(HANDLE, char*);
	HBITMAP* (__cdecl *pGetBitmapAddress)(HANDLE);

public:

	void InitLib();
	void UnInitLib();

};

#endif // !defined(AFX_CTRLVISIONALIGNMENT_H__951D6567_4A2D_4BF7_A492_1E1B4AAF2535__INCLUDED_)
