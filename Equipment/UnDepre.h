#if !defined(AFX_UNDEPRE_H__441E5758_BDA7_4742_9A86_F163441F284A__INCLUDED_)
#define AFX_UNDEPRE_H__441E5758_BDA7_4742_9A86_F163441F284A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnDepre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnDepre dialog

class CUnDepre : public CDialog
{
// Construction
public:
	CUnDepre(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUnDepre)
	enum { IDD = IDD_UNDEPRE_DIALOG };
	CRichEditCtrl	memo;
	CDateTimeCtrl	currentdate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnDepre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	// Generated message map functions
	//{{AFX_MSG(CUnDepre)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtondelete();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNDEPRE_H__441E5758_BDA7_4742_9A86_F163441F284A__INCLUDED_)
