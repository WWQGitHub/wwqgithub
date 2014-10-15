#if !defined(AFX_DELETEEQUIP_H__839E8228_70A6_4C64_9DCF_53EAE50704D3__INCLUDED_)
#define AFX_DELETEEQUIP_H__839E8228_70A6_4C64_9DCF_53EAE50704D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteEquip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteEquip dialog

class CDeleteEquip : public CDialog
{
// Construction
public:
	CDeleteEquip(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeleteEquip)
	enum { IDD = IDD_DELETEEQUIP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteEquip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteEquip)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEEQUIP_H__839E8228_70A6_4C64_9DCF_53EAE50704D3__INCLUDED_)
