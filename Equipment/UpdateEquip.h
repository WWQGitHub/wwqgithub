#if !defined(AFX_UPDATEEQUIP_H__28D7451F_356A_4A43_B084_C8F52555B10D__INCLUDED_)
#define AFX_UPDATEEQUIP_H__28D7451F_356A_4A43_B084_C8F52555B10D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpdateEquip.h : header file
//
#include "NumberEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CUpdateEquip dialog

class CUpdateEquip : public CDialog
{
// Construction
public:
	bool IsNegative();
	bool InfoIsNull();
	void AddQueryCondition();
	void AddUseState();
	void AddEquipMode();
	void AddEquipKinds();
	void ClearText();
	CUpdateEquip(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpdateEquip)
	enum { IDD = IDD_UPDATEEQUIP_DIALOG };
	CEdit	equipid;
	CComboBox	usestate;
	CEdit	spec;
	CNumberEdit	sourcevalue;
	CDateTimeCtrl	regdate;
	CComboBox	querycondition;
	CButton	query;
	CNumberEdit	purevalue;
	CEdit	preusemonth;
	CNumberEdit	prepurerate;
	CNumberEdit	prepurevalue;
	CNumberEdit	monthdeprevalue;
	CNumberEdit	monthdeprerate;
	CListCtrl	list;
	CEdit	equipname;
	CComboBox	equipkinds;
	CEdit	depremonth;
	CComboBox	depremethod;
	CNumberEdit	addupdepre;
	CComboBox	addkinds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateEquip)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_Hicon;
	CToolBarCtrl toolbar;
	CImageList imagelist;
	// Generated message map functions
	//{{AFX_MSG(CUpdateEquip)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonrefresh();
	afx_msg void OnQuery();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeSourcevalue();
	afx_msg void OnChangeAddupdepre();
	afx_msg void OnChangePurevalue();
	afx_msg void OnChangePrepurserate();
	afx_msg void OnChangePreusemonth();
	afx_msg void OnChangeDepremonth();
	afx_msg void OnSelchangeDepremethod();
	afx_msg void OnChangeMonthdeprerate();
	afx_msg void OnButtonupdate();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATEEQUIP_H__28D7451F_356A_4A43_B084_C8F52555B10D__INCLUDED_)
