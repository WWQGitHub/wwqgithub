// UpdateEquip.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "UpdateEquip.h"
#include "NumberEdit.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CUpdateEquip dialog


CUpdateEquip::CUpdateEquip(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateEquip::IDD, pParent)
{
	m_Hicon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
	//{{AFX_DATA_INIT(CUpdateEquip)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUpdateEquip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateEquip)
	DDX_Control(pDX, IDC_EquipID, equipid);
	DDX_Control(pDX, IDC_USESTATE, usestate);
	DDX_Control(pDX, IDC_SPEC, spec);
	DDX_Control(pDX, IDC_SOURCEVALUE, sourcevalue);
	DDX_Control(pDX, IDC_REGDATE, regdate);
	DDX_Control(pDX, IDC_QUERYCONDITION, querycondition);
	DDX_Control(pDX, IDC_QUERY, query);
	DDX_Control(pDX, IDC_PUREVALUE, purevalue);
	DDX_Control(pDX, IDC_PREUSEMONTH, preusemonth);
	DDX_Control(pDX, IDC_PREPURSERATE, prepurerate);
	DDX_Control(pDX, IDC_PREPUREVALUE, prepurevalue);
	DDX_Control(pDX, IDC_MONTHDEPREVALUE, monthdeprevalue);
	DDX_Control(pDX, IDC_MONTHDEPRERATE, monthdeprerate);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_EQUIPNAME, equipname);
	DDX_Control(pDX, IDC_EQUIPKINDS, equipkinds);
	DDX_Control(pDX, IDC_DEPREMONTH, depremonth);
	DDX_Control(pDX, IDC_DEPREMETHOD, depremethod);
	DDX_Control(pDX, IDC_ADDUPDEPRE, addupdepre);
	DDX_Control(pDX, IDC_ADDKINDS, addkinds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateEquip, CDialog)
	//{{AFX_MSG_MAP(CUpdateEquip)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_CHANGE(IDC_SOURCEVALUE, OnChangeSourcevalue)
	ON_EN_CHANGE(IDC_ADDUPDEPRE, OnChangeAddupdepre)
	ON_EN_CHANGE(IDC_PUREVALUE, OnChangePurevalue)
	ON_EN_CHANGE(IDC_PREPURSERATE, OnChangePrepurserate)
	ON_EN_CHANGE(IDC_PREUSEMONTH, OnChangePreusemonth)
	ON_EN_CHANGE(IDC_DEPREMONTH, OnChangeDepremonth)
	ON_CBN_SELCHANGE(IDC_DEPREMETHOD, OnSelchangeDepremethod)
	ON_EN_CHANGE(IDC_MONTHDEPRERATE, OnChangeMonthdeprerate)
	ON_COMMAND(ID_BUTTONUPDATE, OnButtonupdate)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateEquip message handlers

void CUpdateEquip::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CUpdateEquip::OnOK() 
{

}

BOOL CUpdateEquip::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_Hicon,true);
	/**************************设计工具栏********************************/
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
			buttons[i].idCommand = ID_BUTTONADD+i;
			buttons[i].iBitmap = i;
			str.LoadString(ID_BUTTONADD+i);
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
	/*****************************初始化列表****************************/
	list.SetExtendedStyle(LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED |LVS_EX_FLATSB|LVS_SHOWSELALWAYS|LVS_EX_HEADERDRAGDROP);
	list.InsertColumn(100,_T("资产编号"));
	list.InsertColumn(100,_T("资产名称"));
	list.InsertColumn(100,_T("资产类别"));
	list.InsertColumn(100,_T("增加方式"));
	list.InsertColumn(100,_T("入账原值"));
	list.InsertColumn(100,_T("累计折旧"));
	list.InsertColumn(100,_T("净值"));
	list.InsertColumn(100,_T("规格"));
	list.InsertColumn(100,_T("使用状态"));
	list.InsertColumn(100,_T("预计净残值率"));
	list.InsertColumn(100,_T("预计净残值"));
	list.InsertColumn(100,_T("入账日期"));
	list.InsertColumn(100,_T("预计使用月份"));
	list.InsertColumn(100,_T("已计提月份"));
	list.InsertColumn(100,_T("折旧方法"));
	list.InsertColumn(100,_T("月折旧率"));
	list.InsertColumn(100,_T("月折旧额"));
	for (int i =0 ;i<17;i++)
		list.SetColumnWidth(i,100);
	OnButtonrefresh();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUpdateEquip::OnButtonrefresh() 
{
	AddEquipKinds();
	AddEquipMode();	
	AddUseState();
	AddQueryCondition();
	ClearText();
	list.DeleteAllItems();
}

