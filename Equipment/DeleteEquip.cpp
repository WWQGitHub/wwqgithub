// DeleteEquip.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "DeleteEquip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteEquip dialog


CDeleteEquip::CDeleteEquip(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteEquip::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteEquip)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeleteEquip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteEquip)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteEquip, CDialog)
	//{{AFX_MSG_MAP(CDeleteEquip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteEquip message handlers

void CDeleteEquip::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDeleteEquip::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}
