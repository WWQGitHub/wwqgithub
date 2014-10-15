#if !defined(AFX_ADDEQUIP_H__9B5654BB_EC11_480A_BED2_90F47B889681__INCLUDED_)
#define AFX_ADDEQUIP_H__9B5654BB_EC11_480A_BED2_90F47B889681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddEquip.h : header file
//
#include"NumberEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CAddEquip dialog

class CAddEquip : public CDialog
{
// Construction
public:
	bool IsNegative(); //判断是否出现负数
	bool InfoIsNull(); //判断信息是否为空
	void AddUseState();
	void ClearText(); //清空编辑框中的文本
	void AddEquipMode();
	void AddEquipKinds();
	CAddEquip(CWnd* pParent = NULL); // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddEquip)
	enum { IDD = IDD_ADDEQUIP_DIALOG };
	CNumberEdit	purevalue;
	CNumberEdit	prepurerate;
	CNumberEdit	prepurevalue;
	CNumberEdit	monthdeprevalue;
	CNumberEdit	monthdeprerate;
	CNumberEdit	addupdepre;
	CNumberEdit	sourcevalue;//入账原值
	CComboBox	usestate;//使用状况
	CEdit	spec; //规格
	CDateTimeCtrl	regdate;//入账日期
	CEdit	preusemonth;//预计使用月份
	CEdit	equipname;//资产名称
	CComboBox	equipkinds;//资产类别
	CEdit	depremonth; //已计提月份
	CComboBox	depremethod; //折旧方法
	CComboBox	addkinds; //增加方式
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddEquip)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolBarCtrl toolbar;
	CImageList imagelist;
	HICON m_hIcon; 
	// Generated message map functions
	//{{AFX_MSG(CAddEquip)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonclose();
	afx_msg void OnButtonrefresh();
	afx_msg void OnChangeSourcevalue();
	afx_msg void OnChangeAddupdepre();
	afx_msg void OnChangePrepurserate();
	afx_msg void OnChangePurevalue();
	afx_msg void OnChangePreusemonth();
	afx_msg void OnSelchangeDepremethod();
	afx_msg void OnChangeDepremonth();
	afx_msg void OnChangeMonthdeprerate();
	afx_msg void OnButtonadd();
	afx_msg void OnChangePrepurevalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDEQUIP_H__9B5654BB_EC11_480A_BED2_90F47B889681__INCLUDED_)
