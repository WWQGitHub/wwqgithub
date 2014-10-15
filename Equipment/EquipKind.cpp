// EquipKind.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "EquipKind.h"
#include "Equipment.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CEquipKind dialog


CEquipKind::CEquipKind(CWnd* pParent /*=NULL*/)
	: CDialog(CEquipKind::IDD, pParent)
{	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}

bool CEquipKind::IsRepeated(CString str)
{
	CString sql;
	sql.Format(_T("select * from EquipmentManage.dbo.tb_kinds where kinds = '%s'"),str);
	theApp.datamanage->Record1->raw_Close();	
	theApp.datamanage->Record1->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if(theApp.datamanage->Record1->RecordCount>0)
		return true;
	return false;
}

void CEquipKind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEquipKind)
	DDX_Control(pDX, IDC_EDIT1, kind);
	DDX_Control(pDX, IDC_DATAGRID, DBgrid1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEquipKind, CDialog)
	//{{AFX_MSG_MAP(CEquipKind)
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	ON_COMMAND(ID_BUTTONADD, OnButtonadd)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_COMMAND(ID_BUTTONUPDATE, OnButtonupdate)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquipKind message handlers

void CEquipKind::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CEquipKind::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	OnButtonrefresh(); //调用刷新按钮的单击事件	
	// TODO: Add your message handler code here
}


BEGIN_EVENTSINK_MAP(CEquipKind, CDialog)
    //{{AFX_EVENTSINK_MAP(CEquipKind)
	ON_EVENT(CEquipKind, IDC_DATAGRID, -600 /* Click */, OnClickDatagrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CEquipKind::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//PostMessage(WM_SETICON,ICON_SMALL,(LPARAM)theApp.LoadIcon(IDR_MAINTITLE));
	SetIcon(theApp.LoadIcon(IDR_MAINTITLE), TRUE);	//设置窗口图标
	toolbar.Create(TBSTYLE_FLAT|CCS_TOP|WS_CHILD|WS_VISIBLE|WS_BORDER|CCS_ADJUSTABLE|TBSTYLE_WRAPABLE,CRect(0,0,0,0),this,IDR_TOOLBAR2);
	toolbar.SetBitmapSize(CSize(32,32));
	imagelist.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);
	for (int n =0;n<5;n++)
	{
		imagelist.Add(theApp.LoadIcon(n+IDI_ICON1));
	}	
	toolbar.SetImageList(&imagelist);
	TBBUTTON  buttons[6];
	for (int i =0; i<6;i++)
	{
		CString str;
		int strlength;
		TCHAR *temp;
		str.LoadString(ID_BUTTONADD+i-1);//第一个按钮为分隔条
		strlength = str.GetLength()+1;
		temp = str.GetBufferSetLength(strlength);
		temp[strlength]= '\0';
		temp[strlength-1]= '\0';
		if (i<1)
			buttons[i].fsStyle =TBSTYLE_SEP;
		else
		{
			buttons[i].fsStyle =TBSTYLE_BUTTON;
		}
		buttons[i].fsState =TBSTATE_ENABLED;
		buttons[i].dwData =0;
		buttons[i].idCommand = ID_BUTTONADD+i-1;		
		buttons[i].iString = toolbar.AddStrings(temp);
		buttons[i].iBitmap = i-1;
		str.ReleaseBuffer();
	}	
	toolbar.AutoSize();
	toolbar.AddButtons(6,buttons);
	toolbar.ShowWindow(SW_SHOW);
	return TRUE;   
}

void CEquipKind::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// Do not call CDialog::OnPaint() for painting messages
}

void CEquipKind::OnClickDatagrid() 
{
	CString str;
	_variant_t temp;
	if ((!theApp.datamanage->GetRecordset()->ADOEOF)&&(!theApp.datamanage->GetRecordset()->BOF))
	{
		temp = theApp.datamanage->GetRecordset()->GetFields()->GetItem((long)0)->Value;
		str = temp.bstrVal;
		kind.SetWindowText(str);
	}	
}

void CEquipKind::OnButtonadd() 
{
	CString str;
	kind.GetWindowText(str);
	if (!str.IsEmpty())
	{
		if (!IsRepeated(str))
		{
			try
			{
				CString sql;
				sql.Format(_T("insert into EquipmentManage.dbo.tb_kinds values ('%s')"),str);
				theApp.datamanage->ExecSQL(sql);
				this->MessageBox(_T("操作成功."),_T("提示"),64);
				kind.SetWindowText(_T(""));
				kind.SetFocus();
			}
			catch(...)
			{
				this->MessageBox(_T("操作失败."),_T("提示"),64);
				kind.SetFocus();
				kind.SetSel(0);
			}
			OnButtonrefresh();
		}
		else
			MessageBox(_T("该类别已存在."),_T("提示"),64);
	}
	else
		AfxMessageBox(_T("基础信息不能为空."),0,0);	
}

void CEquipKind::OnButtonrefresh() 
{
	kind.SetWindowText(_T(""));	//清空编辑框文本
	DBgrid1.SetRefDataSource(NULL);
	theApp.datamanage->GetRecordset()->raw_Close();	
	theApp.datamanage->GetRecordset()->Open("select kinds as 资产类别 from EquipmentManage.dbo.tb_kinds",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);	
	if(theApp.datamanage->GetRecordset()->RecordCount>0)
		DBgrid1.SetRefDataSource(theApp.datamanage->GetRecordset()->DataSource);
}

void CEquipKind::OnButtonupdate() 
{
	if (theApp.datamanage->GetRecordset()->RecordCount >0)
	{
		if(MessageBox(_T("确实要修改当前数据吗?"),_T("提示"),MB_YESNO)==IDYES )
		{
			CString str;
			kind.GetWindowText(str);
			
			if (str.IsEmpty()) //判断基础信息是否为空
			{
				MessageBox(_T("基础信息不能为空"),_T("提示"),64);
			}
			else if (!IsRepeated(str))
			{
				try
				{
					_bstr_t temp= str;		
					theApp.datamanage->GetRecordset()->GetFields()->GetItem((long)0)->Value =temp;
					theApp.datamanage->GetRecordset()->Update();
					this->MessageBox(_T("操作成功."),_T("提示"),64);
					kind.SetWindowText(_T(""));
					kind.SetFocus();					
				}
				catch(...)
				{
					MessageBox(_T("操作失败."),_T("提示"),64);				
				}
				OnButtonrefresh();
			}
			else
				MessageBox(_T("该类别已经存在."),_T("提示"),64);
		}
	}
	else
		MessageBox(_T("当前没有可修改的数据."),_T("提示"),64);	
}

void CEquipKind::OnButtondelete() 
{
	if(MessageBox(_T("确实要删除当前记录吗?"),_T("提示"),MB_YESNO)==IDYES)
		if (theApp.datamanage->GetRecordset()->RecordCount>0)
		{
			CString i ;
			kind.GetWindowText(i);
			if (! i.IsEmpty() )
			{
				CString sql;
				theApp.datamanage->GetRecordset()->raw_Close();
				sql.Format(_T("delete EquipmentManage.dbo.tb_kinds where kinds = '%s'"),i);
				theApp.datamanage->GetConn()->Execute((_bstr_t)sql,NULL,0);
				OnButtonrefresh();
			}
			else
				MessageBox(_T("请在编辑框中输入信息或在表格中选择信息"),_T("提示"));	
		}
		else
			MessageBox(_T("当前没有可删除的记录.","提示"));		
}

void CEquipKind::OnButtonclose() 
{
	EndDialog(0);	
}
