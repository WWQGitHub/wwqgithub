#if !defined(AFX_REDUCEKINDS_H__5396A7E7_C9EA_470E_9288_C4A4289C10E9__INCLUDED_)
#define AFX_REDUCEKINDS_H__5396A7E7_C9EA_470E_9288_C4A4289C10E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReduceKinds.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReduceKinds dialog

class CReduceKinds : public CDialog
{
// Construction
public:
	bool IsRepeated(CString str);
	CReduceKinds(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReduceKinds)
	enum { IDD = IDD_REDUCEKINDS_DIALOG };
	CEdit	kind;
	CListCtrl	list;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReduceKinds)
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
	//{{AFX_MSG(CReduceKinds)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonadd();
	afx_msg void OnButtonclose();
	afx_msg void OnButtondelete();
	afx_msg void OnButtonrefresh();
	afx_msg void OnButtonupdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDUCEKINDS_H__5396A7E7_C9EA_470E_9288_C4A4289C10E9__INCLUDED_)