void CUpdateEquip::ClearText()
{
	CWnd * temp;
	temp = this;
	for (int i= 0;i<16;i++)
	{
		temp = this->GetNextDlgTabItem(temp);
		temp->SetWindowText(_T(""));
	}
	//设置日期
	CTime t=CTime::GetCurrentTime();
	regdate.SetTime(&t);
	equipid.SetWindowText(_T(""));
}

void CUpdateEquip::AddEquipKinds()
{
	_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select kinds from EquipmentManage.dbo.tb_kinds",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	if (temp->RecordCount>0) //如果有数据,利用循环向组合框中添加数据
	{
		equipkinds.ResetContent();
		while (!temp->ADOEOF)
		{
			CString str;
			str = temp->GetFields()->GetItem("kinds")->Value.bstrVal;
			equipkinds.AddString(str);
			temp->MoveNext();
		}
	}
}

void CUpdateEquip::AddEquipMode()
{
	_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select addkinds from EquipmentManage.dbo.tb_addkinds",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	if (temp->RecordCount>0) //如果有数据,利用循环向组合框中添加数据
	{
		addkinds.ResetContent();
		while (!temp->ADOEOF)
		{
			CString str;
			str = temp->GetFields()->GetItem("addkinds")->Value.bstrVal;
			addkinds.AddString(str);
			temp->MoveNext();
		}
	}
}

void CUpdateEquip::AddUseState()
{
		_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select usestate from EquipmentManage.dbo.tb_usestate",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	if (temp->RecordCount>0) //如果有数据,利用循环向组合框中添加数据
	{
		usestate.ResetContent();
		while (!temp->ADOEOF)
		{
			CString str;
			str = temp->GetFields()->GetItem("usestate")->Value.bstrVal;
			usestate.AddString(str);
			temp->MoveNext();
		}
	}
}

void CUpdateEquip::AddQueryCondition()
{
	_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select distinct name from EquipmentManage.dbo.tb_equipmentinfo",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	querycondition.ResetContent();
	while (!temp->ADOEOF)
	{
		CString str;
		str = temp->GetFields()->GetItem("name")->Value.bstrVal;
		querycondition.AddString(str);
		temp->MoveNext();
	}
}

void CUpdateEquip::OnQuery() 
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
		sql.Format(_T("select * from EquipmentManage.dbo.tb_equipmentinfo where name like '%s%%'"),str);
		temp->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);		
		if (temp->RecordCount>0)
		{
			int row = 0;
			while (!temp->ADOEOF)
			{
				list.InsertItem(row,_T(""),0);
				for (int i= 0;i<temp->GetFields()->Count-1;i++)
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

BOOL CUpdateEquip::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message ==WM_KEYDOWN)
		if (pMsg->wParam ==13)
			pMsg->wParam = 9;	
	return CDialog::PreTranslateMessage(pMsg);
}

void CUpdateEquip::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int row = list.GetSelectionMark();
	CString str;
	if (row !=-1)
	{	
		CWnd * temp;
		temp = this;
		for (int i= 0;i<16;i++)
		{
			temp = this->GetNextDlgTabItem(temp);
			str =list.GetItemText(row,i+1); //对于表格list,0对应于编号,
			temp->SetWindowText(str);
		}	
		//对于折旧方法和入账日期单独赋值
		str = list.GetItemText(row,14);
		if (str == _T("平均年限法1"))
			depremethod.SetCurSel(0);
		else
			depremethod.SetCurSel(1);
		str = list.GetItemText(row,11);
		CTime t ;
		t = theApp.StrToTime(str);
		regdate.SetTime(&t);
		//显示资产编号
		str = list.GetItemText(row,0);
		equipid.SetWindowText(str);
	}
	*pResult = 0;
}

void CUpdateEquip::OnChangeSourcevalue() 
{
	CString temp1,temp2;
	sourcevalue.GetWindowText(temp1);
	addupdepre.GetWindowText(temp2);
	if ((temp1.IsEmpty())|(temp2.IsEmpty())) //如果入账原值或累计折旧为空,净值为空
	{
		purevalue.SetWindowText(_T(""));
	}
	else
	{
		float source,add,netvalue;
		source = _ttof(temp1);
		add = _ttof(temp2);
		netvalue = source-add;
		CString temp3;
		temp3.Format(_T("%f"),netvalue);
		purevalue.SetWindowText(temp3);
	}
	OnChangePrepurserate();//计算预计净残值	
}

