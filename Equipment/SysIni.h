#if !defined(AFX_SYSINI_H__38A14B27_1E89_433D_A5D0_572EA5401E5B__INCLUDED_)
#define AFX_SYSINI_H__38A14B27_1E89_433D_A5D0_572EA5401E5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysIni.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysIni dialog

class CSysIni : public CDialog
{
// Construction
public:
	CString GetFileRoot(CString fullfilename,CString filename);
	bool FindFile(LPCTSTR FilePath,LPCTSTR FileName);
	CSysIni(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysIni)
	enum { IDD = IDD_SYSINI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysIni)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	// Generated message map functions
	//{{AFX_MSG(CSysIni)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonrefresh();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINI_H__38A14B27_1E89_433D_A5D0_572EA5401E5B__INCLUDED_)
