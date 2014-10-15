// EquipmentDlg.h : header file
//
#include "CustomBar.h"
#if !defined(AFX_EQUIPMENTDLG_H__D82339BC_09E3_41B6_A94C_6161CE9A9BCB__INCLUDED_)
#define AFX_EQUIPMENTDLG_H__D82339BC_09E3_41B6_A94C_6161CE9A9BCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEquipmentDlg dialog

class CEquipmentDlg : public CDialog
{
// Construction
public:
	CStatusBarCtrl statusbar;
	HICON m_hIcon;
	CCustomBar toolbar;
	void DoToolMouseMove(int strid);

	void Close();
	CEquipmentDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEquipmentDlg)
	enum { IDD = IDD_EQUIPMENT_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquipmentDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL toolbarcreated;
	int panelcount;//×´Ì¬À¸Ãæ°åÊýÁ¿
	// Generated message map functions
	//{{AFX_MSG(CEquipmentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAddequip();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEquipkind();
	afx_msg void OnAddmode();
	afx_msg void OnRedusemode();
	afx_msg void OnUsestate();
	afx_msg void OnUpdateequip();
	afx_msg void OnDeleteequip();
	afx_msg void OnReduseequip();
	afx_msg void OnDepreciation();
	afx_msg void OnCanceldepre();
	afx_msg void OnCalculator();
	afx_msg void OnNote();
	afx_msg void OnMenuabout();
	afx_msg void OnBackup();
	afx_msg void OnMenusysini();
	afx_msg void OnRestore();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EQUIPMENTDLG_H__D82339BC_09E3_41B6_A94C_6161CE9A9BCB__INCLUDED_)