void CUpdateEquip::OnChangeAddupdepre() 
{
	OnChangeSourcevalue(); //调用入账原值改变时的事件
}

void CUpdateEquip::OnChangePurevalue() 
{
	//月折旧额 =( 入账原值-累计折旧-预计净残值)/(预计使用月份-已计提月份)
	CString c_temp1,c_temp2,c_temp3,c_temp4,c_temp5;
	sourcevalue.GetWindowText(c_temp1);
	addupdepre.GetWindowText(c_temp2);
	prepurevalue.GetWindowText(c_temp3);
	preusemonth.GetWindowText(c_temp4);
	depremonth.GetWindowText(c_temp5);
	if (c_temp1.IsEmpty()|c_temp2.IsEmpty()|c_temp3.IsEmpty()|c_temp4.IsEmpty()|c_temp5.IsEmpty())
	{
		monthdeprevalue.SetWindowText(_T(""));
	}
	else
	{
		float f_value1,f_value2,f_value3,f_value4,f_value5,f_value;
		f_value1 = _ttof(c_temp1);
		f_value2 = _ttof(c_temp2);
		f_value3 = _ttof(c_temp3);
		f_value4 = _ttof(c_temp4);
		f_value5 = _ttof(c_temp5);
		f_value = (f_value1-f_value2-f_value3)/(f_value4-f_value5);
		CString temp;
		temp.Format(_T("%f"),f_value);
		monthdeprevalue.SetWindowText(temp);
	}	
}

void CUpdateEquip::OnChangePrepurserate() 
{
	CString temp1,temp2;
	prepurerate.GetWindowText(temp1); //获得净残值率
	sourcevalue.GetWindowText(temp2);//获入账原值
	if ((temp1.IsEmpty())|(temp2.IsEmpty())) //如果净值或净残值率为空,清空净残值
	{
		prepurevalue.SetWindowText(_T(""));		
	}
	else
	{
		float netrate,value,netvalue;
		netrate = _ttof(temp1);
		value = _ttof(temp2);
		//净残值 = 入账原值 * 净残值率
		netvalue = value * netrate;
		CString temp3;
		temp3.Format(_T("%f"),netvalue);
		prepurevalue.SetWindowText(temp3);	
	}
	OnChangePreusemonth();//计算月折旧率	
}

void CUpdateEquip::OnChangePreusemonth() 
{
	CString temp1,temp2;
	preusemonth.GetWindowText(temp1); //获得预计使用月份
	prepurerate.GetWindowText(temp2);//获得净残值率
	if ((temp1.IsEmpty())|(temp2.IsEmpty())) //如果预计使用月份或净残值率为空,清空月折旧率
	{
		monthdeprerate.SetWindowText(_T(""));		
	}
	else
	{
		float monthrate,value,monthvalue;
		monthvalue = _ttof(temp1);
		value = _ttof(temp2);
		//月折旧率 = (1 - 净残值率)/预计使用月份
		monthrate = (1- value)/(monthvalue);
		CString temp3;
		temp3.Format(_T("%f"),monthrate);
		monthdeprerate.SetWindowText(temp3);	
	}	
}

void CUpdateEquip::OnChangeDepremonth() 
{
	if (depremethod.GetCurSel()==1)//平均年限法2
		OnChangePurevalue();	
}

void CUpdateEquip::OnSelchangeDepremethod() 
{
	if (depremethod.GetCurSel()==-1)
		monthdeprevalue.SetWindowText(_T(""));
	else if (depremethod.GetCurSel()==0) //平均年限法1
	{
		CString value1,value2;
		sourcevalue.GetWindowText(value1);//获取入账原值
		monthdeprerate.GetWindowText(value2);
		if ((value1.IsEmpty())|(value2.IsEmpty())) //如果入账原值或月折旧率为空,月折旧额为空
			monthdeprevalue.SetWindowText(_T(""));
		else //计算月折旧额
		{
			//月折旧额 = 入账原值*月折旧率
			float m_value,m_rate,s_value;
			m_rate = _ttof(value2);
			s_value = _ttof(value1);
			m_value = s_value * m_rate;
			CString c_value;
			c_value.Format(_T("%f"),m_value);
			monthdeprevalue.SetWindowText(c_value);
		}
	}
	else //平均年限法2
	{		
		OnChangePurevalue(); //调用预计净残值改变时的事件		
	}	
}

