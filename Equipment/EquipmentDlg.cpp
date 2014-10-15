// EquipmentDlg.cpp : implementation file
#include "stdafx.h"
#include "Equipment.h"
#include "EquipmentDlg.h"
#include "CustomBar.h"
#include "EquipKind.h"
#include "ReduceKinds.h"
#include "AddKinds.h"
#include "UseState.h"
#include "AddEquip.h"
#include "UpdateEquip.h"
#include "DeleteEquipment.h"
#include "ReduceEquip.h"
#include "Depre.h"
#include "UnDepre.h"
#include "DataBackup.h"
#include "DataRestore.h"
#include "SysIni.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
const int panelnum = 6;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern CEquipmentApp theApp;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon; 
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON6);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquipmentDlg dialog

CEquipmentDlg::CEquipmentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipmentDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE); //设置窗口图标
	toolbarcreated = false;	
}

void CEquipmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEquipmentDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEquipmentDlg, CDialog)
	//{{AFX_MSG_MAP(CEquipmentDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(IDS_ADDEQUIP, OnAddequip)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDS_EQUIPKIND, OnEquipkind)
	ON_COMMAND(IDS_ADDMODE, OnAddmode)
	ON_COMMAND(IDS_REDUSEMODE, OnRedusemode)
	ON_COMMAND(IDS_USESTATE, OnUsestate)
	ON_COMMAND(IDS_UPDATEEQUIP, OnUpdateequip)
	ON_COMMAND(IDS_DELETEEQUIP, OnDeleteequip)
	ON_COMMAND(IDS_REDUSEEQUIP, OnReduseequip)
	ON_COMMAND(IDS_DEPRECIATION, OnDepreciation)
	ON_COMMAND(IDS_CANCELDEPRE, OnCanceldepre)
	ON_COMMAND(ID_Calculator, OnCalculator)
	ON_COMMAND(ID_NOTE, OnNote)
	ON_COMMAND(ID_MENUABOUT, OnMenuabout)
	ON_COMMAND(IDS_BACKUP, OnBackup)
	ON_COMMAND(ID_MENUSYSINI, OnMenusysini)
	ON_COMMAND(IDS_Restore, OnRestore)
	ON_WM_CAPTURECHANGED()
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquipmentDlg message handlers

BOOL CEquipmentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	/******************************创建工具栏*********************************/
	toolbar.Create(TBSTYLE_FLAT|CCS_TOP|WS_CHILD|WS_VISIBLE|WS_BORDER|CCS_ADJUSTABLE|TBSTYLE_WRAPABLE,CRect(0,0,0,0),this,IDR_TOOLBAR1);
	//MouseMove = DoToolMouseMove;
	/******************************创建工具栏*********************************/
	/******************************创建状态栏*********************************/

	int panels[panelnum];//定义一个整型数组,记录状态栏每个面板的宽度
	CRect rect1;
	this->GetClientRect(&rect1);

	//this->GetClientRect()
	panels[0]= rect1.Width() / 9;
	panels[1]=rect1.Width() / 9*3;
	panels[2]=panels[1]+rect1.Width() / 9;
	panels[3]=panels[2]+rect1.Width() / 9*2;
	panels[4]=panels[3]+rect1.Width() / 9;
	panels[5]=2000;
	statusbar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM|SBARS_SIZEGRIP,rect1,this,ID_statusbar);
	statusbar.SetParts(panelnum,panels);//设置状态栏面板及宽度
	statusbar.SetText(_T("提示"),0,0);
	statusbar.SetText(_T("公司"),2,0);
	CString string;
	string.LoadString(IDS_COMPANY);
	statusbar.SetText(string,3,0);	
	statusbar.SetText(_T("系统时间"),4,0);
	/******************************创建状态栏**********************************/
	this->UpdateWindow();
	toolbarcreated = true;
	SetIcon(m_hIcon, TRUE);// Set big icon
	SetIcon(m_hIcon, FALSE);// Set small icon
	SetWindowText(_T("【资产设备管理系统】")); //设置窗口标题
	this->ShowWindow(SW_SHOWMAXIMIZED);
	this->SetTimer(12,1000,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEquipmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
	}
//	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEquipmentDlg::OnPaint() 
{
		CPaintDC dc(this);
		CDC MemDC;
		CBitmap bit;
		CRect rect;
		bit.LoadBitmap(IDB_BITMAP3);
		MemDC.CreateCompatibleDC(this->GetDC());
		MemDC.SelectObject(&bit);
		this->GetClientRect(&rect);
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,1022,611,SRCCOPY);   
		MemDC.DeleteDC();
		::DeleteObject(&bit);
		CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEquipmentDlg::OnQueryDragIcon()
{
	return 0;//(HCURSOR) m_hIcon;
}

