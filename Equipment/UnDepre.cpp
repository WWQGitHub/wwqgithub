// UnDepre.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "UnDepre.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnDepre dialog
extern CEquipmentApp theApp;

CUnDepre::CUnDepre(CWnd* pParent /*=NULL*/)
	: CDialog(CUnDepre::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}

void CUnDepre::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnDepre)
	DDX_Control(pDX, IDC_RICHEDIT2, memo);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, currentdate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnDepre, CDialog)
	//{{AFX_MSG_MAP(CUnDepre)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnDepre message handlers

void CUnDepre::OnOK() 
{
	// TODO: Add extra validation here
	

}

void CUnDepre::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CUnDepre::OnInitDialog() 
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
			str.LoadString(IDS_Undepre);
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
	str = _T("注意:\n   本系统反计提折旧只允许对当前会计期已计提折旧的固定资产进行反计提,如果当前会计期没有计提折旧固定资产,不允许反计提.");
	memo.SetWindowText(str);
	CTime t = CTime::GetCurrentTime();
	currentdate.SetTime(&t);
	return TRUE; 
}

void CUnDepre::OnButtondelete() 
{
	//查询当前会计期是否进行计提折旧
	if (MessageBox(_T("确实要进行反计提管理吗?"),_T("提示"),MB_YESNO)==IDYES)
	{
		CString id,sql;
		CTime t;
		currentdate.GetTime(t);
		id = CTime::GetCurrentTime().Format(_T("%Y%m"));
		_RecordsetPtr recordset;
		recordset = theApp.datamanage->Record1;
		recordset->raw_Close();
		sql.Format( _T("select tag from EquipmentManage.dbo.EquipmentManage.dbo.tb_depreciation where tag = '%s'"),id);
		recordset->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
		if ( recordset->RecordCount <1)
		{
			MessageBox(_T("本期没有进行资产折旧,不能进行反计提."),_T("提示"),64);
			return ;
		}
		//进行反计提
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
					c_id = recordset->GetFields()->GetItem("equipmentid")->Value.bstrVal;
					c_method = recordset->GetFields()->GetItem("depremethod")->Value.bstrVal;
					if (c_method == "平均年限法1")
					{
						//折旧方法  累计折旧 = 累计折旧+月折旧额
						recordset->GetFields()->GetItem("depreciation")->Value = (float)recordset->GetFields()->GetItem("depreciation")->Value - (float)recordset->GetFields()->GetItem("monthdeprevalue")->Value ;
						recordset->GetFields()->GetItem("depreciationmonth")->Value= (float)recordset->GetFields()->GetItem("depreciationmonth")->Value-1;
						recordset->Update();
					}
					else //平均年限法2
					{
						recordset->GetFields()->GetItem("depreciationmonth")->Value= (float)recordset->GetFields()->GetItem("depreciationmonth")->Value-1;					
						//折旧方法  月折旧额= (入账原值 -累计折旧-预计净残值)/(预计使用月份-已计提月份)					
						recordset->GetFields()->GetItem("monthdeprevalue")->Value= ((float)recordset->GetFields()->GetItem("sourcevalue")->Value-(float)recordset->GetFields()->GetItem("depreciation")->Value-(float)recordset->GetFields()->GetItem("prenetvalue")->Value)/((float)recordset->GetFields()->GetItem("preusemonth")->Value-(float)recordset->GetFields()->GetItem("depreciationmonth")->Value);			
						recordset->Update();
					}
					recordset->MoveNext();
				}
				sql.Format(_T("delete EquipmentManage.dbo.tb_depreciation where tag = '%s'"),id);
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
}

void CUnDepre::OnButtonclose() 
{
	EndDialog(0);	
}
