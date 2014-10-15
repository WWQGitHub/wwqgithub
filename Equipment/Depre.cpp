// Depre.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "Depre.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CDepre dialog


CDepre::CDepre(CWnd* pParent /*=NULL*/)
	: CDialog(CDepre::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}


void CDepre::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDepre)
	DDX_Control(pDX, IDC_RICHEDIT2, memo);
	DDX_Control(pDX, IDC_EDIT1, currentdate);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDepre, CDialog)
	//{{AFX_MSG_MAP(CDepre)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDepre message handlers

void CDepre::OnOK() 
{
	// TODO: Add extra validation here
	

}

void CDepre::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDepre::OnInitDialog() 
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
			buttons[i].idCommand = ID_BUTTONADD+2; //对应于删除
			buttons[i].iBitmap = 2;
			str.LoadString(IDS_Depremanage);
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
	CString str;
	str = _T("注意:\n   本系统计提折旧按照会计制度中对资产计提折旧的有关规定处理,本期增加的固定资产,本期不计提折旧,下期计提折旧,本期减少的固定资产,本期继续计提折旧,下期停止计提折旧.");
	memo.SetWindowText(str);
	CTime t = CTime::GetCurrentTime();
	date.SetTime(&t);
	str = t.Format(_T("%Y-%m-%d"));
	currentdate.SetWindowText(str);
	return TRUE;  
}

void CDepre::OnButtondelete() 
{
	//判断折旧时间是否大于系统当前时间
	CTime t,t1;
	CTimeSpan temp;
	date.GetTime(t);
	CString c_date;
	currentdate.GetWindowText(c_date);
	t1 = theApp.StrToTime(c_date);
	temp = t-t1;
	if (temp.GetDays()>=1)
	{
		MessageBox(_T("折旧日期不能大于系统当前日期."),_T("提示"),64);
		return ;
	}
	//判断本期是否进行了折旧
	CString id,sql;
	id = CTime::GetCurrentTime().Format(_T("%Y%m"));
	_RecordsetPtr recordset;
	recordset = theApp.datamanage->Record1;
	recordset->raw_Close();
	sql.Format( _T("select tag from EquipmentManage.dbo.tb_depreciation where tag = '%s'"),id);
	recordset->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	if ( recordset->RecordCount >0)
	{
		MessageBox(_T("本期已进行了资产折旧."),_T("提示"),64);
		return ;
	}
	//进行计提折旧
	try
	{
		theApp.datamanage->GetConn()->BeginTrans();
		sql.Format(_T("select * from EquipmentManage.dbo.tb_equipmentinfo where Enabled =0 and (equipmentid not in (select equipmentid from EquipmentManage.dbo.tb_equipmentinfo where year(regdate) = '%s' and month(regdate) = '%s')) or equipmentid in (select equipmentid from EquipmentManage.dbo.tb_equipmentdecrease where year(cleardate) = '%s' and month(cleardate) = '%s')"),t.Format(_T("%Y")),t.Format(_T("%m")),t.Format(_T("%Y")),t.Format(_T("%m")));
		recordset->raw_Close();
		recordset->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
		if (recordset->RecordCount >0)
		{
			while (!recordset->ADOEOF)
			{
				CString c_id,c_method;
				float premonths,months;
				premonths = (float)recordset->GetFields()->GetItem("preusemonth")->Value;
				months = (float)recordset->GetFields()->GetItem("depreciationmonth")->Value;
				if (months < premonths) //已计提月份小于预计使用月份
				{	
					c_id = recordset->GetFields()->GetItem("equipmentid")->Value.bstrVal;
					c_method = recordset->GetFields()->GetItem("depremethod")->Value.bstrVal;
					if (c_method == "平均年限法1")
					{
						//折旧方法  累计折旧 = 累计折旧+月折旧额
						recordset->GetFields()->GetItem("depreciation")->Value = (float)recordset->GetFields()->GetItem("depreciation")->Value + (float)recordset->GetFields()->GetItem("monthdeprevalue")->Value ;
						recordset->GetFields()->GetItem("depreciationmonth")->Value= (float)recordset->GetFields()->GetItem("depreciationmonth")->Value+1;
						recordset->Update();
					}
					else if (c_method == "平均年限法2")
					{
						recordset->GetFields()->GetItem("depreciationmonth")->Value= (float)recordset->GetFields()->GetItem("depreciationmonth")->Value+1;					
						//折旧方法  月折旧额= (入账原值 -累计折旧-预计净残值)/(预计使用月份-已计提月份)					
						recordset->GetFields()->GetItem("monthdeprevalue")->Value= ((float)recordset->GetFields()->GetItem("sourcevalue")->Value-(float)recordset->GetFields()->GetItem("depreciation")->Value-(float)recordset->GetFields()->GetItem("prenetvalue")->Value)/((float)recordset->GetFields()->GetItem("preusemonth")->Value-(float)recordset->GetFields()->GetItem("depreciationmonth")->Value);			
						recordset->Update();
					}
				}
				recordset->MoveNext();
			}
			sql.Format(_T("insert into EquipmentManage.dbo.tb_depreciation values ('%s' ,'%s')"),id,t.Format(_T("%Y-%m-%d")));
			theApp.datamanage->ExecSQL(sql);
			theApp.datamanage->GetConn()->CommitTrans();
			MessageBox(_T("操作成功."),_T("提示"),64);
		}
		else
			MessageBox(_T("没有可折旧的固定资产."),_T("提示"),64);	
	}
	catch(...)
	{
		theApp.datamanage->GetConn()->RollbackTrans();
		MessageBox(_T("操作失败."),_T("提示"),64);
	}
}

void CDepre::OnButtonclose() 
{
	EndDialog(0);	
}
