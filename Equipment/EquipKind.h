//{{AFX_INCLUDES()
#include "datagrid.h"
#include "adodc.h"
//}}AFX_INCLUDES
#if !defined(AFX_EQUIPKIND_H__B768469D_D778_45DC_A55D_674F0F2EE4B3__INCLUDED_)
#define AFX_EQUIPKIND_H__B768469D_D778_45DC_A55D_674F0F2EE4B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EquipKind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEquipKind dialog

class CEquipKind : public CDialog
{
// Construction
public:
	CEquipKind(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEquipKind)
	enum { IDD = IDD_EQUIPKIND_DIALOG };
	CButton	RefreshButton;
	CButton	UpdateButton;
	CEdit	kind;
	CDataGrid	DBgrid1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquipKind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CToolBarCtrl toolbar;
	CImageList imagelist;
	// Generated message map functions
	//{{AFX_MSG(CEquipKind)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickDatagrid1();
	afx_msg void OnClickDatagrid();
	afx_msg void OnButtonadd();
	afx_msg void OnButtonrefresh();
	afx_msg void OnButtonupdate();
	afx_msg void OnButtondelete();
	afx_msg void OnButtonclose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	bool IsRepeated(CString str); //判断添加的信息是否重复
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EQUIPKIND_H__B768469D_D778_45DC_A55D_674F0F2EE4B3__INCLUDED_)
