#if !defined(AFX_DEPRE_H__3A861B6B_FC90_40BD_9ADD_5D81CE2D0880__INCLUDED_)
#define AFX_DEPRE_H__3A861B6B_FC90_40BD_9ADD_5D81CE2D0880__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Depre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDepre dialog

class CDepre : public CDialog
{
// Construction
public:
	CDepre(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDepre)
	enum { IDD = IDD_DEPRE_DIALOG };
	CRichEditCtrl	memo;
	CEdit	currentdate;
	CDateTimeCtrl	date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDepre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	// Generated message map functions
	//{{AFX_MSG(CDepre)
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

#endif // !defined(AFX_DEPRE_H__3A861B6B_FC90_40BD_9ADD_5D81CE2D0880__INCLUDED_)
