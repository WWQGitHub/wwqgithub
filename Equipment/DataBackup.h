#if !defined(AFX_DATABACKUP_H__B15475FD_3366_4B48_94F0_6586F1B871BF__INCLUDED_)
#define AFX_DATABACKUP_H__B15475FD_3366_4B48_94F0_6586F1B871BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataBackup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataBackup dialog

class CDataBackup : public CDialog
{
// Construction
public:
	CDataBackup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataBackup)
	enum { IDD = IDD_DATABACKUP_DIALOG };
	CEdit	datafile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataBackup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	// Generated message map functions
	//{{AFX_MSG(CDataBackup)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonclose();
	afx_msg void OnButton1();
	afx_msg void OnButtonrefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABACKUP_H__B15475FD_3366_4B48_94F0_6586F1B871BF__INCLUDED_)
