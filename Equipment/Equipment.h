// Equipment.h : main header file for the EQUIPMENT application
//

#if !defined(AFX_EQUIPMENT_H__0CFB8610_33AE_49C4_9391_AA65F6C4B629__INCLUDED_)
#define AFX_EQUIPMENT_H__0CFB8610_33AE_49C4_9391_AA65F6C4B629__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "DataManage1.h"
		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEquipmentApp:
// See Equipment.cpp for the implementation of this class
//

class CEquipmentApp : public CWinApp
{
public:
	CTime StrToTime(CString str);//将字符串转换为日期
	CEquipmentApp();
	CDataManage * datamanage;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquipmentApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEquipmentApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EQUIPMENT_H__0CFB8610_33AE_49C4_9391_AA65F6C4B629__INCLUDED_)
