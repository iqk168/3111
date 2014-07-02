// CtrlVisionAlignment.cpp: implementation of the CCtrlVisionAlignment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "CtrlVisionAlignment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtrlVisionAlignment::CCtrlVisionAlignment()
{
	dNCCLimit	= 0.8;
	dMaxAng		= 0.5;
	dMinAng		= 0;
	iObjectNum	= 1;	
}


CCtrlVisionAlignment::~CCtrlVisionAlignment()
{
	// Destory Object
	if( pVBCImageIsNULL(hHandle) )
		pDestroyVBCImage(hHandle);

	if( pVBCImageIsNULL(hHandleInspect) )
		pDestroyVBCImage(hHandleInspect);

	if( pVBCImageIsNULL(hHandleSubInspect) )
		pDestroyVBCImage(hHandleSubInspect);

	if( pVBCImageIsNULL(hHandleExtInspect) )
		pDestroyVBCImage(hHandleExtInspect);	

	if( pVBCImageIsNULL(hHandleMatchInspect) )
		pDestroyVBCImage(hHandleMatchInspect);
	
	if( pVBCImageIsNULL(hHandleMatchSubInspect) )
		pDestroyVBCImage(hHandleMatchSubInspect);

	TRACE("~CCtrlVisionAlignment\n");
}

void CCtrlVisionAlignment::UnInitLib()
{
	// Destory Object
	if( pVBCImageIsNULL(hHandle) )
		pDestroyVBCImage(hHandle);

	if( pVBCImageIsNULL(hHandleInspect) )
		pDestroyVBCImage(hHandleInspect);

	if( pVBCImageIsNULL(hHandleSubInspect) )
		pDestroyVBCImage(hHandleSubInspect);

	if( pVBCImageIsNULL(hHandleExtInspect) )
		pDestroyVBCImage(hHandleExtInspect);

	if( pVBCImageIsNULL(hHandleMatchPatten) )
		pDestroyVBCImage(hHandleMatchPatten);

	if( pVBCImageIsNULL(hHandleMatchInspect) )
		pDestroyVBCImage(hHandleMatchInspect);

	if( pVBCImageIsNULL(hHandleMatchSubInspect) )
		pDestroyVBCImage(hHandleMatchSubInspect);
}
void CCtrlVisionAlignment::InitLib()
{
	// VBCImage Process
	hInstLibraryVBCImageProcess = ::LoadLibrary(_T("VBCImageProcess.dll"));
    if(hInstLibraryVBCImage == NULL) 
    { 		
		CString cs = _T("");
		cs.Format("VBCImageProcess.dll Error.!");
		FreeLibrary(hInstLibraryVBCImageProcess);
		AfxMessageBox( cs );
	}

	// VBAlignment Process
	hInstLibraryVBCImageAlignment = ::LoadLibrary( _T("VBCImageProcess.dll")); 
    if(hInstLibraryVBCImageAlignment == NULL) 
    { 		
		CString cs = _T("");
		cs.Format("hInstLibraryVBCImageAlignment.dll Error.!");
		FreeLibrary(hInstLibraryVBCImageAlignment);
		AfxMessageBox( cs );
	}
	//

	// VBCImage
	hInstLibraryVBCImage = ::LoadLibrary(_T("VBCImage.dll"));
    if(hInstLibraryVBCImage == NULL) 
    { 		
		CString cs = _T("");
		cs.Format("VBCImage.dll Error.!");
		FreeLibrary(hInstLibraryVBCImage);
		AfxMessageBox( cs );
	}

	// Create 一個 Color Image
	pCreateVBCColorImage	= (HANDLE (__cdecl *)())GetProcAddress((HMODULE)hInstLibraryVBCImage, "CreateVBCColorImage");
	hHandle					= pCreateVBCColorImage(); // for Pattern
	hHandleInspect			= pCreateVBCColorImage(); // for Inspect
	hHandleSubInspect		= pCreateVBCColorImage(); // for Inspect
	hHandleExtInspect		= pCreateVBCColorImage(); // for Ext Inspect

	// Match
	hHandleMatchPatten		= pCreateVBCColorImage(); // for Match Pattern
	hHandleMatchInspect		= pCreateVBCColorImage(); // for Match Inspect
	hHandleMatchSubInspect	= pCreateVBCColorImage(); // for Match Inspect

	// Create 一個 NCC Tool
	pVBCreateNCCTool = (HANDLE (__cdecl*)())GetProcAddress((HMODULE)hInstLibraryVBCImageProcess, "VBCreateNCCTool");
	hHandleNCCTool = pVBCreateNCCTool();

	// Create 一個 Training NCC Tool
	pVBCreateNCCMatchColorModel = (BOOL (__cdecl*)(HANDLE, HANDLE))
					GetProcAddress((HMODULE)hInstLibraryVBCImageProcess, "VBCreateNCCMatchColorModel");

	// 刪除 NCC Tool
	pVBDestroyNCCModel = (void (__cdecl*)(HANDLE))
		GetProcAddress((HMODULE)hInstLibraryVBCImageAlignment, "VBDestroyNCCModel");

	// 載入要尋找的 Pattern
	pLoadCImage = (BOOL (__cdecl*)(HANDLE, char*))
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "LoadCImage");

	// 儲存檔案
	pSaveCImage = (BOOL (__cdecl*)(HANDLE, char*))
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "SaveCImage");

	// 取得圖像寬
	pVBGetWidth = (int (__cdecl*)(HANDLE))								
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "VBGetWidth");
	
	// 取得圖像高
	pVBGetHeight = (int (__cdecl*)(HANDLE))
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "VBGetHeight");

	// 刪除 Color Image 
	pDestroyVBCImage = (void (__cdecl*)(HANDLE))
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "DestroyVBCImage");

	// 確認是不是 NULL
	pVBCImageIsNULL = (BOOL (__cdecl *)(HANDLE))
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "VBCImageIsNULL");

	// 取得子畫面圖像
	pVBGetSubImage = (BOOL (__cdecl*)(HANDLE, HANDLE, tagVBmROI))
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "VBGetSubImage");

	// 開始 Match
	pVBFindNCCMatchColorModel = (int (__cdecl*)(HANDLE, HANDLE, double, double, double, bool, int) )
		GetProcAddress((HMODULE)hInstLibraryVBCImageAlignment, "VBFindNCCMatchColorModel");

	// 取回結果
	pVBGetNCCMatchResults = (BOOL (__cdecl*)(HANDLE, int, tagVBNCCFind* ) )
		GetProcAddress((HMODULE)hInstLibraryVBCImageProcess, "VBGetNCCMatchResults");
	
	// 取得Bitmap Address
	pGetBitmapAddress = (HBITMAP* (__cdecl*)(HANDLE) )
		GetProcAddress((HMODULE)hInstLibraryVBCImage, "VBGetBitmapAddress");

}

