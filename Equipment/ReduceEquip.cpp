// ReduceEquip.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "ReduceEquip.h"
#include "NumberEdit.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CReduceEquip dialog


CReduceEquip::CReduceEquip(CWnd* pParent /*=NULL*/)
	: CDialog(CReduceEquip::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}


void CReduceEquip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReduceEquip)
	DDX_Control(pDX, IDC_ID, equipid);
	DDX_Control(pDX, IDC_REDUCEMODE, reducemode);
	DDX_Control(pDX, IDC_QUERYCONDITION, querycondition);
	DDX_Control(pDX, IDC_QUERY, query);
	DDX_Control(pDX, IDC_NAME, clearname);
	DDX_Control(pDX, IDC_CLERAERNING, clearearning);
	DDX_Control(pDX, IDC_CLEARREASON, clearreason);
	DDX_Control(pDX, IDC_CLEARECHARGE, clearcharge);
	DDX_Control(pDX, IDC_CLEARDATE, cleardate);
	DDX_Control(pDX, IDC_LIST1, list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReduceEquip, CDialog)
	//{{AFX_MSG_MAP(CReduceEquip)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReduceEquip message handlers

void CReduceEquip::OnOK() 
{
	// TODO: Add extra validation here
	

}

void CReduceEquip::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CReduceEquip::OnInitDialog() 
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
	TBBUTTON  buttons[4];
	for (int i =0; i<4;i++)
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
		if ((i ==2)|(i==3))
		{
			buttons[i].idCommand = ID_BUTTONADD+i+1;
			buttons[i].iBitmap = i+1;
			str.LoadString(ID_BUTTONADD+i+1);
		}
		else
		{
			buttons[i].idCommand = ID_BUTTONADD+i+1;
			buttons[i].iBitmap = i+1;
			str.LoadString(IDS_redusemange);//第一个按钮为分隔条
		}
		strlength = str.GetLength()+1;
		temp = str.GetBufferSetLength(strlength);
		temp[strlength]= '\0';
		temp[strlength-1]= '\0';
		buttons[i].iString = toolbar.AddStrings(temp);		
		str.ReleaseBuffer();
	}
	toolbar.AutoSize();
	toolbar.AddButtons(4,buttons);
	toolbar.ShowWindow(SW_SHOW);
	list.SetExtendedStyle(LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED |LVS_EX_FLATSB|LVS_SHOWSELALWAYS|LVS_EX_HEADERDRAGDROP);
	list.InsertColumn(100,_T("资产编号"));
	list.InsertColumn(100,_T("资产名称"));
	list.InsertColumn(100,_T("类别"));
	list.InsertColumn(100,_T("增加方式"));
	list.InsertColumn(100,_T("入账原值"));
	list.InsertColumn(100,_T("累计折旧"));
	for (int i =0 ;i<6;i++)
		list.SetColumnWidth(i,100);
	OnButtonrefresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReduceEquip::AddEquipName()
{
	_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select distinct name from EquipmentManage.dbo.tb_equipmentinfo where enabled = 0",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	querycondition.ResetContent();
	while (!temp->ADOEOF)
	{
		CString str;
		str = temp->GetFields()->GetItem("name")->Value.bstrVal;
		querycondition.AddString(str);
		temp->MoveNext();
	}
}

void CReduceEquip::AddReduceMode()
{
	_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select decreasekinds from EquipmentManage.dbo.tb_decreasekinds",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	reducemode.ResetContent();
	while (!temp->ADOEOF)
	{
		CString str;
		str = temp->GetFields()->GetItem("decreasekinds")->Value.bstrVal;
		reducemode.AddString(str);
		temp->MoveNext();
	}
}

void CReduceEquip::ClearText()
{
	CWnd * temp;
	temp = this;
	for (int i= 0;i<8;i++)
	{
		temp = this->GetNextDlgTabItem(temp);
		temp->SetWindowText(_T(""));
	}
	//设置日期
	CTime t=CTime::GetCurrentTime();
	cleardate.SetTime(&t);
	list.DeleteAllItems();
}

