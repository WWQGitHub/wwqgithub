// ReduceKinds.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "ReduceKinds.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CReduceKinds dialog


CReduceKinds::CReduceKinds(CWnd* pParent /*=NULL*/)
	: CDialog(CReduceKinds::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}


void CReduceKinds::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReduceKinds)
	DDX_Control(pDX, IDC_EDIT1, kind);
	DDX_Control(pDX, IDC_LIST, list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReduceKinds, CDialog)
	//{{AFX_MSG_MAP(CReduceKinds)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_COMMAND(ID_BUTTONADD, OnButtonadd)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_COMMAND(ID_BUTTONUPDATE, OnButtonupdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReduceKinds message handlers

void CReduceKinds::OnOK() 
{

}

BOOL CReduceKinds::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon,true);
	//设置列表风格
	list.SetExtendedStyle(LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED |LVS_EX_FLATSB|LVS_SHOWSELALWAYS|LVS_EX_HEADERDRAGDROP);
	list.InsertColumn(1,_T("资产减少方式"));//向列表中添加列
	list.SetColumnWidth(0,300);//设置列宽度
	OnButtonrefresh();
	toolbar.Create(TBSTYLE_FLAT|CCS_TOP|WS_CHILD|WS_VISIBLE|WS_BORDER|CCS_ADJUSTABLE|TBSTYLE_WRAPABLE,CRect(0,0,0,0),this,IDR_TOOLBAR2);
	toolbar.SetBitmapSize(CSize(32,32));
	imagelist.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);
	for (int n =0;n<5;n++)
	{
		imagelist.Add(theApp.LoadIcon(n+IDI_ICON1));
	}
	
	toolbar.SetImageList(&imagelist);
	//toolbar.AddBitmap(5,IDR_TOOLBAR2);
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
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CReduceKinds::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message ==WM_KEYDOWN)
		if (pMsg->wParam ==13)
			pMsg->wParam = 9;	
	return CDialog::PreTranslateMessage(pMsg);
}

bool CReduceKinds::IsRepeated(CString str)
{
	CString sql;
	sql.Format(_T("select * from EquipmentManage.dbo.tb_decreasekinds where decreasekinds = '%s'"),str);
	theApp.datamanage->Record1->raw_Close();	
	theApp.datamanage->Record1->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if(theApp.datamanage->Record1->RecordCount>0)
		return true;
	return false;
}

void CReduceKinds::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentrow = list.GetSelectionMark();//得到当前行
	if (currentrow!=-1)
	{
		kind.SetWindowText(list.GetItemText(currentrow,0));
	}
	else
		kind.SetWindowText(_T(""));	
	*pResult = 0;
}

void CReduceKinds::OnButtonadd() 
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
				sql.Format(_T("insert into EquipmentManage.dbo.tb_decreasekinds values ('%s')"),str);
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
			OnButtonrefresh() ;
		}
		else
			MessageBox(_T("该类别已存在."),_T("提示"),64);
	}
	else
		AfxMessageBox(_T("基础信息不能为空."),0,0);		
}

void CReduceKinds::OnButtonclose() 
{
	EndDialog(0);		
}

void CReduceKinds::OnButtondelete() 
{
	if(MessageBox(_T("确实要删除当前记录吗?"),_T("提示"),MB_YESNO)==IDYES)
		if (theApp.datamanage->GetRecordset()->RecordCount>0)
		{
			int currentrow = list.GetSelectionMark();//得到当前行
			if (currentrow!=-1)
			{
				CString sql,olddata;
				olddata = list.GetItemText(currentrow,0);
				sql.Format(_T("delete EquipmentManage.dbo.tb_decreasekinds where decreasekinds = '%s'"),olddata);
				try
				{
					theApp.datamanage->ExecSQL(sql);
					MessageBox(_T("操作成功."),_T("提示"),64);
				}
				catch(_com_error e)
				{
					MessageBox(e.Description(),_T("提示"),64);			
				}
				OnButtonrefresh();
			}
			else
			{
				MessageBox(_T("请在表格中选择欲删除的数据."),_T("提示"),64);
			}
		}
			
		else
			MessageBox(_T("当前没有可删除的记录."),_T("提示"));	
}

void CReduceKinds::OnButtonrefresh() 
{
	kind.SetWindowText(_T(""));
	list.DeleteAllItems();
	theApp.datamanage->GetRecordset()->raw_Close();
	theApp.datamanage->GetRecordset()->Open("select decreasekinds as 资产减少方式 from EquipmentManage.dbo.tb_decreasekinds",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	if (theApp.datamanage->GetRecordset()->RecordCount >0)
	{
		while (! theApp.datamanage->GetRecordset()->ADOEOF)
		{
			CString str;
			_variant_t temp;
			temp =theApp.datamanage->GetRecordset()->GetCollect((long)0);
			str = temp.bstrVal;
			list.InsertItem(0,str,0);
			theApp.datamanage->GetRecordset()->MoveNext();
		}
	}	
}

void CReduceKinds::OnButtonupdate() 
{
	if (theApp.datamanage->GetRecordset()->RecordCount >0)
	{
		if(MessageBox(_T("确实要修改当前数据吗?"),_T("提示"),MB_YESNO)==IDYES )
		{
			CString str;
			kind.GetWindowText(str);			
			if (str.IsEmpty()) //判断能力基础信息是否为空
			{
				MessageBox(_T("基础信息不能为空"),_T("提示"),64);
			}
			else if (!IsRepeated(str))
			{
				int currentrow = list.GetSelectionMark();//得到当前行
				if (currentrow!=-1)
				{
					try
					{
						CString sql,olddata;
						olddata = list.GetItemText(currentrow,0);		
						sql.Format(_T("update EquipmentManage.dbo.tb_decreasekinds set decreasekinds = '%s' where decreasekinds = '%s'"),str,olddata);
						theApp.datamanage->ExecSQL(sql);
						this->MessageBox(_T("操作成功."),_T("提示"),64);
						kind.SetWindowText(_T(""));
						kind.SetFocus();					
					}
					catch(...)
					{
						MessageBox(_T("操作失败."),_T("提示"),64);				
					}
					OnButtonrefresh() ;
				}
				else
				{
					MessageBox(_T("当前没有可修改的数据."),_T("提示"),64);	
				}
			}
			else
				MessageBox(_T("该类别已经存在."),_T("提示"),64);
		}
	}
	else
		MessageBox(_T("当前没有可修改的数据."),_T("提示"),64);	
}
