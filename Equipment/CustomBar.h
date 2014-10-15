#if !defined(AFX_CUSTOMBAR_H__C6107326_7F30_4CAE_8E03_F9F63EC0A9EF__INCLUDED_)
#define AFX_CUSTOMBAR_H__C6107326_7F30_4CAE_8E03_F9F63EC0A9EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomBar.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CCustomBar window
class CCustomBar : public CToolBarCtrl
{
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomBar)
	public:
	virtual BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DoMouseLeave();
	void DoMouseMove(int strid);
	CCustomBar();
	virtual ~CCustomBar();
	// Generated message map functions
protected:
	int m_ButtonCount; //记录工具栏中的按钮数
	CImageList* imagelist;
	//{{AFX_MSG(CCustomBar)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMBAR_H__C6107326_7F30_4CAE_8E03_F9F63EC0A9EF__INCLUDED_)
