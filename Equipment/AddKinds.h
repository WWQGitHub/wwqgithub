#if !defined(AFX_ADDKINDS_H__5AAFEBCC_6F46_4ACF_99EB_61A380C5589A__INCLUDED_)
#define AFX_ADDKINDS_H__5AAFEBCC_6F46_4ACF_99EB_61A380C5589A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddKinds.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddKinds dialog

class CAddKinds : public CDialog
{
// Construction
public:
	bool IsRepeated(CString str);
	CAddKinds(CWnd* pParent = NULL);   // standard constructor
	CFont font;
// Dialog Data
	//{{AFX_DATA(CAddKinds)
	enum { IDD = IDD_ADDKINDS_DIALOG };
	CEdit	kind;
	CListCtrl	list;
	CToolBarCtrl toolbar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddKinds)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon; 
	CImageList imagelist;
	// Generated message map functions
	//{{AFX_MSG(CAddKinds)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonadd();
	afx_msg void OnButtonclose();
	afx_msg void OnButtonupdate();
	afx_msg void OnButtondelete();
	afx_msg void OnButtonrefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDKINDS_H__5AAFEBCC_6F46_4ACF_99EB_61A380C5589A__INCLUDED_)
