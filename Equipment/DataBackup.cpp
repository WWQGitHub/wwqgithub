// DataBackup.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "DataBackup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CDataBackup dialog


CDataBackup::CDataBackup(CWnd* pParent /*=NULL*/)
	: CDialog(CDataBackup::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}


void CDataBackup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataBackup)
	DDX_Control(pDX, IDC_EDIT1, datafile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataBackup, CDialog)
	//{{AFX_MSG_MAP(CDataBackup)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataBackup message handlers

void CDataBackup::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDataBackup::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL CDataBackup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon,true);
	toolbar.Create(TBSTYLE_FLAT|CCS_TOP|WS_CHILD|WS_VISIBLE|WS_BORDER|CCS_ADJUSTABLE|TBSTYLE_WRAPABLE,CRect(0,0,0,0),this,IDR_TOOLBAR2);
	toolbar.SetBitmapSize(CSize(32,32));
	imagelist.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);
	for (int n =0;n<5;n++)
	{
		imagelist.Add(theApp.LoadIcon(n+IDI_ICON1));
	}	
	toolbar.SetImageList(&imagelist);
	TBBUTTON  buttons[3];
	for (int i =0; i<3;i++)
	{
		CString str;
		int strlength;
		TCHAR *temp;
		if (i<1)
			buttons[i].fsStyle =TBSTYLE_SEP;
		else
		{
			buttons[i].fsStyle =TBSTYLE_BUTTON;
		}
		buttons[i].fsState =TBSTATE_ENABLED;
		buttons[i].dwData =0;
		if (i == 1) 
		{
			buttons[i].idCommand = ID_BUTTONADD+3; //对应于刷新
			buttons[i].iBitmap = 3;
			str.LoadString(IDS_BACKUP);
		}
		else
		{
			buttons[i].idCommand = ID_BUTTONADD+4;//退出
			buttons[i].iBitmap = 4;
			str.LoadString(ID_BUTTONADD+4);
		}				
		strlength = str.GetLength()+1;
		temp = str.GetBufferSetLength(strlength);
		temp[strlength]= '\0';
		temp[strlength-1]= '\0';
		buttons[i].iString = toolbar.AddStrings(temp);		
		str.ReleaseBuffer();
	}
	toolbar.AutoSize();
	toolbar.AddButtons(3,buttons);
	toolbar.ShowWindow(SW_SHOW);
	return TRUE;  
}

void CDataBackup::OnButtonclose() 
{
	EndDialog(0);	
}

void CDataBackup::OnButton1() 
{
	CFileDialog* filedialog;
	filedialog = new CFileDialog(true,_T("bak"));
	if (filedialog->DoModal()==IDOK )
	{
		CString str;
		str = filedialog->GetPathName();
		datafile.SetWindowText(str);
	}
	delete (filedialog);
	//filedialog.Create();
//	
}

void CDataBackup::OnButtonrefresh() 
{
	CString str;
	datafile.GetWindowText(str);
	if (!str.IsEmpty())
	{
		try
		{
			CString sql;
			sql.Format(_T("backup database EquipmentManage to disk = '%s'"),str);
			theApp.datamanage->ExecSQL(sql);
		}
		catch(_com_error e)
		{
			MessageBox(_T("备份失败.\r\n") + e.Description(), _T("提示"),64);
			return;
		}
		MessageBox(_T("备份成功."), _T("提示"), 64);
	}
	else
	{
		MessageBox(_T("请指定备份文件."),_T("提示"),64);
	}
}
