// SysIni.cpp : implementation file
//
#include<atlconv.h>
#include "stdafx.h"
#include "Equipment.h"
#include "SysIni.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysIni dialog

extern CEquipmentApp theApp;
CSysIni::CSysIni(CWnd* pParent /*=NULL*/)
	: CDialog(CSysIni::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}

void CSysIni::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysIni)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysIni, CDialog)
	//{{AFX_MSG_MAP(CSysIni)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysIni message handlers

void CSysIni::OnOK() 
{
	// TODO: Add extra validation here
	

}

void CSysIni::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CSysIni::OnInitDialog() 
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
			str.LoadString(IDS_Sysini);
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

void CSysIni::OnButtonrefresh() 
{
	TCHAR  temp[MAX_PATH];
	GetModuleFileName(NULL,temp,MAX_PATH);//获得可执行文件的完整路径
	CString dir;
	dir.Format(_T("%s.exe"),theApp.m_pszAppName);
	dir = GetFileRoot(temp,dir);//去除文件名
	if (!FindFile(dir,_T("equipmentmanage.sql")))
	{
		MessageBox(_T("数据库脚本文件不存在."),_T("提示"),64);
		return;
	}
	if (MessageBox(_T("确实要进行系统初始化吗?"),_T("提示"),MB_YESNO|MB_ICONINFORMATION )==IDYES)
	{
		CString exestr;
		exestr.Format(_T("isqlw -S . -d equipmentmanage -E -i %s -o c:\\out.txt"),dir+_T("\\equipmentmanage.sql"));
		USES_CONVERSION;
		try
		{
			WinExec(T2A(exestr),SW_SHOW);
			MessageBox(_T("操作成功."),_T("提示"),64|MB_ICONINFORMATION);
		}
		catch(...)
		{
			MessageBox(_T("操作失败."),_T("提示"),64|MB_ICONINFORMATION);
		}
	}
}



bool CSysIni::FindFile(LPCTSTR FilePath,LPCTSTR FileName)
{
	WIN32_FIND_DATA* filestruct;
	HANDLE filehandle;
	CString temp;
	char arrays[200];
	sprintf_s(arrays,"%s\\*.*",FilePath);
	filestruct =new WIN32_FIND_DATA();
	filehandle = FindFirstFile((LPCWSTR)arrays,filestruct);
	temp = filestruct->cFileName;
	if (temp == FileName)
		return true;
	BOOL finded =false;
	finded= FindNextFile(filehandle,filestruct);
	while(finded ==TRUE)
	{
		temp = filestruct->cFileName;
		if (temp == FileName)
			return true;	
		finded= FindNextFile(filehandle,filestruct);
	}
	return false;
}

CString CSysIni::GetFileRoot(CString fullfilename,CString filename)
{
	int pos;
	pos = fullfilename.Find(filename,0);
	if (pos!=-1)
		return fullfilename.Left(pos-1);
	else
		return "";
}

void CSysIni::OnButtonclose() 
{
	EndDialog(0);	
}
