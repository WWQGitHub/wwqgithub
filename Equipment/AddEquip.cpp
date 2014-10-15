// AddEquip.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "AddEquip.h"
#include "NumberEdit.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAddEquip dialog


CAddEquip::CAddEquip(CWnd* pParent /*=NULL*/)
	: CDialog(CAddEquip::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);	
}


void CAddEquip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CAddEquip)
	DDX_Control(pDX, IDC_PUREVALUE, purevalue);
	DDX_Control(pDX, IDC_PREPURSERATE, prepurerate);
	DDX_Control(pDX, IDC_PREPUREVALUE, prepurevalue);
	DDX_Control(pDX, IDC_MONTHDEPREVALUE, monthdeprevalue);
	DDX_Control(pDX, IDC_MONTHDEPRERATE, monthdeprerate);
	DDX_Control(pDX, IDC_ADDUPDEPRE, addupdepre);
	DDX_Control(pDX, IDC_SOURCEVALUE, sourcevalue);
	DDX_Control(pDX, IDC_USESTATE, usestate);
	DDX_Control(pDX, IDC_SPEC, spec);
	DDX_Control(pDX, IDC_REGDATE, regdate);
	DDX_Control(pDX, IDC_PREUSEMONTH, preusemonth);
	DDX_Control(pDX, IDC_EQUIPNAME, equipname);
	DDX_Control(pDX, IDC_EQUIPKINDS, equipkinds);
	DDX_Control(pDX, IDC_DEPREMONTH, depremonth);
	DDX_Control(pDX, IDC_DEPREMETHOD, depremethod);
	DDX_Control(pDX, IDC_ADDKINDS, addkinds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddEquip, CDialog)
	//{{AFX_MSG_MAP(CAddEquip)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_EN_CHANGE(IDC_SOURCEVALUE, OnChangeSourcevalue)
	ON_EN_CHANGE(IDC_ADDUPDEPRE, OnChangeAddupdepre)
	ON_EN_CHANGE(IDC_PREPURSERATE, OnChangePrepurserate)
	ON_EN_CHANGE(IDC_PUREVALUE, OnChangePurevalue)
	ON_EN_CHANGE(IDC_PREUSEMONTH, OnChangePreusemonth)
	ON_CBN_SELCHANGE(IDC_DEPREMETHOD, OnSelchangeDepremethod)
	ON_EN_CHANGE(IDC_DEPREMONTH, OnChangeDepremonth)
	ON_EN_CHANGE(IDC_MONTHDEPRERATE, OnChangeMonthdeprerate)
	ON_COMMAND(ID_BUTTONADD, OnButtonadd)
	ON_EN_CHANGE(IDC_PREPUREVALUE, OnChangePrepurevalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddEquip message handlers

void CAddEquip::OnOK() 
{
	// TODO: Add extra validation here
	

}

BOOL CAddEquip::OnInitDialog() 
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
			buttons[i].idCommand = ID_BUTTONADD+i-1;
			buttons[i].iBitmap = i-1;
			str.LoadString(ID_BUTTONADD+i-1);//第一个按钮为分隔条
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
	OnButtonrefresh();
	return TRUE;  
}

BOOL CAddEquip::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message ==WM_KEYDOWN)
		if (pMsg->wParam ==13)
			pMsg->wParam = 9;		
	return CDialog::PreTranslateMessage(pMsg);
}

void CAddEquip::OnButtonclose() 
{
	EndDialog(0);	
}

void CAddEquip::OnButtonrefresh() 
{
	AddEquipKinds();
	AddEquipMode();	
	AddUseState();
	ClearText();
}

void CAddEquip::AddEquipKinds()
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

void CAddEquip::AddEquipMode()
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

void CAddEquip::ClearText()
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
}
//入账原值改变时的事件
void CAddEquip::OnChangeSourcevalue() 
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
//累计折旧改变时的事件
void CAddEquip::OnChangeAddupdepre() 
{
	OnChangeSourcevalue(); 	//调用入账原值改变时的事件
}
//处理预计净残值率改变时的事件,用于计算预计净残值,月折旧率
void CAddEquip::OnChangePrepurserate() 
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

//处理净值改变时的事件
void CAddEquip::OnChangePurevalue() 
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

//处理预计使用月份的OnChange事件,计算月折旧率
void CAddEquip::OnChangePreusemonth() 
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
//处理折旧方法改变时的事件,计算月折旧额
void CAddEquip::OnSelchangeDepremethod() 
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

void CAddEquip::OnChangeDepremonth() 
{
	if (depremethod.GetCurSel()==1)//平均年限法2
		OnChangePurevalue();	
}

void CAddEquip::OnChangeMonthdeprerate() 
{
	OnSelchangeDepremethod() ;	
}

void CAddEquip::AddUseState()
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

bool CAddEquip::InfoIsNull()
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

bool CAddEquip::IsNegative()
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

void CAddEquip::OnButtonadd() 
{
	if (!InfoIsNull())
		if (!IsNegative())
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
			try
			{	//执行存储过程保存数据
				CString sql;
				CString str;
				str = _T("temp");
				sql.Format(_T(" Add_Equipmentinfo '%s','%s','%s',%f,%f,%f,'%s','%s',%f,%f,'%s',%f,%f,'%s',%f,%f ,'%s'"),arrays[0],arrays[1],arrays[2],f_sourcevalue,f_addupdepre,f_netvalue,arrays[6],arrays[7],f_prenetrate,f_prenetvalue,arrays[10],f_premonth,f_month,arrays[13],f_deprerate,f_deprevalue,str);
				theApp.datamanage->ExecSQL(sql);
				MessageBox(_T("操作成功."),_T("提示"),64);
			}
			catch(...)
			{
				MessageBox(_T("操作失败."),_T("提示"),64);
			}
			OnButtonrefresh();
		}
		else
		{
			MessageBox(_T("基础信息不能出现负数."),_T("提示"),64);
		}
	else
		this->MessageBox(_T("基础信息不能为空."),_T("提示"),64);
}

void CAddEquip::OnChangePrepurevalue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