void CUpdateEquip::OnChangeMonthdeprerate() 
{
	OnSelchangeDepremethod() ;	
}

void CUpdateEquip::OnButtonupdate() 
{
	CString id;
	equipid.GetWindowText(id);
	if (!id.IsEmpty())
	{
		if(!InfoIsNull())
		{
			if(!IsNegative())
			{
				if (MessageBox(_T("确实要修改资产信息吗?"),_T("提示"),MB_YESNO)==IDYES)
				{
					float f_sourcevalue,f_addupdepre,f_netvalue,f_prenetrate,f_prenetvalue,f_premonth,f_month,f_deprevalue,f_deprerate;
					CTime t;
					regdate.GetTime(t);
					CString arrays[16];		
					CWnd * temp;
					temp = this;
					for (int i= 0;i<16;i++)
					{
						temp = this->GetNextDlgTabItem(temp);
						temp->GetWindowText(arrays[i]);
					}
					f_sourcevalue = _ttof(arrays[3]);
					f_addupdepre = _ttof(arrays[4]);
					f_netvalue = _ttof(arrays[5]);
					f_prenetrate = _ttof(arrays[8]);
					f_prenetvalue = _ttof(arrays[9]);
					f_premonth = _ttoi(arrays[11]);
					f_month = _ttoi(arrays[12]);
					f_deprerate = _ttof(arrays[14]);
					f_deprevalue = _ttof(arrays[15]);			
					CString sql;
					sql.Format(_T("update EquipmentManage.dbo.tb_equipmentinfo set name = '%s',kinds = '%s',addkind = '%s',sourcevalue = %f,depreciation = %f ,netvalue= %f,spec = '%s',usestate = '%s',prenetvaluerate = %f,prenetvalue = %f,regdate = '%s',preusemonth = %f,depreciationmonth = %f,depremethod = '%s',monthdeprerate = %f,monthdeprevalue = %f,enabled = %d where equipmentid = '%s' "),arrays[0],arrays[1],arrays[2],f_sourcevalue,f_addupdepre,f_netvalue,arrays[6],arrays[7],f_prenetrate,f_prenetvalue,arrays[10],f_premonth,f_month,arrays[13],f_deprerate,f_deprevalue,0,id);
					try
					{
						theApp.datamanage->ExecSQL(sql);
						MessageBox(_T("修改成功"),_T("提示"),64);
					}
					catch(...)
					{
						MessageBox(_T("修改失败"),_T("提示"),64);
					}
					OnButtonrefresh() ;
				}
			}
			else
				MessageBox(_T("资产信息不能出现负数"),_T("提示"),64);
		}
		else
			MessageBox(_T("资产信息不能为空"),_T("提示"),64);
	}
	else
		MessageBox(_T("资产编号不能为空"),_T("提示"),64);	
}

bool CUpdateEquip::InfoIsNull()
{
	CWnd * temp;
	temp = this;
	for (int i= 0;i<16;i++)
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

bool CUpdateEquip::IsNegative()
{
	CString c_value1,c_value2,c_value3,c_value4,c_value5,c_value6,c_value7,c_value8;
	float f_value1,f_value2,f_value3,f_value4,f_value5,f_value6,f_value7,f_value8;
	sourcevalue.GetWindowText(c_value1);//入账原值
	addupdepre.GetWindowText(c_value2);//累计折旧
	purevalue.GetWindowText(c_value3);//净值
	prepurevalue.GetWindowText(c_value4);//净残值率
	preusemonth.GetWindowText(c_value5);//预计使用月份
	depremonth.GetWindowText(c_value6);//已计提月份
	monthdeprerate.GetWindowText(c_value7);//月折旧率
	monthdeprevalue.GetWindowText(c_value8); //月折旧额
	f_value1 = _ttof(c_value1);
	f_value2 = _ttof(c_value2);
	f_value3 = _ttof(c_value3);
	f_value4 = _ttof(c_value4);
	f_value5 = _ttof(c_value5);
	f_value6 = _ttof(c_value6);
	f_value7 = _ttof(c_value7);
	f_value8 = _ttof(c_value8);
	if ((f_value1 <0)|(f_value2<0)|(f_value3<0)|(f_value4 <0)|(f_value5 <0)|(f_value6 <0)|(f_value7 <0))
		return true;
	else
		return false;
}

void CUpdateEquip::OnButtonclose() 
{
	EndDialog(0);	
}