bool CReduceEquip::InfoIsNull()
{
	CWnd * temp;
	temp = this;
	for (int i= 2;i<8;i++)
	{
		temp = this->GetNextDlgTabItem(temp);
		CString str;
		temp->GetWindowText(str);
		if (str.IsEmpty())
		{
			return true;	
		}
	}
	return false;
}

void CReduceEquip::OnButtonrefresh() 
{
	AddEquipName();
	AddReduceMode();
	ClearText();
	
}

void CReduceEquip::OnQuery() 
{
	CString str;
	querycondition.GetWindowText(str);
	if(!str.IsEmpty())
	{
		_RecordsetPtr temp;
		list.DeleteAllItems();
		temp =theApp.datamanage->Record1; 
		temp->raw_Close();
		CString sql;
		sql.Format(_T("select * from EquipmentManage.dbo.tb_equipmentinfo where name = '%s' and enabled = 0 "),str);
		temp->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);		
		if (temp->RecordCount>0)
		{
			int row = 0;
			while (!temp->ADOEOF)
			{
				list.InsertItem(row,_T(""),0);
				for (int i= 0;i<6;i++)
				{
					CString str;
					_variant_t value;
					value = temp->GetFields()->GetItem((long)i)->Value;
					str = (TCHAR *)(_bstr_t)value;
					list.SetItemText(row,i,str);
				}
				row +=1;
				temp->MoveNext();
			}
		}
		else
			MessageBox(_T("没有发现符合条件的数据"),_T("提示"),64);		
	}
	else
		MessageBox(_T("请设置查询条件"),_T("提示"),64);	
}

void CReduceEquip::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int row = list.GetSelectionMark();
	CString str;
	if (row !=-1)
	{	
		str =list.GetItemText(row,0);
		equipid.SetWindowText(str);
		str =list.GetItemText(row,1);
		clearname.SetWindowText(str);
	}
	else
	{
		equipid.SetWindowText(_T(""));
		clearname.SetWindowText(_T(""));
	}
	*pResult = 0;
}

void CReduceEquip::OnButtondelete() 
{
	if (!InfoIsNull())
	{
		try
		{
			theApp.datamanage->GetConn()->BeginTrans();//开始一个事务
			CString sql,str;
			equipid.GetWindowText(str);
			sql.Format(_T("update EquipmentManage.dbo.tb_equipmentinfo set enabled = 1 where equipmentid = '%s'"),str);
			theApp.datamanage->Record1->raw_Close();
			theApp.datamanage->Record1->Open((_variant_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
			CString c_id,c_mode,c_earning, c_charge,c_reason,c_date;
			equipid.GetWindowText(c_id);
			reducemode.GetWindowText(c_mode);
			clearearning.GetWindowText(c_earning);
			clearcharge.GetWindowText(c_charge);
			clearreason.GetWindowText(c_reason);
			cleardate.GetWindowText(c_date);
			float earning,charge;
			earning = _ttof(c_earning);
			charge = _ttof(c_charge);
			sql.Format(_T("insert into EquipmentManage.dbo.tb_equipmentdecrease values ('%s','%s',%f,%f,'%s','%s')"),c_id,c_mode,earning,charge,c_reason,c_date);
			theApp.datamanage->Record1->raw_Close();
			theApp.datamanage->Record1->Open((_variant_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);			
					
			theApp.datamanage->GetConn()->CommitTrans();//提交事务
			MessageBox(_T("操作成功."),_T("提示"),64);
		}
		catch(_com_error)
		{
			theApp.datamanage->GetConn()->RollbackTrans();//出现异常,回滚事务
			MessageBox(_T("系统出错."),_T("提示"),64);
		}
		OnButtonrefresh();
	}
	else
	{
		MessageBox(_T("基础信息不能为空."),_T("提示"),64);
	}
}

BOOL CReduceEquip::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message ==WM_KEYDOWN)
		if (pMsg->wParam ==13)
			pMsg->wParam = 9;		
	return CDialog::PreTranslateMessage(pMsg);
}

void CReduceEquip::OnButtonclose() 
{
	EndDialog(0);	
}
