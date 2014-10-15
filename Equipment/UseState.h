#if !defined(AFX_USESTATE_H__5951FE75_1100_410C_9188_27E6D53B241D__INCLUDED_)
#define AFX_USESTATE_H__5951FE75_1100_410C_9188_27E6D53B241D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UseState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUseState dialog

class CUseState : public CDialog
{
// Construction
public:
	bool IsRepeated(CString str);
	CUseState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUseState)
	enum { IDD = IDD_USESTATE_DIALOG };
	CEdit	kind;
	CListCtrl	list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CToolBarCtrl toolbar;
	CImageList imagelist;
	// Generated message map functions
	//{{AFX_MSG(CUseState)
	virtual void OnOK();
	virtual void OnCancel();
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

#endif // !defined(AFX_USESTATE_H__5951FE75_1100_410C_9188_27E6D53B241D__INCLUDED_)
