// DataRestore.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "DataRestore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataRestore dialog

extern CEquipmentApp theApp;
CDataRestore::CDataRestore(CWnd* pParent /*=NULL*/)
	: CDialog(CDataRestore::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
	backfilename = "";
}

void CDataRestore::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataRestore)
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_EDIT1, datafile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataRestore, CDialog)
	//{{AFX_MSG_MAP(CDataRestore)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataRestore message handlers

void CDataRestore::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDataRestore::OnOK() 
{

}

BOOL CDataRestore::OnInitDialog() 
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
			str.LoadString(IDS_Restore);
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
	list.SetExtendedStyle(LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED |LVS_EX_FLATSB|LVS_SHOWSELALWAYS|LVS_EX_HEADERDRAGDROP);
	list.InsertColumn(100,_T("位置"));
	list.InsertColumn(100,_T("备份时间"));
	list.SetColumnWidth(0,100);
	list.SetColumnWidth(1,245);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataRestore::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CDataRestore::OnButton1() 
{
	CFileDialog* filedialog;
	filedialog = new CFileDialog(true,_T("bak"));
	list.DeleteAllItems();
	if (filedialog->DoModal()==IDOK )
	{
		CString str,sql;
		str = filedialog->GetPathName();
		datafile.SetWindowText(str);
		//str = ExpandFileName(str);
		backfilename = str;
		sql.Format(_T("restore headeronly from disk = '%s'"),str);
		theApp.datamanage->Record1->raw_Close();
		try
		{
			theApp.datamanage->Record1->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
		}
		catch(...)
		{
			MessageBox(_T("指定的文件不是合法的备份文件."),_T("提示"),64);
			datafile.SetWindowText(_T(""));
			backfilename = _T("");
			return;
		}
		int row = 0;
		while(! theApp.datamanage->Record1->ADOEOF)
		{
			list.InsertItem(row,_T(""));
			str = (TCHAR *)(_bstr_t)theApp.datamanage->Record1->GetFields()->GetItem("Position")->Value;
			list.SetItemText(row,0,str);
			str = (TCHAR *)(_bstr_t)theApp.datamanage->Record1->GetFields()->GetItem("backupfinishdate")->Value;
			list.SetItemText(row,1,str);
			row += 1;
			theApp.datamanage->Record1->MoveNext();
		}
		
	}
	delete (filedialog);
	
}

CString CDataRestore::ExpandFileName(CString filename)
{
	int pos;
	pos = filename.Find(_T("."),0);
	if (pos != -1)
	{
		return filename.Left(pos);
	}
	return filename;

}

void CDataRestore::OnButtonrefresh() 
{
	int row = list.GetSelectionMark();
	if (row != -1)
	{
		CString temp,sql;
		temp = (TCHAR*)(_bstr_t)theApp.datamanage->GetConn()->ConnectionString;
		try
		{
			theApp.datamanage->GetConn()->Close();
			theApp.datamanage->ConnectDatabase("Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initial Catalog=master;Data Source=.");
			sql = "select spid from master..sysprocesses where dbid=db_id('EquipmentManage')";			
			_RecordsetPtr recordset;
			recordset = theApp.datamanage->Record1;
			recordset->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
			while (!recordset->ADOEOF)
			{				
				temp = (TCHAR *)(_bstr_t)recordset->GetFields()->GetItem("spid")->Value;
				sql.Format(_T("kill %i"),_ttoi(temp));
				theApp.datamanage->ExecSQL(sql);
				recordset->MoveNext();
			}
			sql.Format(_T("  restore database equipmentmanage from disk ='%s' with file = %i"),backfilename,_ttoi(list.GetItemText(row,0)));				
			theApp.datamanage->ExecSQL(sql);
			MessageBox(_T("还原成功."),_T("提示"),64);
		}
		catch(...)
		{
			MessageBox(_T("还原失败."),_T("提示"),64);
		}
		theApp.datamanage->GetConn()->Close();
		theApp.datamanage->ConnectDatabase("Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initial Catalog=Equipmentmanage;Data Source=.");
	}
	else
	{
		MessageBox(_T("请在列表中选择备份集."),_T("提示"),64);
	}
}

void CDataRestore::OnButtonclose() 
{
	EndDialog(0);	
}
