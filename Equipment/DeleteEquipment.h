#if !defined(AFX_DELETEEQUIPMENT_H__6171050E_18DE_4276_8B9B_4C7EB89034C2__INCLUDED_)
#define AFX_DELETEEQUIPMENT_H__6171050E_18DE_4276_8B9B_4C7EB89034C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteEquipment.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteEquipment dialog

class CDeleteEquipment : public CDialog
{
// Construction
public:
	void AddEquipName();
	CDeleteEquipment(CWnd* pParent = NULL);   // standard constructor
	int currentrow;
// Dialog Data
	//{{AFX_DATA(CDeleteEquipment)
	enum { IDD = IDD_DELETEEQUIPMENT_DIALOG };
	CComboBox	querycondition;
	CButton	query;
	CListCtrl	list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteEquipment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	// Generated message map functions
	//{{AFX_MSG(CDeleteEquipment)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonrefresh();
	afx_msg void OnQuery();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtondelete();
	afx_msg void OnButtonclose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEEQUIPMENT_H__6171050E_18DE_4276_8B9B_4C7EB89034C2__INCLUDED_)
