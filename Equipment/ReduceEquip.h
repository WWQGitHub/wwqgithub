#if !defined(AFX_REDUCEEQUIP_H__2D551E4F_BA4C_451E_A2B4_D5F6BDFD9F3D__INCLUDED_)
#define AFX_REDUCEEQUIP_H__2D551E4F_BA4C_451E_A2B4_D5F6BDFD9F3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReduceEquip.h : header file
//
#include "NumberEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CReduceEquip dialog

class CReduceEquip : public CDialog
{
// Construction
public:
	bool InfoIsNull();
	void ClearText();
	void AddReduceMode();
	void AddEquipName();
	CReduceEquip(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReduceEquip)
	enum { IDD = IDD_REDUCEEQUIP_DIALOG };
	CEdit	equipid;
	CComboBox	reducemode;
	CComboBox	querycondition;
	CButton	query;
	CEdit	clearname;
	CNumberEdit	clearearning;
	CEdit	clearreason;
	CNumberEdit	clearcharge;
	CDateTimeCtrl	cleardate;
	CListCtrl	list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReduceEquip)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList imagelist;
	HICON m_hIcon ;
	CToolBarCtrl toolbar;
	// Generated message map functions
	//{{AFX_MSG(CReduceEquip)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonrefresh();
	afx_msg void OnQuery();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtondelete();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDUCEEQUIP_H__2D551E4F_BA4C_451E_A2B4_D5F6BDFD9F3D__INCLUDED_)
