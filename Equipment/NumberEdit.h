#if !defined(AFX_NUMBEREDIT_H__4B3763FF_A9C2_42CC_A7BD_0DFCC7F7B9F6__INCLUDED_)
#define AFX_NUMBEREDIT_H__4B3763FF_A9C2_42CC_A7BD_0DFCC7F7B9F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumberEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit window

class CNumberEdit : public CEdit
{
// Construction
public:
	CNumberEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNumberEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumberEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMBEREDIT_H__4B3763FF_A9C2_42CC_A7BD_0DFCC7F7B9F6__INCLUDED_)
