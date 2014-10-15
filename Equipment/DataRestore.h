#if !defined(AFX_DATARESTORE_H__917E4753_2C63_4A95_B3B2_42412EFAD660__INCLUDED_)
#define AFX_DATARESTORE_H__917E4753_2C63_4A95_B3B2_42412EFAD660__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataRestore.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataRestore dialog

class CDataRestore : public CDialog
{
// Construction
public:
	CString ExpandFileName(CString filename);
	CDataRestore(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataRestore)
	enum { IDD = IDD_DATARESTORE_DIALOG };
	CListCtrl	list;
	CEdit	datafile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataRestore)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	CString backfilename;
	// Generated message map functions
	//{{AFX_MSG(CDataRestore)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButton1();
	afx_msg void OnButtonrefresh();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATARESTORE_H__917E4753_2C63_4A95_B3B2_42412EFAD660__INCLUDED_)
