#if !defined(AFX_DLGREPEATTRAYINOUTCTRL_H__1D553FF3_5040_44F0_8FDB_0BD855EBBDCF__INCLUDED_)
#define AFX_DLGREPEATTRAYINOUTCTRL_H__1D553FF3_5040_44F0_8FDB_0BD855EBBDCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRepeatTrayInOutCtrl.h : header file
//

#include "ColorPickerCB.h"
#include "ComboListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayInOutCtrl dialog

class CDlgRepeatTrayInOutCtrl : public CDialog
{
// Construction
public:
	CDlgRepeatTrayInOutCtrl(CWnd* pParent = NULL);   // standard constructor

	void InitTrayMode();
	void InitTestsetting();
	void InitValue();

	void CheckItemVerify(int iTray);
	bool SaveData(CString &csErr);

public:
	void Style();
	void ShowTitle();
	void ShowData();

	long m_iItemCount;

	//
	void SetCount(int Count);

public:
	tagRepeatInOutCtrl m_RepeatInOutCtrl;

public:
	// Temper Data
	CArray<tagRepeatTemperData, tagRepeatTemperData&> m_RepeatTrayTemperData;
	void LoadDataFromFile();
	void SaveDataToFile();
	void GetDataFromList();

public:
	void LockUI();	// if already build new lot, no change
	void ChangeUIForTrayFile();

public:
	void ResetItemValue();

// Dialog Data
	//{{AFX_DATA(CDlgRepeatTrayInOutCtrl)
	enum { IDD = IDD_DLG_REPEAT_TRAY_INOUT };
	CButton	m_cbxTemperatureConfim;
	CStatic	m_wndStaticTestSetting;
	CComboBox	m_cbxTestsetting;
	CStatic	m_wndCount;
	CComboListCtrl	m_List;
	CComboBox	m_cbxTray2;
	CComboBox	m_cbxTray1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRepeatTrayInOutCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRepeatTrayInOutCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLstDelete();
	afx_msg void OnLstInsert();
	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnSelchangeTTray1();
	afx_msg void OnSelchangeTTray2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPEATTRAYINOUTCTRL_H__1D553FF3_5040_44F0_8FDB_0BD855EBBDCF__INCLUDED_)