void CEquipmentDlg::OnSize(UINT nType, int cx, int cy) 
{
	if (toolbarcreated)
	{
    	toolbar.AutoSize();
		CRect rect;
		this->GetClientRect(rect);
		statusbar.MoveWindow(rect,false);
		OnPaint();
	}
	CDialog::OnSize(nType, cx, cy);	
}

void CEquipmentDlg::OnAddequip() 
{
	CAddEquip addequip;
	addequip.DoModal();	
}

void CEquipmentDlg::OnClose() 
{
	if (MessageBox(_T("确实要退出系统吗?"),_T("提示"),MB_YESNO)!=IDNO)
		EndDialog(0);
}

void CEquipmentDlg::OnTimer(UINT nIDEvent) 
{
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%H:%M:%S");
	statusbar.SetText(s,5,0);
	CDialog::OnTimer(nIDEvent);
}

void CEquipmentDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
//	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CEquipmentDlg::Close()
{
//
}

BOOL CEquipmentDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN)&&(pMsg->wParam ==VK_ESCAPE))
	{
		PostMessage(WM_CLOSE);
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CEquipmentDlg::OnEquipkind() 
{
	CEquipKind EquipKind;
	try
	{
		EquipKind.DoModal();
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
	}
}

void CEquipmentDlg::OnAddmode() 
{
	CAddKinds addkinds;
	addkinds.DoModal();
}

void CEquipmentDlg::OnRedusemode() 
{
	CReduceKinds reducekinds;
	reducekinds.DoModal();
}

void CEquipmentDlg::OnUsestate() 
{
	CUseState usestate;
	try
	{
		usestate.DoModal();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}

void CEquipmentDlg::OnUpdateequip() 
{
	CUpdateEquip * updateEquip;
	updateEquip = new CUpdateEquip();
	try
	{
		updateEquip->DoModal();
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	delete(updateEquip);
	updateEquip = NULL;
}

void CEquipmentDlg::OnDeleteequip() 
{
	CDeleteEquipment * deleteequipment;
	deleteequipment = new CDeleteEquipment();
	deleteequipment->DoModal();
	delete(deleteequipment);
	deleteequipment = NULL;	
}

void CEquipmentDlg::OnReduseequip() 
{
	CReduceEquip * reduceequip;
	reduceequip= new CReduceEquip();
	reduceequip->DoModal();
	delete(reduceequip);
	reduceequip = NULL;
}

void CEquipmentDlg::OnDepreciation() 
{
	AfxInitRichEdit();
	CDepre * depre;
	depre = new CDepre();
	depre->DoModal();
	delete(depre);
	depre = NULL;
}

void CEquipmentDlg::OnCanceldepre() 
{
	AfxInitRichEdit();
	CUnDepre * undepre;
	undepre = new CUnDepre();
	undepre->DoModal();
	delete (undepre);
	undepre = NULL;
}


void CEquipmentDlg::OnCalculator() 
{
	ShellExecute(this->GetSafeHwnd(),_T("open") ,_T("calc.EXE"),NULL,NULL,SW_SHOWNORMAL);		
}

void CEquipmentDlg::OnNote() 
{
	ShellExecute(this->GetSafeHwnd(),_T("open") ,_T("NOTEPAD.EXE"),NULL,NULL,SW_MAXIMIZE);	
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon,true);

	return TRUE;  
}

void CEquipmentDlg::OnMenuabout() 
{
	CAboutDlg * about;
	about = new CAboutDlg();
	about->DoModal();
	delete (about);
	about = NULL;
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CEquipmentDlg::OnBackup() 
{
	CDataBackup * databackup;
	databackup= new CDataBackup();
	databackup->DoModal();
	delete(databackup);
	databackup = NULL;
}

void CEquipmentDlg::OnMenusysini() 
{
	CSysIni * sysini;
	sysini= new CSysIni();
	sysini->DoModal();
	delete(sysini);
	sysini = NULL;		
}

void CEquipmentDlg::OnRestore() 
{
	CDataRestore * restore;
	restore= new CDataRestore();
	restore->DoModal();
	delete(restore);
	restore = NULL;	
}

void CEquipmentDlg::OnButtonclose() 
{
	PostMessage(WM_CLOSE,0,0);	
}

void CEquipmentDlg::DoToolMouseMove(int strid)
{
	CString str;
	int temp;
	temp = strid / 4; //每3个工具栏按钮间有1个分隔条
	str.LoadString(strid+IDS_EQUIPKIND-temp);
	statusbar.SetText(str,1,0);
}
