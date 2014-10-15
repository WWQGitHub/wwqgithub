// Equipment.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Equipment.h"
#include "EquipmentDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEquipmentApp

BEGIN_MESSAGE_MAP(CEquipmentApp, CWinApp)
	//{{AFX_MSG_MAP(CEquipmentApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquipmentApp construction

CEquipmentApp::CEquipmentApp()
{

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEquipmentApp object

CEquipmentApp theApp;

// conn;

/////////////////////////////////////////////////////////////////////////////
// CEquipmentApp initialization

BOOL CEquipmentApp::InitInstance()
{
	AfxEnableControlContainer();
	if (!AfxOleInit())
	{
		AfxMessageBox(_T("OLE DLL初始化失败!"));
		return FALSE;
	}
	//AfxOleInit();
	datamanage = new CDataManage();
	datamanage->ConnectDatabase("Provider=SQLOLEDB.1;Server=WWQ-PC\\WWQ;Database=EquipmentManage;Uid=sa;Pwd=1021");
#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	//LoadIcon(IDI_TOOLBAR10);

	CEquipmentDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
//	datamanage->~CDataManage();
//	delete datamanage;
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CTime CEquipmentApp::StrToTime(CString str)
{
	int year,month,day,pos1,pos2;
	CString s_year,s_month,s_day;
	pos1 =str.Find(_T("-"),0);
	pos2 = str.Find(_T("-"),pos1+1);
	year = _ttoi(str.Left(4));//读取年
	month = _ttoi(str.Mid(pos1+1,2));//读取月
	day = _ttoi(str.Mid(pos2+1));//读取日
	return CTime(year,month,day,0,0,0);
}

int CEquipmentApp::ExitInstance() 
{
	
	return CWinApp::ExitInstance();
}
